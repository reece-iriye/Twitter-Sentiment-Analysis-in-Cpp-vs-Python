# Assignment: Don't Be Sentimental!


## Introduction
Have you ever read a tweet and thought, “Gee, what a positive outlook!” or “Wow, why so negative, friend?”  Can computers make the same determination?  They can surely try!

In Machine Learning, the task of assigning a **label** to a data item is called **classification** (putting things into different classes or categories).  The more specific name for what we’re going to do is sentiment analysis because you’re trying to determine the “sentiment” or attitude based on the words in a tweet.  The goal of the project is to build a sentiment classifier! Aren’t you excited??  ( ← That would be positive sentiment!)

You’ll be given a set of tweets called the **training data set** that are already pre-classified by humans as **positive** or **negative** based on their content.  You’ll analyze the frequency of occurrences of words in the tweets to develop a classification scheme.  Using your classification scheme, you’ll then classify another set of tweets called the **testing data set** and **predict** if each tweet has positive sentiment or negative sentiment.


## Building a Classifier
The goal in classification is to assign a class label to each element of a data set, positive or negative in our case.  Of course, we would want this done with the highest accuracy possible.  At a high level, the process to build a classifier (and many other machine learning models) has two major steps:

1. Training Phase
   - Input is a set of tweets with each tweet’s associated sentiment value.  This is the training data set.
   - Example: Assume you have 10 tweets and each is pre-classified with positive or negative sentiment.  How might you go about analyzing the words in these 10 tweets to find words more commonly associated with negative sentiment and words more commonly associated with positive sentiment?
   - The result of the training step will be one list of words that have an associated positive or negative sentiment with them depending on which type of tweet they appeared in more frequently.  Or, you might have 2 lists of words: one list is positive, one list is negative.

2. Testing Phase
   - In the testing phase, for a set of tweets called the testing data set, you predict the sentiment by using the list or lists of words extracted during the training phase.
   - Behind the scenes, you already know the sentiment of each of the tweets in the testing data set.  We’ll call this the actual sentiment or ground truth.  You then compare your predicted sentiment to the known sentiment for each of the testing tweets. Some of the predictions will be correct; some will be wrong.  The percentage correct is the accuracy, but more on this later.

## The Data
The data set we will be using in this project comes from real tweets posted around 11-12 years ago.  The original data was retrieved from Kaggle at https://www.kaggle.com/kazanova/sentiment140.  I’ve pre-processed it into the file format we are using for this project.  For more information, please see  Go, A., Bhayani, R. and Huang, L., 2009. Twitter sentiment classification using distant supervision. CS224N Project Report, Stanford, 1(2009), p.12.

**The preprocessed dataset can be accessed from is already included in the data folder in the project repo.**

## Input files
There will be 3 different input files:
* Training Data
* Testing Data Tweet (no sentiment column)
* Testing Ground Truth (id and sentiment for testing data for you to compare against).

The training data file is formatted as a comma-separated-values (CSV) file containing a list of tweets, each one on a separate line.  Each line of the data files include the following fields:
* Sentiment value (negative = 0, positive = 4, numbers in between are not used),
* the tweet id,
* the date the tweet was posted
* Query status (you can ignore this column)
* the twitter username that posted the tweet
* the text of the tweet itself

The testing data set is broken into two files:
* A CSV file containing formatted just like the training data EXCEPT no Sentiment column
* A CSV file containing tweet ID and sentiment for the testing dataset (so you can compare your predictions of sentiment to the actually sentiment ground truth)

Below are two example tweets from the training dataset:
```
4,1467811594,Mon Apr 06 22:20:03 PDT 2009,NO_QUERY,peruna_pony,"Beat TCU"
0,1467811595,Mon Apr 06 22:22:03 PDT 2009,NO_QUERY,the_frog,"Beat SMU"
```

Here is a tweet from the testing dataset:
```
1467811596,Mon Apr 06 22:20:03 PDT 2009,NO_QUERY,peruna_pony,"SMU > TCU"
```

The sentiment file for that testing tweet would be:
```
4, 1467811596
```

## Running your Program: Training and Testing

Your program should take 5 command line arguments:
1. training data set filename - the file with the training tweets
2. testing data set filename - tweets that your program will classify
3. testing data set sentiment filename - the file with the classifications for the testing tweet data
4. classifier results file name - see Output Files section below
5. classifier accuracy and errors file name - see Output Files section below

Example:
```
./classifier.out <train data> <test data> <test sentiment> <results> <accuracy/errors>
```

### Output Files
Your program should produce two output files. The first file should contain your classifier's
results for all tweets in the testing dataset in the same format as the sentiment file:
```
4, 1467811596
...
```

The second file should be organized as follows:
* The first line of the output file will contain the accuracy, a single floating point number with exactly 3 decimal places of precision.  See the section “How good is your classifier” below to understand Accuracy.
* The remaining lines of the file will contain for each tweet that your algorithm incorrectly classified your prediction,
the ground truth and the Tweet ID. This could be useful information as you tweak your algorithm to increase efficiency.

Example of the testing data tweet classifications file:
```
0.500
4, 1, 2323232323
1, 3, 1132553423
...
```

## Implementation Requirements

### Structure

Clearly separate training from testing in your code. Your main function could look like this pseudo code:

```cpp
int main()
{
   myModelClass model;
   
   model.train(args);

   model.predict(args);
   model.evaluatePredictions(args);

   return 0;
}
```

### DSString and DSVector Classes
You must implement your own custom string class (`DSString`) as part of this project.  You may not use the STL string class or any other available string class from the Internet.  Additionally, you may NOT use c-strings (null-terminated character arrays) directly.

Your DSString class can use the [DSvector class](https://github.com/mhahsler/CS2341/tree/main/Chapter3_Lists_etc/DSVector) we have introduced in this course.

A good way to do this is to publicly inherit `DSVector` templated for `char` and add the needed 
operators and member functions.

```cpp
class DSString: public DSVector<char>
{
// add code.
};
```

There is a `DSString.h` file in the template repo that you may use as a guidepost for your `DSString` class. The only exception here is when you’re reading from or writing to a file.  You may temporarily use a char[] array/buffer for this.

You need to use `DSVector` to store `DSString` objects and counters. You can use the STL algorithms like `std::sort` and [`std::find`](https://en.cppreference.com/w/cpp/algorithm/find)
or you can implement your own functions.
Make sure you have the necessary operators with the appropriate `const` versions overloaded in `DSString` so STL algorithms work.

While there are implementations of advanced text classifiers available, do not use them for this project, but rather implement your own simple strategy that counts words appearing in positive and in negative tweets and used 
these counts to create a list of words that more frequent in positive tweets and words that are more frequent in negative tweets. Write comments in your code that explains how you do this. 
Hint: You probably should implement a subclass of `DSString` that adds a counter to the string.

You may be inclined to skip the learning and find lists of positive words and/or negative words on the internet and simply count the occurrences of those words.  However, this is not allowed in this assignment.

## Coding Style
We will be looking for simple, elegant, well-designed solutions to this problem. Please do not try to “wow” us with your knowledge of random, esoteric programming practices.

* File input and output: It is so important to be able to read from and write to data files.     
  Think about some software program that doesn't use files...
* Proper use of command-line arguments.
* Minimal amount of code in the driver method (main, in the case of C++).
* Organize your code in functions and classes with clear purposes
  to make it easier to read and debug. Remember: A function should do **only** one thing!
* Just the right amount of comments in just the right places.
* Proper memory management, including following the rule of 3 (or 5).

_Note:_ You will probably find yourself rewriting parts of your code several times to make it 
more flexible. This is called **refactoring** and is a good thing! 


## How Good is Your Classifier?
Training and testing of a classification algorithm is an iterative process.  You’ll develop a training algorithm, test it, evaluate its performance, tweak the algo, retrain, retest, etc.  How do you know how good your classifier is after each development iteration, though?  We will use accuracy as the metric for evaluation.

$$\text{Accuracy} = \frac{(\text{total number of correctly classified tweets from test dataset})}{(\text{total number of tweets in the test data set})}  $$ 

Why should you be interested in this?  The TAs will take your final solutions and classify a set of tweets that your algorithm has never seen.  They will calculate the accuracies (as defined above) for each submission.  If your submission achieves 72.000% accuracy or higher, you will receive 10 bonus points on the project.

## Ways to Improve Accuracy

### Stemming
Happy, happier, and happiest all come from the same root word of happy. Finding a common word stem is called [stemming.](https://en.wikipedia.org/wiki/Stemming).  You might explore the use of a stemming library to help get to the root word.
Words that appear frequently in both positive and negative tweets are useless for determining sentiment. You can look for a C++ stemming library.

### Stop words
You may look into using [stop words](https://en.wikipedia.org/wiki/Stop_word).

### Character Encoding
Some tweets might have interesting characters in them that aren’t part of the ASCII character set.  You might look into [character encoding](https://www.joelonsoftware.com/2003/10/08/the-absolute-minimum-every-software-developer-absolutely-positively-must-know-about-unicode-and-character-sets-no-excuses/) and the `wchar_t` data type (instead of `char`) if this becomes a problem.

### Converting Counts into Probabilities

[Naive Bayes classifiers](https://en.wikipedia.org/wiki/Naive_Bayes_classifier) are a family of simple "probabilistic classifiers" based on applying Bayes' theorem. You can try to implement this strategy (this is very advanced and probably not fun using the data structures we have learned so far).

## Time Line 

You have about four weeks to complete the assignment. Start right away! **The lab TA will expect that you already have most of that week's work completed. Come with prepared questions and
be prepared to answer the TA's questions about your code.**

* Week 1: DSString Class and a method to store counters for strings. You should be able
  to represent a set of words with counts. Test with `valgrind` to make sure you do not have 
  a memory leak. 
* Week 2: Training + adapting the string counter. Break text into words and count them. You    
  should have lists with positive and negative words.  
* Week 3: Classification and accuracy calculation.
* Week 4: Cleaning up code. Improving the documentation comments. Answering the questions below.

## Answers

Complete this section and commit your changes. Keep your answers short and precise.

1. How do you classify a new tweet? Give a short description of the main steps.

    > My clasification algorithm is a little complex, because I train a logistic regression model using gradient descent. I train this model using the specific equation that I got from the internet, where each parameter is multiplied by the learning rate (alpha) times the model gradient. b0 represents the starting parameter when x1 and x2 equal 0, while b1 represents the rate of change as the sum of positive appearances of words from the training set (x1) increases by 1 and b2 represents the rate of change as the sum of negative appearances of words from the training set (x2) increases by 1. I set theta = b0 + (b1)(x1) + (b2)(x2), then input it into a sigmoid function (1/(1+e^(-theta))) to determine the probability that the tweet is positive. I then classify the tweet as positive if its resulting sigmoid function is greater than 0.5, and negative otherwise. The method is imperfect, but that may be because of stemming problems, or maybe because I could be analyzing better parameters in this logisitc regression model. 

2. What is the time complexity of your training implementation (Big-Oh notation)? Explain why.

   > Training implementation includes dictionary(), numerical_data(), and gradient_descent(). Time complexity for dictionary() is O(m x n) (m = tweet word count {variable}; n = number of tweets {constant}). Time complexity for numerical_data() is O(m x n x p), where p is the total words in each tweet and the same m and n from dictionary(). Time complexity for gradient_descent() is O(n x q), where n is the same tweet count and q is the specified number of iterations (epochs=9000) I chose for the algorithm to loop through for gradient descent. I did not include any of the reading and initial language cleaning into this Big-Oh notation calculation. Therefore, training implementation Big-Oh notation is O(m x n x p) due to numerical_data() having the highest runtime complexity out of all the other functions involved in training.

3. What is the time complexity of your classification implementation (Big-Oh notation)? Explain why.

   > The main functions used for the actual classification implementation are numerical_data() and testing_accuracy(). Like I said above, numerical_data() has a Big-Oh notation of O(m x n x p). testing_accuracy(), however, has a runtime complexity of O(n). Therefore, classification implementation Big-Oh notation is O(m x n x p) due to numerical_data() having the highest runtime complexity out of all the other functions involved in training. 

4. How do you know that you use proper memory management? That is that you do not have
   a memory leak?

   > I rarely declare anything on the heap, which makes it almost certain that I used proper memory management. Memory management problems didn't occur in my DSString class at all for the most part, because my DSString was inherited from DSVector. The only spot where I do actually have some memory management concerns is in my c_str() function, but even then I think it's alright because it's hardly ever used except for ensuring I can use file title names. 

5. What was the most challenging part of the assignment?

   > The most challenging part of this assignment was definitely implementing the 2D DSVectors. I am used to visualizing 2D arrays because I am a math major and I see a lot of high-dimensiom matrices, but even then, using these 2D DSVectors and keeping track of them was really difficult for me in the data wrangling, training, and testing processes. I did, however, improve tremendously on my ability to visualize and store data in this 2D manner, and it helped me realize a lot about how data structures are used and implemented in C++, and it also helped me understand numpy arrays and pandas dataframes in Python a lot more. 

## Grading Rubric

|                             | Points Possible | Points Awarded |
| :------------------         | --------------: | -------------: |
| DSString Class              | 20              |                |
| Training Algo (+ counters)  | 25              |                |
| Classification Algo         | 20              |                |
| Proper Memory Management    | 10              |                |
| Formatting, Comments, etc.  | 10              |                |
| Proper use of GitHub        |  5              |                |
| Answers to questions        | 10              |                |
| Accuracy/Improvements Bonus | +10             |                |











