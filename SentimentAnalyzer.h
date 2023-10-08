#include "DSString.h"
#include "SentimentFinder.h"
#include "CleanData.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <map>

#ifndef SENTIMENTANALYZER_H
#define SENTIMENTANALYZER_H

class SentimentAnalyzer
{

private:
    std::map<DSString,SentimentFinder> trainTokens; //tokenized string and function to assign the sentiments
    size_t trainingCount; // total number of tokens that are read in
    std::map<DSString,int> tweets; //tweet ID, predicted sentiment

    // std::vector<DSString> tokenizeTweets(DSString tweets);//returns list of tokenized words
    // DSString wordStemmer(DSString stemmedTweets);//stems words

public:
    void train(std::istream&); //train the data with the provided file, build biases for words
    void analyze(std::istream&);// analyze the read file, make guesses on test tweets
    void printPredictions(std::ostream &);
    void evaluateAccuracy(std::istream&, std::ostream&);
};

#endif