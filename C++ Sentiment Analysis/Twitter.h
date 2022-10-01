//
// Created by Reece Iriye on 9/12/22.
//

#ifndef ASSIGNMENT2_SENTIMENT_TWITTER_H
#define ASSIGNMENT2_SENTIMENT_TWITTER_H

#include <iostream>
#include <algorithm>
#include <fstream> // fileio
#include <filesystem> // fileio
#include <sstream> // Dr. Hahsler approved the use of stringstream library
#include <cmath> // For gradient_descent() linear algebra calculations

#include "DSString.h"
#include "DSVector.h"
#include "DataFrame.h"
#include "Word.h"

class Twitter {
private:
    DSVector<Word> theDictionary; // DSVector of all words and attributes in Word object
    DSVector<double> parameters; // DSVector of logistic regression parameters
    double trainingAccuracy; // percentage accuracy of logistic regression model on training set
    double testingAccuracy; // percentage accuracy of logistic regression model on testing set
    DSVector<DSString> testPredictions; // DSVector of our model's predictions on testing set
    DSVector<DSString> testIDs; // DSVector of all the ID's in the testing set
    DSVector<int> incorrectIndices; // DSVector containing all indices where we predicted incorrectly
public:
    Twitter() = default;
    Twitter(const DSVector<Word> theDictionary, const DSVector<double> parameters, double trainingAccuracy,
                     double testingAccuracy, DSVector<DSString> testPredictions, DSVector<DSString> testIDs,
                     DSVector<int> incorrectIndices);
    Twitter &operator=(const Twitter &rhs);
    ~Twitter() = default;

    // Getters and setters
    const DSVector<Word> &getTheDictionary() const;
    void setTheDictionary(const DSVector<Word> &theDictionary);
    const DSVector<double> &getParameters() const;
    void setParameters(const DSVector<double> &parameters);
    double getTrainingAccuracy() const;
    void setTrainingAccuracy(double trainingAccuracy);
    double getTestingAccuracy() const;
    void setTestingAccuracy(double testingAccuracy);
    const DSVector<DSString> &getTestPredictions() const;
    void setTestPredictions(const DSVector<DSString> &testPredictions);
    const DSVector<DSString> &getTestIDs() const;
    void setTestIDs(const DSVector<DSString> &testIDs);
    const DSVector<int> &getIncorrectIndices() const;
    void setIncorrectIndices(const DSVector<int> &incorrectIndices);


    /*
     * The read_tweets() function divides data from a specified filepath into
     * a 2D DSVector that I'll refer to as a DataFrame object. Technically, it's
     * 3D if you take into account the actual definition of DSString as a
     * DSVector of char's, but I digress.
     *
     * params
     *  DSString filename: the file that the function will read from
     *
     * @return a DataFrame object with information from the
     *      file categorized by specified titles.
     */
    DataFrame read_tweets(DSString filename);

    /*
     * The remove_stop_words() function is called within the cleaned_tweets()
     * function and deletes all of the stop words from the tweets so that
     * they won't be counted in the dictionary or in later numerical calculations.
     *
     * params
     *     DSVector<DSVector<DSString>> tweetWordsList (Pass-By Reference):
     *       updates tweetWordsList to not include the specified stop-words
     *
     */
    void remove_stop_words(DSVector<DSVector<DSString>> & tweetWordsList);

    /*
     *  The cleaned_tweets() function performs cleaning functions in the DSString
     *  class to normalize Natural Language Processing as much as possible.
     *
     *  params
     *      Dataframe df: representing the 2D DSVector of all file data
     *
     *  @RETURN a DSVector<DSVector<DSString>> that contains the tweets organized
     *  word-by-word for columns and each tweet for row.
     */
    DSVector<DSVector<DSString>> cleaned_tweets(DataFrame df);

    /*
     * The sentiment_label() function gets a 1D DSVector that contains
     * a "4" or "0" denoting whether a tweet is positive or negative.
     *
     * params
     *  Dataframe df: the data we previously read in from the file in 2D DSVector
     *      format
     *
     * @RETURN a DSVector<DSString> of "4"'s and "0"'s that represent our
     *      the actual sentiments of each tweet
     */
    DSVector<DSString> sentiment_label(DataFrame df);


    /*
     * The dictionary() function creates a DSVector of Word objects containing
     * the number of positive and negative appearances of each word based on our
     * training data.
     *
     * params
     *      DSVector<DSVector<DSString>> tweets: a cleaned 2D DSVector of our tweets
     *         categorized by each individual word in columns and each tweet for rows.
     *      DSVector<DSString> sentiments: contains the true sentiments in the training data
     *
     * @RETURN a DSVector<Word> containing each word and the number of positive and negative
     * appearances from the training set.
     */
    DSVector<Word> dictionary(
            DSVector<DSVector<DSString>> tweets,
            DSVector<DSString> sentiments
            );

    /*
     * Did not end up implementing this function due to terrible runtime and concerns that a 1-layer
     * classification algorithm would create an accurate logistic regression function.
     */
    DSVector<DSVector<int>> one_hot_encoding(DSVector<Word> dict, DSVector<DSVector<DSString>> tweets);


    /*
     * The numerical_data() function transforms each tweet into a 3-column 2D DSVector,
     * with the first row representing a 1 for the B0 parameter that we'll later implement
     * in the logistic regression model, the second row representing the number of total positive
     * appearances for all words that are in the selected tweet, and the third row representing
     * the latter but with negative appearances instead.
     *
     * params
     *      DSVector<Word> dict: Dictionary of words and each word's attributes
     *      DSVector<DSVector<DSString>> tweets: 2D DSVector of cleaned tweets
     *
     * @RETURN a 2D DSVector representing the numeric form of the data.
     */
    DSVector<DSVector<double>> numerical_data(
            DSVector<Word> dict,
            DSVector<DSVector<DSString>> tweets);


    double calculate_mean(DSVector<double> items);

    double calculate_stdev(DSVector<double> items);

    DSVector<DSVector<double>> standardize_data(DSVector<DSVector<double>> X);



    /*
     * The sigmoid() function is called on each loop in the gradient_descent() function
     *
     * params
     *      double theta: represents b0 + b1*x1 + b2*x2
     *
     * @RETURN a double denoting 1 / (1 + e^(-theta))
     */
    double sigmoid(double theta);

    /*
     * The gradient_descent() function is styled in a way that tries to capture the best
     * b0, b1, and b2 parameters in logistic regression. It iterates through a specified
     * number of epochs with a specified learning rate that I believe makes it work best, because
     * it's styled to minimize the cost function.
     *
     * params
     *      DSVector<DSVector<double>> : denotes the numerical training data
     *      DSVector<DSString> : denotes the true sentiments of each tweet
     */
    DSVector<double> gradient_descent(DSVector<DSVector<double>> trainingMatrix, DSVector<DSString> sentiments);

    /*
     * The training_accuracy() function outputs how well our logistic regression model predicts the sentiments
     * of our training data.
     *
     * params
     *      DSVector<double> parameters : logistic regression parameters
     *      DSVector<DSVector<DSString>> data : the numerical representationm of training data
     *      DSVector<DSString> sentiments : a DSVector of the true training sentiments
     */
    double training_accuracy(DSVector<double> parameters,
                             DSVector<DSVector<double>> data,
                             DSVector<DSString> sentiments);

    /*
     * The create_ID_list() function generates a list of our testing IDs
     *
     * params
     *      Dataframe df : denotes organized DSString testing data
     *
     * @RETURN a DSVector<DSString> of all the testing data IDs for each tweet
     */
    DSVector<DSString> create_ID_list(DataFrame df);

    /*
     * The testing_accuracy() function checks the true testing accuracy of our
     * logistic regression model
     *
     * params
     *      DSVector<double> parameters : the parameters in our dataset
     *      DSVector<DSVector<double>> data : numerical data
     *      DSVector<DSString> semtimemnts : denotes true sentiments of testing data
     */
    double testing_accuracy(DSVector<double> parameters,
                            DSVector<DSVector<double>> data,
                            DSVector<DSString> sentiments,
                            DSVector<DSString> IDs);

    /*
     * The train() function calls the correct methods needed to train our model.
     *
     * params
     *      DSString trainingFile : reads in the training set file
     */
    void train(DSString trainingFile);

    /*
     * The test() function calls the correct methods needed to test our model.
     *
     * params
     *      DSString testingFile : reads in the testing set file
     *      DSString resultsFile : reads in the results of our testing dataset from specified file
     */
    void test(DSString testingFile, DSString resultsFile);

    /*
     * The check_results() function generates two files that contain all our predictions, the testing
     * accuracy, and the results of our incorrectly checked tweets.
     *
     * params
     *      DSString predictionsTitle : the title of the file we create containing predictions
     *      DSString resultsTitle : the title of the file we create containing results
     */
    void check_results(DSString predictionsTitle, DSString resultsTitle);




};


#endif //ASSIGNMENT2_SENTIMENT_TWITTER_H
