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


### Creating my Own String and Vector Classes
Instead, of using standard template libraries for strings and vectors, this project challenged me to further understand data structures by implementing my own DSString and DSVector classes from scratch. I developed a much stronger understanding of Object-Oriented programming, assignment operators, iterators, and more by creating my own template classes.
### Reading in the Training File
While developing my own string class, I came across the obstable of reading in the file without standard template library strings. I used a stringstream to perform this task, then immediately converted the stringstream to a DSString type. From there, I used a split() function that I incorporated into my DSString class to parse through the gigantic DSString and create a 2D-DSVector reminiscent of a Pandas DataFrame in Python to store my data. 
### Cleaning the Data
Within my DSString class, I included stemming(), to_lowercase(), remove_punctuation(), and remove_repeat_chars() functions to handle the cleaning of Tweet data easily. I clean the data using these methods to ensure that my feature extraction model would fit as accurately as it possibly could to the data. For example, words like "jumps", "JUMP", "jumppp!", and "jumped" would all be equated to "jump" and be evaluated as such when put into perspective with all their other appearances in Tweets during the feature extraction process.
### Creating a "Dictionary"
I created a 1D DSVector to store Word objects, where each Word contains private variables denoting the word as a DSString and two integers denoting the number of positive and negative appearances in the training set respectively. I tried to create this "dictionary" as a C++ unordered_map, so I could achieve O(1) search instead of O(n) search, but I could not get past bugs that required hashing elements of my key to overcome.
### Feature Extraction
I developed a feature extraction method on my own to numerically represent my data. I used the positive and negative appearances stored in my dictionary for each word in the tweet to score the overall Tweet. I then created a (20,000 x 3) DSVector containing 1's in the first column, positive training set appearances for all Tweet words in the second column for each Tweet, and negative training set appearances in the third column. The runtime is flawed because it's Big-Oh notation is O(3*n^2) => O(n^2) [could have been O(n) using an unordered_map]. Regardless, my feature extraction method evaluates each Tweet based off of each word's data with respect to its positive and negative frequency within the entire training set, which is why it's so powerful.
### Training my Logistic Regression Model with Gradient Descent
I coded a Gradient Descent function from scratch that returns the estimated population parameters for our Logistic Regression model. Computing the gradient and applying it to this process was difficult, but to qualitatively describe the process, I basically coded a function that trends towards the smallest deviation in reality compared to our estimated Logistic Regression model as possible as we iterate through it. By coding this algorithm that climbs down a mathematical function denoting this deviation and finding its global minimum, we are able to return parameters that perform well at predicting positive and negative Tweet sentiments.  
### Applying my Logistic Regression Model to the Training Data
I used the same methods of reading, cleaning, and feature extracting for my testing data. I then used the logistic regression parameters which I retrieved from my Gradient Descent function to predict testing Tweet sentiments. If the Tweet prediction was above 0.5 after inputing the positive and negative Training set appearances for all the words within the Tweet, I predicted a positive sentiment, and I predicted a negative sentiment when that wasn't the case. I used this method, because the decimal in the sigmoid function represents the probability of our assuming our model features are perfect (which they are not). 
### Results
Using my method of feature extraction, my Logistic Regression model predicted the testing data sentiments correctly 69.79% of the time!
## Take-Aways 💡
While my approach had some flaws, and adjustments in both my feature extraction model and my data cleaning methods could have been made to improve the accuracy, I am very happy with my Classification model and how I implemented a machine learning model from scratch in C++. Keeping track of my variables was difficult, especially when I resorted to using several 2D-DSVectors, but I definitely strengthened my ability to visualize data and dissect 
After finishing this project in C++, that's where I decided to segue over to Python and observe my results over there. 
