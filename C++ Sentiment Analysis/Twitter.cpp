//
// Created by Reece Iriye on 9/12/22.
//

#include "Twitter.h"



using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// Constructor & Assignment Operator //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

Twitter::Twitter(const DSVector<Word> theDictionary, const DSVector<double> parameters, double trainingAccuracy,
                 double testingAccuracy, DSVector<DSString> testPredictions, DSVector<DSString> testIDs,
                 DSVector<int> incorrectIndices) {
    this->theDictionary = theDictionary;
    this->parameters = parameters;
    this->trainingAccuracy = trainingAccuracy;
    this->testingAccuracy = testingAccuracy;
    this->testPredictions = testPredictions;
    this->testIDs = testIDs;
    this->incorrectIndices = incorrectIndices;
}

Twitter &Twitter::operator=(const Twitter &rhs) {
    this->theDictionary = rhs.theDictionary;
    this->parameters = rhs.parameters;
    this->trainingAccuracy = rhs.trainingAccuracy;
    this->testingAccuracy = rhs.testingAccuracy;
    this->testPredictions = rhs.testPredictions;
    this->testIDs = rhs.testIDs;
    this->incorrectIndices = rhs.incorrectIndices;

    return *this;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// Getters and Setters ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

const DSVector<Word> &Twitter::getTheDictionary() const {
    return theDictionary;
}

void Twitter::setTheDictionary(const DSVector<Word> &theDictionary) {
    this->theDictionary = theDictionary;
}

const DSVector<double> &Twitter::getParameters() const {
    return parameters;
}

void Twitter::setParameters(const DSVector<double> &parameters) {
    this->parameters = parameters;
}

double Twitter::getTrainingAccuracy() const {
    return trainingAccuracy;
}

void Twitter::setTrainingAccuracy(double trainingAccuracy) {
    this->trainingAccuracy = trainingAccuracy;
}

double Twitter::getTestingAccuracy() const {
    return testingAccuracy;
}

void Twitter::setTestingAccuracy(double testingAccuracy) {
    this->testingAccuracy = testingAccuracy;
}

const DSVector<DSString> &Twitter::getTestPredictions() const {
    return testPredictions;
}

void Twitter::setTestPredictions(const DSVector<DSString> &testPredictions) {
    this->testPredictions = testPredictions;
}

const DSVector<DSString> &Twitter::getTestIDs() const {
    return testIDs;
}

void Twitter::setTestIDs(const DSVector<DSString> &testIDs) {
    this->testIDs = testIDs;
}

const DSVector<int> &Twitter::getIncorrectIndices() const {
    return incorrectIndices;
}

void Twitter::setIncorrectIndices(const DSVector<int> &incorrectIndices) {
    this->incorrectIndices = incorrectIndices;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// Training & Testing Methods /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*
 * The read_tweets() function divides data from a specified filepath into
 * a 2D DSVector that I'll refer to as a DataFrame object. Technically, it's
 * 3D if you take into account the actual definition of DSString as a
 * DSVector of char's, but I digress.
 *
 *
 * @return a DataFrame object with information from the
 *      file categorized by specified titles.
 */
DataFrame Twitter::read_tweets(DSString filename) {
    // Reading in file using stringstream:
    // https://stackoverflow.com/questions/132358/how-to-read-file-content-into-istringstream
    // https://stackoverflow.com/questions/1374468/stringstream-string-and-char-conversion-confusion

    DataFrame dataframe_2D;
    DSVector<DSString> dataframe_1D;

    // Read in file
    ifstream infile;
    infile.open(filename.c_str());

    // Try, catch
    if (infile.is_open()) {
        cout << "   Reading Tweets [==      ][1/4]..." << endl;

        stringstream buffer; // Declare stringstream buffer
        buffer << infile.rdbuf();

        infile.close(); // close the file after reading everything

        // .str().c_str() converts buffer into a c_string, which is compatible with operator= for DSString
        DSString data = buffer.str().c_str();

        cout << "   Reading Tweets [====    ][2/4]..." << endl;

        // Reference .split() in DSString class
        dataframe_1D = data.split('\n');
    }
    else {
        throw runtime_error("Input file not open!");
    }

    cout << "   Reading Tweets [======  ][3/4]..." << endl;

    size_t colCounter = 1;

    for (int i = 0; i < dataframe_1D[0].size(); ++i) {
        if (dataframe_1D[0][i] == ',')
            colCounter++;
    }

    // Column separating for-loop
    for (auto row: dataframe_1D) {
        DSVector<DSString> tmp = row.split(',', colCounter);
        dataframe_2D.push_back(tmp);
    }

    cout << "   Reading Tweets [========][4/4]..." << endl;


    return dataframe_2D;
}







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
void Twitter::remove_stop_words(DSVector<DSVector<DSString>> & tweetWordsList) {
    DSVector<DSString> stopWords(732);
    DSVector<DSString> cleanedStopWords;

    // Read in file
    // Data sources:
    //// https://gist.githubusercontent.com/ZohebAbai/513218c3468130eacff6481f424e4e64/raw/b70776f341a148293ff277afa0d0302c8c38f7e2/gist_stopwords.txt
    //// https://www.kaggle.com/datasets/rowhitswami/stopwords?resource=download
    ifstream file;
    file.open("data/stopwords.csv");

    // Try, catch
    if (file.is_open()) {
        stringstream buffer; // Declare stringstream buffer
        buffer << file.rdbuf();

        file.close(); // close the file after reading everything

        // .str().c_str() converts buffer into a c_string, which is compatible with operator= for DSString
        DSString data = buffer.str().c_str();

        // Reference .split() in DSString class
        stopWords = data.split(',');
    }
    else {
        throw runtime_error("Stop words file is not open!");
    }

    // Create copy of stopWords to generate cleaned versions, then append them to stopWords DSVector
    cleanedStopWords = stopWords;
    for (int i = 0; i < cleanedStopWords.size(); ++i) {
        cleanedStopWords[i].stemming();
        cleanedStopWords[i].remove_repeat_chars();
        stopWords.push_back(cleanedStopWords[i]);
    }

    // Ensure that all stop words in our stop dataset are removed to lessen overfitting
    for (int i = 0; i < stopWords.size(); ++i)
        for (int j = 0; j < tweetWordsList.size(); ++j)
            for (int k = 0; k < tweetWordsList[j].size(); ++k)
                if(stopWords[i] == tweetWordsList[j][k])
                    tweetWordsList[j].remove(k);

}







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
DSVector<DSVector<DSString>> Twitter::cleaned_tweets(DataFrame df) {
    cout << "   Cleaning Tweets [===      ][1/3]..." << endl;

    DSVector<int> shape(2);
    shape[0] = df.size();

    // Runtime Error if we aren't observing the Tweet column
    if (df[0][-1] != "Tweet")
        throw std::runtime_error("Not analyzing Tweet Column!");

    DSVector<DSVector<DSString>> tweetWordsList;

    // i=1 so we don't include the column title
    for (size_t i = 1; i < shape[0]; ++i) {
        // Create buffer DSVector that holds words in individual Tweet
        DSVector<DSString> buffer;

        // Implement cleaning functions in DSString and assign result to buffer
        buffer = df[i][-1].to_lower().remove_punctuation().split(' ');

        for (int j = 0; j < buffer.size(); ++j) {
            buffer[j].stemming();
            buffer[j].remove_repeat_chars();
        }

        tweetWordsList.push_back(buffer);

        if (i == shape[0] / 2)
            cout << "   Cleaning Tweets [======   ][2/3]..." << endl;

    }

    remove_stop_words(tweetWordsList);

    cout << "   Cleaning Tweets [=========][3/3]..." << endl;




    return tweetWordsList;
}

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
DSVector<DSString> Twitter::sentiment_label(DataFrame df) {
    DSVector<DSString> sentiments;

    if (df[0][0] == "Sentiment")
        for (int i = 1; i < df.size(); ++i) {
            sentiments.push_back(df[i][0]);
        }
    else
        throw runtime_error("sentiment_label() in Twitter class failed! Not analyzing sentiment column!");

    return sentiments;

}







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
DSVector<Word> Twitter::dictionary(
        DSVector<DSVector<DSString>> tweets,
        DSVector<DSString> sentiments
) {

    DSVector<Word> wordDictionary;
    cout << "   Creating Dictionary [==                    ][1/11]..." << endl;

    int tweetNum = tweets.size();

    for (int i = 0; i < tweetNum; ++i) {
        int wordCount = tweets[i].size();

        // LOADING SCREEN CODE:
        if(i == (tweetNum / 10))
            cout << "   Creating Dictionary [====                  ][2/11]..." << endl;
        else if(i == 2*(tweetNum / 10))
            cout << "   Creating Dictionary [======                ][3/11]..." << endl;
        else if(i == 3*(tweetNum / 10))
            cout << "   Creating Dictionary [========              ][4/11]..." << endl;
        else if(i == 4*(tweetNum / 10))
            cout << "   Creating Dictionary [==========            ][5/11]..." << endl;
        else if(i == 5*(tweetNum / 10))
            cout << "   Creating Dictionary [============          ][6/11]..." << endl;
        else if(i == 6*(tweetNum / 10))
            cout << "   Creating Dictionary [==============        ][7/11]..." << endl;
        else if(i == 7*(tweetNum / 10))
            cout << "   Creating Dictionary [================      ][8/11]..." << endl;
        else if(i == 8*(tweetNum / 10))
            cout << "   Creating Dictionary [==================    ][9/11]..." << endl;
        else if(i == 9*(tweetNum / 10))
            cout << "   Creating Dictionary [====================  ][10/11]..." << endl;
        // END LOADING SCREEN CODE


        // Inner loop evaluating each tweet
        for (int j = 0; j < wordCount; ++j) {
            Word word;
            word.setTheWord(tweets[i][j]);
            int foundHere = -1;

            // SKIP EMPTY SPACES THAT MIGHT ACCIDENTALLY BE LEFT OVER
            if (word.getTheWord() == DSString(""))
                continue;

            bool wordIsSeen = false;
            for (int k = 0; k < wordDictionary.size(); ++k) {
                if (word.getTheWord() == wordDictionary[k].getTheWord()) {
                    wordIsSeen = true;
                    foundHere = k;
                    break;
                }

            }

            // If we have not seen the word in training data yet
            if (!wordIsSeen) {
                // Positive sentiment case below
                if (sentiments[i] == "4") {
                    word.setPositive(1);
                    word.setNegative(0);
                }
                    // Negative sentiment case below
                else if (sentiments[i] == "0") {
                    word.setPositive(0);
                    word.setNegative(1);
                }
                    // Exception handling
                else {
                    throw runtime_error("dictionary() in Twitter class failed! Tweet doesn't have positive ('4') or negative ('0') sentiment!");
                }

                // Insert here!
                wordDictionary.push_back(word);
            } else {
                // Increment positive appearances in positive tweet case
                if (sentiments[i] == "4")
                    wordDictionary[foundHere].setPositive(
                            wordDictionary[foundHere].getPositive() + 1
                    );

                    // Increment negative appearances in negative tweet case
                else if (sentiments[i] == "0")
                    wordDictionary[foundHere].setNegative(
                            wordDictionary[foundHere].getNegative() + 1
                    );

                    // Exception handling
                else
                    throw runtime_error("dictionary() in Twitter class failed! Tweet doesn't have positive ('4') or negative ('0') sentiment!");
            }

        } // end inner loop
    } // end outer loop

    cout << "   Creating Dictionary [======================][11/11]..." << endl;


    return wordDictionary;
}






/*
 * Did not end up implementing this function due to terrible runtime and concerns that a 1-layer
 * classification algorithm would not create an accurate logistic regression function.
 */
// https://medium.com/analytics-vidhya/twitter-sentiment-analysis-8ef90df6579c
DSVector<DSVector<int>> Twitter::one_hot_encoding(DSVector<Word> dict, DSVector<DSVector<DSString>> tweets) {

    cout << "   One Hot Encoding [=                                        ][1/41]..." << endl;

    DSVector<DSVector<int>> matrix;

    int matRowNum = tweets.size();
    int matColNum = dict.size() + 1;


    for (int i = 0; i < matRowNum; ++i) {

        if(i == (matColNum / 40))
            cout << "   One Hot Encoding [==                                       ][2/41]..." << endl;
        else if(i == 2*(matColNum / 40))
            cout << "   One Hot Encoding [===                                      ][3/41]..." << endl;
        else if(i == 3*(matColNum / 40))
            cout << "   One Hot Encoding [====                                     ][4/41]..." << endl;
        else if(i == 4*(matColNum / 40))
            cout << "   One Hot Encoding [=====                                    ][5/41]..." << endl;
        else if(i == 5*(matColNum / 40))
            cout << "   One Hot Encoding [======                                   ][6/41]..." << endl;
        else if(i == 6*(matColNum / 40))
            cout << "   One Hot Encoding [=======                                  ][7/41]..." << endl;
        else if(i == 7*(matColNum / 40))
            cout << "   One Hot Encoding [========                                 ][8/41]..." << endl;
        else if(i == 8*(matColNum / 40))
            cout << "   One Hot Encoding [=========                                ][9/41]..." << endl;
        else if(i == 9*(matColNum / 40))
            cout << "   One Hot Encoding [==========                               ][10/41]..." << endl;
        else if(i == 10*(matColNum / 40))
            cout << "   One Hot Encoding [===========                              ][11/41]..." << endl;
        else if(i == 11*(matColNum / 40))
            cout << "   One Hot Encoding [============                             ][12/41]..." << endl;
        else if(i == 12*(matColNum / 40))
            cout << "   One Hot Encoding [=============                            ][13/41]..." << endl;
        else if(i == 13*(matColNum / 40))
            cout << "   One Hot Encoding [==============                           ][14/41]..." << endl;
        else if(i == 14*(matColNum / 40))
            cout << "   One Hot Encoding [===============                          ][15/41]..." << endl;
        else if(i == 15*(matColNum / 40))
            cout << "   One Hot Encoding [================                         ][16/41]..." << endl;
        else if(i == 16*(matColNum / 40))
            cout << "   One Hot Encoding [=================                        ][17/41]..." << endl;
        else if(i == 17*(matColNum / 40))
            cout << "   One Hot Encoding [==================                       ][18/41]..." << endl;
        else if(i == 18*(matColNum / 40))
            cout << "   One Hot Encoding [===================                      ][19/41]..." << endl;
        else if(i == 19*(matColNum / 40))
            cout << "   One Hot Encoding [====================                     ][20/41]..." << endl;
        else if(i == 20*(matColNum / 40))
            cout << "   One Hot Encoding [=====================                    ][21/41]..." << endl;
        else if(i == 21*(matColNum / 40))
            cout << "   One Hot Encoding [======================                   ][22/41]..." << endl;
        else if(i == 22*(matColNum / 40))
            cout << "   One Hot Encoding [=======================                  ][23/41]..." << endl;
        else if(i == 23*(matColNum / 40))
            cout << "   One Hot Encoding [========================                 ][24/41]..." << endl;
        else if(i == 24*(matColNum / 40))
            cout << "   One Hot Encoding [=========================                ][25/41]..." << endl;
        else if(i == 25*(matColNum / 40))
            cout << "   One Hot Encoding [==========================               ][26/41]..." << endl;
        else if(i == 26*(matColNum / 40))
            cout << "   One Hot Encoding [===========================              ][27/41]..." << endl;
        else if(i == 27*(matColNum / 40))
            cout << "   One Hot Encoding [============================             ][28/41]..." << endl;
        else if(i == 28*(matColNum / 40))
            cout << "   One Hot Encoding [=============================            ][29/41]..." << endl;
        else if(i == 29*(matColNum / 40))
            cout << "   One Hot Encoding [==============================           ][30/41]..." << endl;
        else if(i == 30*(matColNum / 40))
            cout << "   One Hot Encoding [===============================          ][31/41]..." << endl;
        else if(i == 31*(matColNum / 40))
            cout << "   One Hot Encoding [================================         ][32/41]..." << endl;
        else if(i == 32*(matColNum / 40))
            cout << "   One Hot Encoding [=================================        ][33/41]..." << endl;
        else if(i == 33*(matColNum / 40))
            cout << "   One Hot Encoding [==================================       ][34/41]..." << endl;
        else if(i == 34*(matColNum / 40))
            cout << "   One Hot Encoding [===================================      ][35/41]..." << endl;
        else if(i == 35*(matColNum / 40))
            cout << "   One Hot Encoding [====================================     ][36/41]..." << endl;
        else if(i == 36*(matColNum / 40))
            cout << "   One Hot Encoding [=====================================    ][37/41]..." << endl;
        else if(i == 37*(matColNum / 40))
            cout << "   One Hot Encoding [======================================   ][38/41]..." << endl;
        else if(i == 38*(matColNum / 40))
            cout << "   One Hot Encoding [=======================================  ][39/41]..." << endl;
        else if(i == 39*(matColNum / 40))
            cout << "   One Hot Encoding [======================================== ][40/41]..." << endl;


        // Declare buffer vector to push back into matrixTranspose
        DSVector<int> bufferRow;

        for (int j = 0; j < matColNum; ++j) {
            bufferRow.push_back(0);

            // Push 1's into a column for matrix so we have a representative constant
            if (j == 0)
                bufferRow[j] = 1;

            // Insert numbers that represent number of word appearances per sentence
            else {
                // Runtime errors could be mitigated with a map, but I don't think my DSString works as a map key since it's a vector
                for (int k = 0; k < tweets[i].size(); ++k) {
                    bool tweetWord_equals_dictWord = dict[j-1].getTheWord() == tweets[i][k];
                    if (tweetWord_equals_dictWord)
                        bufferRow[j]++;
                }

            } // end else
        } // end inner loop

        // Input row into our 2D vector
        matrix.push_back(bufferRow);

    } // end outer loop

    cout << "   One Hot Encoding [=========================================][41/41]..." << endl;

    return matrix;
}



/*
 * The numerical_data() function transforms each tweet into a 3-column 2D DSVector,
 * with the first row representing a 1 for the B0 parameter that we'll later implement
 * in the logistic regression model, the second row representing the number of total positive
 * appearances for all words that are in the selected tweet, and the third row representing
 * the latter but with negative appearances instead. A TF-IDF method which I learned in the source
 * was used.
 *
 * params
 *      DSVector<Word> dict: Dictionary of words and each word's attributes
 *      DSVector<DSVector<DSString>> tweets: 2D DSVector of cleaned tweets
 *
 *
 * @RETURN a 2D DSVector representing the numeric form of the data.
 */
DSVector<DSVector<double>> Twitter::numerical_data(
        DSVector<Word> dict,
        DSVector<DSVector<DSString>> tweets
) {

    cout << "   Numerically representing data [==          ][1/6]..." << endl;
    DSVector<DSVector<double>> matrix;

    const int matRowNum = tweets.size();

    // Create a (tweets.size() x 3) matrix to implement as quantifiably measurable data
    // for tendencies of positive and negative tweets
    for (int i = 0; i < matRowNum; ++i) {

        // Loading screen
        if(i == (matRowNum / 5))
            cout << "   Numerically representing data [====        ][2/6]..." << endl;
        else if(i == 2*(matRowNum / 5))
            cout << "   Numerically representing data [======      ][3/6]..." << endl;
        else if(i == 3*(matRowNum / 5))
            cout << "   Numerically representing data [========    ][4/6]..." << endl;
        else if(i == 4*(matRowNum / 5))
            cout << "   Numerically representing data [==========  ][5/6]..." << endl;

        // Declare buffer vector to push back into matrixTranspose
        DSVector<double> bufferRow;

        int positiveAppearancesBuffer = 0;
        int negativeAppearancesBuffer = 0;

        // Insert 1 into all columns of the left side
        bufferRow.push_back(1);

        double totalWordsInTweet = double(tweets[i].size());

        for (int j = 0; j < totalWordsInTweet; ++j) {
            for (int k = 0; k < dict.size(); ++k) {
                if(dict[k].getTheWord() == tweets[i][j]) {

                    positiveAppearancesBuffer += dict[k].getPositive();
                    negativeAppearancesBuffer += dict[k].getNegative();

                    int pos = dict[k].getPositive();
                    int neg = dict[k].getNegative();

                    // Break the loop so we aren't iterating through the entire dictionary
                    break;
                }


            } // end inner inner loop

        } // end inner loop

        // Input row into our 2D vector
        bufferRow.push_back(positiveAppearancesBuffer);
        bufferRow.push_back(negativeAppearancesBuffer);

        matrix.push_back(bufferRow);

    } // end outer loop

    cout << "   Numerically representing data [============][6/6]..." << endl;

    return matrix;
}




/*
 * The mean() function calculates the mean of all elements of a DSVector<double>
 *
 * params
 *      DSVector<double> items : denotes all item's the function takes an average of
 *
 * @RETURN a double denoting the mean of all the items
 */
double Twitter::calculate_mean(DSVector<double> items) {
    int n = items.size();

    double avg = 0;
    for (const auto item : items)
        avg += item;

    avg /= n;


    return avg;
}


/*
 * The stdev() function calculates the standard deviation of all elements of a DSVector<double>
 *
 * params
 *      DSVector<double> items : denotes all item's the function takes an average of
 *
 * SOURCE: https://www.programiz.com/cpp-programming/examples/standard-deviation
 *
 * @RETURN a double denoting the standard deviation of all the items
 */
double Twitter::calculate_stdev(DSVector<double> items) {
    double theMean = calculate_mean(items);
    int n = items.size();

    double stdev = 0;
    for (int i = 0; i < n; ++i)
        stdev += pow(items[i] - theMean, 2);

    stdev = sqrt(stdev / n);


    return stdev;
}

/*
 *
 * Did not end up implementing this function in train() and test()
 *
 */
DSVector<DSVector<double>> Twitter::standardize_data(DSVector<DSVector<double>> X) {
    // Declare necessary variables
    DSVector<DSVector<double>> X_prime;
    int rowNum = X.size();
    int colNum = X[0].size();

    cout << "   Standardize Data [========        ][1/2]..." << endl;

    // Allocate memory in X_prime so we can later insert standardized values
    DSVector<double> buffer(colNum);
    buffer[0] = 1.0;  // ensure that we still retain our constant

    for (size_t i = 0; i < rowNum; ++i)
        X_prime.push_back(buffer);

    // Create X.transpose so I can obtain column data
    DSVector<DSVector<double>> X_T;
    for (int i = 0; i < colNum; ++i) {
        // Create buffer variable and store it into X_T iteratively
        DSVector<double> transposeBuffer;
        for (int j = 0; j < rowNum; ++j)
            transposeBuffer.push_back(X[j][i]);

        X_T.push_back(transposeBuffer);
    }


    // Retrieve means and standard deviations of variable columns
    DSVector<double> means;
    DSVector<double> stds;

    means.push_back(1);
    stds.push_back(0);

    for (int i = 1; i < X_T.size(); ++i) {
        double tmpMean = calculate_mean(X_T[i]);
        double tmpStDev = calculate_stdev(X_T[i]);

        means.push_back(tmpMean);
        stds.push_back(tmpStDev);
    }

    // Implement standardization formula
    // Formula: (x(i) - mean(x)) / std(x)
    for (int j = 1; j < colNum; ++j) {

        double varMean = means[j];
        double varStDev = stds[j];

        for (int i = 0; i < rowNum; ++i)
            X_prime[i][j] = (X[i][j] - varMean) / varStDev;


    }

    cout << "   Standardize Data [================][2/2]..." << endl;
    return X_prime;
}



/*
 * The sigmoid() function is called on each loop in the gradient_descent() function
 *
 * params
 *      double theta: represents b0 + b1*x1 + b2*x2
 *
 * @RETURN a double denoting 1 / (1 + e^(-theta))
 */
double Twitter::sigmoid(double theta) {
    return 1.0 / (1.0 + exp(-theta));
}




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
// https://medium.com/analytics-vidhya/logistic-regression-with-gradient-descent-explained-machine-learning-a9a12b38d710
// https://www.analyticsvidhya.com/blog/2020/04/machine-learning-using-c-linear-logistic-regression/
// https://www.internalpointers.com/post/cost-function-logistic-regression
//
/* Repeat until convergence : {
 *
 *    𝜃𝑗 := 𝜃𝑗 − 𝛼 (∂/∂𝜃𝑗 𝐽(𝜃))
 *                           |
 *    This is equal to below v
 *    𝜃[1:𝑗-1] := 𝜃[1:𝑗-1] − (𝛼 * (1/𝑚) * (∑𝑖( ℎ𝜃(𝑥(𝑖)) − 𝑦(𝑖) )*𝑥(𝑖)𝑗 ));
 *    𝜃[0] := 𝜃[0] − (𝛼 * (1/𝑚) * (∑𝑖( ℎ𝜃(𝑥(𝑖)) − 𝑦(𝑖) )*𝑥(𝑖)𝑗 ));
 *  }
 *
 *
 * y = b0 + b1*posNum + b2*negNum
*/
DSVector<double> Twitter::gradient_descent(DSVector<DSVector<double>> X, DSVector<DSString> strSentiments) {
    DSVector<double> trueParameters(5);

    const size_t epochs = 9000; // Initialize number of epochs
    const double alpha = 0.0052; // Initializing learning rate

    // Loading true y with numerical data instead of DSString
    DSVector<double> y;
    for (int i = 0; i < X.size(); ++i) {
        if (strSentiments[i] == "4")
            y.push_back(1.0);
        else if (strSentiments[i] == "0")
            y.push_back(0.0);
        else
            throw runtime_error("Sentiment element is neither positive nor negative in Twitter::gradient_descent()");
    }

    double error; // storing error values
    double b0 = 0.0; // initializing b0
    double b1 = 0.0; // initializing b1
    double b2 = 0.0; // initializing b2

    // Loop a total of (X.size() * epochs) times
    const size_t iterationLimit = epochs * X.size();

    for (size_t i = 0; i < iterationLimit; ++i) {
        int idx = (i % X.size());  // access index after every epoch
        double theta = b0          // make prediction
                       + (b1 * X[idx][1])
                       + (b2 * X[idx][2]);
        double y_hat = sigmoid(theta);
        error = y[idx] - y_hat;

        double gradient = y_hat * (1-y_hat);

        b0 = b0 - alpha * error * gradient * 1.0;       // updating b0
        b1 = b1 + alpha * error * gradient * X[idx][1]; // updating b1
        b2 = b2 + alpha * error * gradient * X[idx][2]; // updating b2

        if ((idx == 0) && (i % (epochs/19) == 0)) {
            cout << "   Training Logistic Regression Model"
                 << " [" << (i / X.size()) << "/" << epochs << "]..." << endl;

            cout << "      b0=" << b0
                 << ", b1=" << b1
                 << ", b2=" << b2
                 << endl;
        }

    }


    // Input b0, b1, and b2 into DSVector that's being returned
    trueParameters[0] = b0;
    trueParameters[1] = b1;
    trueParameters[2] = b2;


    return trueParameters;

}

/*
 * The training_accuracy() function outputs how well our logistic regression model predicts the sentiments
 * of our training data.
 *
 * params
 *      DSVector<double> parameters : logistic regression parameters
 *      DSVector<DSVector<DSString>> data : the numerical representationm of training data
 *      DSVector<DSString> sentiments : a DSVector of the true training sentiments
 */
double Twitter::training_accuracy(DSVector<double> parameters,
                                  DSVector<DSVector<double>> X,
                                  DSVector<DSString> strSentiments)
{
    // Input actual numeric solutions into the y DSVector
    DSVector<double> y;
    for (int i = 0; i < strSentiments.size(); ++i) {
        if (strSentiments[i] == "4")
            y.push_back(1.0);
        else if (strSentiments[i] == "0")
            y.push_back(0.0);
        else
            throw runtime_error("Sentiment element is neither positive nor negative in Twitter::gradient_descent()");
    }

    int correctNum = 0;
    int total = strSentiments.size();

    // Increment correct predictions
    for (int i = 0; i < X.size(); ++i) {
        double p = parameters[0]
                   + (parameters[1] * X[i][1])
                   + (parameters[2] * X[i][2]);
        double y_hat = sigmoid(p);
        if (abs(y_hat - y[i]) <= 0.5)
            correctNum++;
    }

    double percentAccuracy = 100 * (double(correctNum) / double(total));

    return percentAccuracy;

}

/*
 * The create_ID_list() function generates a list of our testing IDs
 *
 * params
 *      Dataframe df : denotes organized DSString testing data
 *
 * @RETURN a DSVector<DSString> of all the testing data IDs for each tweet
 */
DSVector<DSString> Twitter::create_ID_list(DataFrame df) {
    DSVector<DSString> IDs;

    if (df[0][1] == "id")
        for (int i = 1; i < df.size(); ++i)
            IDs.push_back(df[i][1]);
    else
        throw runtime_error("create_ID_list() in Twitter class failed! Not analyzing sentiment column!");

    return IDs;
}

/*
 * The testing_accuracy() function checks the true testing accuracy of our
 * logistic regression model
 *
 * params
 *      DSVector<double> parameters : the parameters in our dataset
 *      DSVector<DSVector<double>> data : numerical data
 *      DSVector<DSString> semtimemnts : denotes true sentiments of testing data
 */
double Twitter::testing_accuracy(DSVector<double> parameters,
                                 DSVector<DSVector<double>> X,
                                 DSVector<DSString> strSentiments,
                                 DSVector<DSString> IDs) {
    // Input actual numeric solutions into the y DSVector
    DSVector<double> y;
    for (int i = 0; i < strSentiments.size(); ++i) {
        if (strSentiments[i] == "4")
            y.push_back(1.0);
        else if (strSentiments[i] == "0")
            y.push_back(0.0);
        else
            throw runtime_error("Sentiment element is neither positive nor negative in Twitter::gradient_descent()");
    }

    int correctNum = 0;
    int total = y.size();

    DSVector<int> anomalyIncides;

    DSVector<DSString> predictions;
    // Increment correct predictions
    for (int i = 0; i < X.size(); ++i) {
        double p = parameters[0]
                   + (parameters[1] * X[i][1])
                   + (parameters[2] * X[i][2]);
        double y_hat = sigmoid(p);
        if (abs(y_hat - y[i]) <= 0.5) {
            correctNum++;
            if (y[i] == 1)
                predictions.push_back("4");
            else if (y[i] == 0)
                predictions.push_back("0");
        }
        else {
            // Keep a log of all incides where incorrect predictions occur
            anomalyIncides.push_back(i);
            if (y[i] == 1)
                predictions.push_back("0");
            else if (y[i] == 0)
                predictions.push_back("4");
        }
    }

    double percentAccuracy = 100 * (double(correctNum) / double(total));


    // Identify anomaly cases and assign these cases to global variables
    DSVector<DSString> anomalyPredictions;
    DSVector<DSString> anomalyIDs;
    for (const auto i : anomalyIncides)
        anomalyIDs.push_back(IDs[i]);

    // Push these values to Twitter object's private variable
    setIncorrectIndices(anomalyIncides);
    setTestPredictions(predictions);
    setTestIDs(IDs);


    return percentAccuracy;
}

/*
 * The train() function calls the correct methods needed to train our model.
 *
 * params
 *      DSString trainingFile : reads in the training set file
 */
void Twitter::train(DSString trainingFile) {
    cout << "Training Data..." << endl;

    // Read in the file
    DataFrame df = read_tweets(trainingFile);

    // Clean up the tweets in the file
    DSVector<DSVector<DSString>> cleanedTweets = cleaned_tweets(df);

    // Obtain the sentiments from the training set into a 1D DSVector
    DSVector<DSString> sentimentLabel = sentiment_label(df);

    // Assign a dictionary of all words and their qualities to a private variable
    setTheDictionary( dictionary(cleanedTweets, sentimentLabel) );

    // Calculate a matrix with all the training data represented quantitatively
    DSVector<DSVector<double>> numericalData = numerical_data(getTheDictionary(), cleanedTweets);
    //DSVector<DSVector<double>> standardizedData = standardize_data(numericalData);

    // Assign Logistic Regression parameters to a private DSVector
    setParameters( gradient_descent(numericalData, sentimentLabel) );

    // Assign the training accuracy to a private variable
    setTrainingAccuracy( training_accuracy(getParameters(), numericalData, sentimentLabel) );

    // Output finishing message
    cout << "   Finished Training!!!" << endl
         << "      Logistic Regression Parameters:" << endl
         << "         b0 = " << getParameters()[0] << endl
         << "         b1 = " << getParameters()[1] << endl
         << "         b2 = " << getParameters()[2] << endl
         << "   Training Accuracy: " << getTrainingAccuracy() << "%" << endl;

}

/*
 * The test() function calls the correct methods needed to test our model.
 *
 * params
 *      DSString testingFile : reads in the testing set file
 *      DSString resultsFile : reads in the results of our testing dataset from specified file
 */
void Twitter::test(DSString testingFile, DSString resultsFile) {
    cout << "Testing Data..." << endl;

    // Read in the testing file
    DataFrame df = read_tweets(testingFile);

    // Clean up the dataset of test tweets
    DSVector<DSVector<DSString>> cleanedTweets = cleaned_tweets(df);

    // Convert DSString data into quantitative data so we can test on logisitc regression
    DSVector<DSVector<double>> numericalData = numerical_data(getTheDictionary(), cleanedTweets);
    //DSVector<DSVector<double>> standardizedData = standardize_data(numericalData);

    // Read in the results file and assign sentiments to a variable
    DataFrame testingResults = read_tweets(resultsFile);
    DSVector<DSString> sentimentAnswers = sentiment_label(testingResults);
    DSVector<DSString> listOfIDs = create_ID_list(testingResults);

    // Obtain testing accuracy and assign value to private variable
    setTestingAccuracy( testing_accuracy(getParameters(), numericalData, sentimentAnswers, listOfIDs) );

    // Output completion message
    cout << "Finished Testing!!!" << endl
         << "   Testing Accuracy: " << getTestingAccuracy() << "%" << endl;

}

/*
 * The check_results() function generates two files that contain all our predictions, the testing
 * accuracy, and the results of our incorrectly checked tweets.
 *
 * params
 *      DSString predictionsTitle : the title of the file we create containing predictions
 *      DSString resultsTitle : the title of the file we create containing results
 */
void Twitter::check_results(DSString predictionsTitle, DSString resultsTitle) {
    cout << "Inserting results into 2 files..." << endl;
    ofstream predictionFile(predictionsTitle.c_str());
    ofstream resultsFile(resultsTitle.c_str());

    cout << "   Generating files [======      ][1/2]..." << endl;

    // Try, catch
    if (predictionFile.is_open() && resultsFile.is_open()) {
        predictionFile.write("Sentiment,id\n", 13);
        resultsFile << setprecision(3) << (getTestingAccuracy() / 100) << "\n";

        bool checkWrongPrediction = true;
        int errorIndex = 0;
        for (int i = 0; i < getTestPredictions().size(); ++i) {
            predictionFile << getTestPredictions()[i] << "," << getTestIDs()[i] << "\n";

            // In moments where our algorithm incorrectly predicted the tweet
            if (checkWrongPrediction) {
                if (i == getIncorrectIndices()[errorIndex]) {
                    if (getTestPredictions()[i] == "4")
                        resultsFile << "0,4," << getTestIDs()[i] << "\n";
                    else if (getTestPredictions()[i] == "0")
                        resultsFile << "4,0," << getTestIDs()[i] << "\n";
                    else
                        throw runtime_error("Private variable testPredictions contains an invalid sentiment.");

                    // Increment so we're evaluating the next error index after the loop
                    errorIndex++;

                    if (errorIndex == incorrectIndices.size())
                        checkWrongPrediction = false;
                }
            }

        }

        predictionFile.close(); // close the file after reading everything
        resultsFile.close(); // close this one as well

    }
    else {
        throw runtime_error("Input file not open!");
    }

    cout << "   Generating files [============][2/2]..." << endl
         << "Twitter Sentiment Analysis Complete!" << endl
         << "   Check " << predictionsTitle << " and " << resultsTitle << " for results!" << endl;
}