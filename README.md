# Twitter Sentiment Analysis with Logistic Regression using Both C++ and Python
## Overview
I implemented a Logistic Regression model to classify whether tweets have a positive or negative sentiment associated with them. I used C++ at first to understand all the data-wrangling, feature extraction, training, and testing processes using Natural Language Processing and Machine Learning. Within C++, I coded string and vector data structures from scratch to perform this task, and I modeled the Logistic Regression function by coding a Gradient Descent algorithm from scratch. Then, I used similar methods in Python to better understand the full capabilites of NLP using data visualizations and TF-IDF, so I could achieve a higher testing accuracy and understand the classification process on a deeper level. My final Python testing accuracy for correctly classifying Tweet sentiments was 76.58%, while my C++ testing accuracy was 69.79%. I spent approximately a month working on the C++ implementation of this project, then completed my Python implementation of the project over a 2-day period. Please enjoy! 😃
# C++: Twitter Sentiment Analysis with Logistic Regression
## Implementation Steps 📚
### Creating my Own String and Vector Classes
Instead, of using standard template libraries for strings and vectors, this project challenged me to further understand data structures by implementing my own DSString and DSVector classes from scratch. I developed a much stronger understanding of Object-Oriented programming, assignment operators, iterators, and more by creating my own template classes.
### Reading in the Training File
While developing my own string class, I came across the obstable of reading in the file without standard template library strings. I used a stringstream to perform this task, then immediately converted the stringstream to a DSString type. From there, I used a split() function that I incorporated into my DSString class to parse through the gigantic DSString and create a 2D-DSVector reminiscent of a Pandas DataFrame in Python to store my data. 
### Cleaning the Data
Within my DSString class, I included stemming(), to_lowercase(), remove_punctuation(), and remove_repeat_chars() functions to handle the cleaning of Tweet data easily. I clean the data using these methods to ensure that my feature extraction model would fit as accurately as it possibly could to the data. For example, words like "jumps", "JUMP", "jumppp!", and "jumped" would all be equated to "jump" and be evaluated as such when put into perspective with all their other appearances in Tweets during the feature extraction process.
### Creating a "Dictionary"
I created a 1D DSVector to store Word objects, where each Word contains private variables denoting the word as a DSString and two integers denoting the number of positive and negative appearances in the training set respectively. I tried to create this "dictionary" as a C++ unordered_map, so I could achieve O(1) search instead of O(n) search, but I could not get past bugs that required hashing elements of my key to overcome.
### Feature Extraction
I developed a feature extraction method on my own to numerically represent my data. I used the positive and negative appearances stored in my dictionary for each word in the tweet to score the overall Tweet. I then created a (20,000 x 3) DSVector containing 1's in the first column, positive training set appearances for all Tweet words in the second column for each Tweet, and negative training set appearances in the third column. The runtime is flawed because it's Big-Oh notation is O(3*n^2) => O(n^2) [could have been O(n^2) using an unordered_map]. Regardless, my feature extraction method evaluates each Tweet based off of each word's data with respect to its positive and negative frequency within the entire training set, which is why it's so powerful.
### Training my Logistic Regression Model with Gradient Descent
I coded a Gradient Descent function from scratch that returns the estimated population parameters for our Logistic Regression model. Computing the gradient and applying it to this process was difficult, but to qualitatively describe the process, I basically coded a function that trends towards the smallest deviation in reality compared to our estimated Logistic Regression model as possible as we iterate through it. By coding this algorithm that climbs down a mathematical function denoting this deviation and finding its global minimum, we are able to return parameters that perform well at predicting positive and negative Tweet sentiments.  
### Applying my Logistic Regression Model to the Training Data
I used the same methods of reading, cleaning, and feature extracting for my testing data. I then used the logistic regression parameters which I retrieved from my Gradient Descent function to predict testing Tweet sentiments. If the Tweet prediction was above 0.5 after inputing the positive and negative Training set appearances for all the words within the Tweet, I predicted a positive sentiment, and I predicted a negative sentiment when that wasn't the case. I used this method, because the decimal in the sigmoid function represents the probability of our assuming our model features are perfect (which they are not). 
### Results
Using my method of feature extraction, my Logistic Regression model predicted the testing data sentiments correctly 69.79% of the time!
## Take-Aways 💡
While my approach had some flaws, and adjustments in both my feature extraction model and my data cleaning methods could have been made to improve the accuracy, I am very happy with my Classification model and how I implemented a machine learning model from scratch in C++. Keeping track of my variables was difficult, especially when I resorted to using several 2D-DSVectors, but I definitely strengthened my ability to visualize data and dissect 
After finishing this project in C++, that's where I decided to segue over to Python and observe my results over there. 
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
### Understanding TF-IDF
TF-IDF is an alternative approach for feature extraction than the one I used in C++ and in my 1st Python implementation. In this implementation, each column in our numerical matrix of training and testing data is representative of a word in our dictionary. The TF-IDF of each word within each Tweet is then represented.  
TF-IDF is calculated using the product of two terms: TF (Term Frequency) and IDF (Inverse Document Frequency).  
  
  TF = number of times word appears in Tweet / number of words in Tweet  
  IDF = log(total tweets / (1 + number of tweets where word appears in training dataset))  
  TF-IDF = TF * IDF  
  
TF-IDF proportionally increases as the appearances of a word in a specific Tweet increases, and it proportionally decreases as the number of the word's appearances in the training set increases.  
### Results
Using the same methods for data-wrangling and Logistic Regression, we achieve a Testing Accuracy of 76.58%, which is a significant increase in comparison to our previous mode!
### Visualizing TF-IDF Logistic Regression
I'm not able to plot each individual variable, because now there are thousands of variables that all are representative of a word in the training set dictionary. However, I still am able to plot the Logistic Regression model by condensing all variables down to one calculation:
![alt text](https://github.com/ririye01/Twitter-Sentiment-Analysis-in-Cpp-vs-Python/blob/main/Python%20Sentiment%20Analysis/Classification%20Plots/TFIDF%20Testing%20Data%20Logistic%20Regression%20.png)
Even in this plot, we can see that the sentiments of positive and negative Tweets are predicted more correctly because of the TF-IDF means of feature extraction.
## Take-Aways 💡
Implementing the TF-IDF method made me aware of how powerful the method really is in the context of Natural Language Processing and Machine Learning. Additionally, by plotting decision boundaries and logistic regression models, I can better explain how classification works in general and how it specifically works in this context.

