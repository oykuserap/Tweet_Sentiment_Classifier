#include "SentimentFinder.h"

// default constructor
SentimentFinder::SentimentFinder() {
    posCount = 0;
    negCount = 0;
}

SentimentFinder::SentimentFinder(SentimentValue value)  // constructor that takes an initial sentiment value
{
    if (value == POSITIVE) {
        posCount = 1;
        negCount = 0;
    } else if (value == NEGATIVE) {
        posCount = 0;
        negCount = 1;
    } else {  // if an invalid value is provided, set both counts to 0.
        posCount = 0;
        negCount = 0;
    }
}

// Method to add training data for sentiment analysis
void SentimentFinder::addTrainingData(SentimentValue value) {
    if (value == POSITIVE) {
        posCount++;
    } else if (value == NEGATIVE) {
        negCount++;
    }
}

// Method to predict sentiment based on training data
SentimentValue SentimentFinder::getPrediction() {
    if (posCount == 0 && negCount == 0) {
        return NEUTRAL;
    }

    // check for the percentage of positives and negatives
    const double posPercent = (double)posCount / (posCount + negCount);
    const double negPercent = (double)negCount / (posCount + negCount);

    // determines positivity or negativity according to percentage
    if (posPercent > negPercent) {
        return POSITIVE;
    } else if (negPercent > posPercent) {
        return NEGATIVE;
    } else {
        return NEUTRAL;
    }
}
