
#include <iostream>

#include "DSString.h"
#include "Twitter.h"

using namespace std;

// Major source for helping me map out this sentiment analysis journey:
// https://medium.com/nerd-for-tech/twitter-sentiment-analysis-using-logistic-regression-ff9944982c67

int main(int argc, char** argv) {
    DSString trainingFile = argv[1];
    DSString testingFile = argv[2];
    DSString resultsFile = argv[3];
    DSString predictionsTitle = argv[4];
    DSString resultsTitle = argv[5];

    Twitter sentimentAnalysis;
    sentimentAnalysis.train(trainingFile);
    sentimentAnalysis.test(testingFile, resultsFile);
    sentimentAnalysis.check_results(predictionsTitle, resultsTitle);


    return 0;
}
