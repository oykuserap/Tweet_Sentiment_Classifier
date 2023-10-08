#include "DSString.h"

#ifndef SENTIMENTFINDER_H
#define SENTIMENTFINDER_H

enum SentimentValue {
    POSITIVE = 4,
    NEGATIVE = 0,
    NEUTRAL = 2
};

class SentimentFinder {
   private:
    unsigned int posCount = 0;  // unsigned int because we want it to be positive numbers since we are keeping count
    unsigned int negCount = 0;

   public:
    SentimentFinder();  // sets posCount and negCount to zero, this is where everything starts
    SentimentFinder(SentimentValue);

    void addTrainingData(SentimentValue);  // tells what to do according to the sentiment value of the tweet
    //(0 or 4 | positive or negative)

    SentimentValue getPrediction();  // analyzing and predicting the sentiment(where the magic happens! )

    unsigned int getPosCount() { return posCount; }
    unsigned int getNegCount() { return negCount; }
};

#endif