# Python: Twitter Sentiment Analysis with Logistic Regression
## Overview
In C++ implemented a Logistic Regression model using Gradient Descent to classify whether tweets have a positive or negative sentiment associated with them. I used C++ at first to understand all the data-wrangling, feature extraction, training, and testing processes using Natural Language Processing and Machine Learning. Then, I used similar methods in Python to better understand the full capabilites of NLP using data visualizations and TF-IDF (Term Frequency-Inverse Document Frequency), After implementing the same methods in Python, I achieved a higher testing accuracy and gained the ability to graphically understand the classification process on a deeper level.
## Implementation Steps 📚
### Preprocess Tweets in Our Training Set
After reading in the training set using Pandas, I cleaned the Tweets by doing the following:
1. Removing hyperlinks, punctuation, and hashtags
2. Transforming each Tweet into a list of its individual words
3. Converting each word to lower case
4. Deleting stop words
5. Stemming to equate words like "eat", "eats", and "eating" all to "eat"
### Created Positive and Negative WordCloud Plots
I used the WordCloud library to plot two images. The first image contains words that tend to pop up in positive Tweets with each word scaled larger based on its frequency within the entire training set. The other image performs the same task but with negative words instead.
![alt text](https://github.com/ririye01/Twitter-Sentiment-Analysis-in-Cpp-vs-Python/blob/main/Python%20Sentiment%20Analysis/Classification%20Plots/Positive%20v%20Negative%20WordCloud.png)  


### Feature Extraction
Create a (20,000 x 3) matrix that translates Tweets to measurable, quantifiable data in a 2D matrix where the first column is filled with 1's, the second column is filled with total positive appearances for each word within the training set, and the third column denotes the total negative appearances for each word. Plotting positive appearances by negative appearances, we get the following graph:
![alt text](https://github.com/ririye01/Twitter-Sentiment-Analysis-in-Cpp-vs-Python/blob/main/Python%20Sentiment%20Analysis/Classification%20Plots/Testing%20Data%20Plot.png)  

### Generate Logistic Regression Parameters using Scikit-Learn
Using scikit-learn to train our Logistic Regression model and testing it on the training data, we get a 68.55% accuracy, which is really similar to the percentage accuracy on my C++ implementation of Logistic Regression.
### Visualizing Logistic Regression
By fitting a Logistic Regression plot to our previous training data graph, we get a decision boundary that divides predictions into sections of negative predictions and positive predictions.  

![alt text](https://github.com/ririye01/Twitter-Sentiment-Analysis-in-Cpp-vs-Python/blob/main/Python%20Sentiment%20Analysis/Classification%20Plots/Training%20Data%20Decision%20Boundary%20Prediction.png)  

Visualizing our Testing Data now, we can apply the exact same decision boundary using our Logistic Regression plot. 
![alt text](https://github.com/ririye01/Twitter-Sentiment-Analysis-in-Cpp-vs-Python/blob/main/Python%20Sentiment%20Analysis/Classification%20Plots/Testing%20Data%20Plot.png)
![alt text](https://github.com/ririye01/Twitter-Sentiment-Analysis-in-Cpp-vs-Python/blob/main/Python%20Sentiment%20Analysis/Classification%20Plots/Testing%20Data%20Decision%20Boundary%20Prediction.png)  

Additionally, by plotting b0 + b1(Positive Appearances) + b2(Negative Appearances) by the results within a Logistic Regression function, we obtain the following plot, which details exactly how our Logistic Regression model was fitted, how the decision boundary impacts predictions, and how our model predicts some Tweets incorrectly:
![alt text](https://github.com/ririye01/Twitter-Sentiment-Analysis-in-Cpp-vs-Python/blob/main/Python%20Sentiment%20Analysis/Classification%20Plots/Testing%20Data%20Logistic%20Regression.png)  

## Alternative Method: TF-IDF (Term Frequency-Inverse Document Frequency) 📚
TF-IDF is an alternative approach for feature extraction than the one I used in C++ and in my 1st Python implementation. In this implementation, each column in our numerical matrix of training and testing data is representative of a word in our dictionary. The TF-IDF of each word within each Tweet is then represented.  
TF-IDF is calculated using the product of two terms: TF (Term Frequency) and IDF (Inverse Document Frequency).  
  
  TF = number of times word appears in Tweet / number of words in Tweet  
  IDF = log(total tweets / (1 + number of tweets where word appears in training dataset))  
  TF-IDF = TF * IDF  
  
TF-IDF proportionally increases as the appearances of a word in a specific Tweet increases, and it proportionally decreases as the number of the word's appearances in the training set increases.  
### Results
Using the same methods for data-wrangling and Logistic Regression, we achieve an accuracy

## Take-Aways 💡
Implementing the TF-IDF method made me aware of how powerful it is in 
