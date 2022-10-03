# C++: Twitter Sentiment Analysis with Logistic Regression
I implemented a Logistic Regression model to classify tweets as either negative or positive by implementing my own Gradient Descent algorithm from scratch. I spent approximately a month working on the C++ implementation of this project, then completed my Python implementation of the project over a 2-day period. I'm excited to share my C++ code here, because I learned so much implementing Logistic Regression from scratch using Gradient Descent and custom data structure classes. Please enjoy! 😃
## Implementation Steps 📚
### Creating my Own String and Vector Classes
Instead, of using standard template libraries for strings and vectors, this project challenged me to further understand data structures by implementing my own DSString and DSVector classes from scratch. I developed a much stronger understanding of Object-Oriented programming, assignment operators, iterators, and more by creating my own template classes.
### Reading in the Training File
While developing my own string class, I came across the obstable of reading in the file without standard template library strings. I used a stringstream to perform this task, then immediately converted the stringstream to a DSString type. From there, I used a .split() function that I incorporated into my DSString class to create a 2D-DSVector reminiscent of a Pandas DataFrame in Python to 
### Cleaning the Data
### Feature Extraction
### Training my Model
### 
## Take-Aways 🤔
### Results
Using my method of feature extraction, my Logistic Regression model predicted the testing data sentiments correctly 69.6% of the time! 
### Dissecting My Approach
While my approach was flawed, and adjustments in both my feature extraction model and my data cleaning methods could have been made to improve the accuracy . After finishing this project in C++, that's where I decided to segue over to Python and observe my results over there. 
