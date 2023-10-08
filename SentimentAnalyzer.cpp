#include "SentimentAnalyzer.h"

#include <chrono>
#include <fstream>

#include "CleanData.h"
#include "DSString.h"
#include "SentimentFinder.h"

void SentimentAnalyzer::train(std::istream& trainingFile) {
    /**
     * read in the line one by one
     * read sentiment
     * skip irrelevant data
     * tokenize words in tweet
     * add each word in tweet to trainTokens
     */
    DSString line;
    getline(trainingFile, line);
    // the line format is : id,Date,Query,User,Tweet
    // we need to read the sentiment
    // we need to skip the first 4 to reach the tweet
    // get sentiment value
    DSString sentimentstr, id, date, query, user, tweet;
    while (getline(trainingFile, sentimentstr, ',')) {  // uses getline function to read characters from the stream, until it reaches ","
        // stores the info in sentiemtnstr
        SentimentValue sentiment;
        switch (sentimentstr[0]) {  // stoi: string to integer
            case '4':
                sentiment = POSITIVE;
                break;
            case '0':
                sentiment = NEGATIVE;
                break;
            default:
                sentiment = NEUTRAL;
                break;
        }

        // get the other values in order to reach the tweet
        getline(trainingFile, id, ',');
        getline(trainingFile, date, ',');
        getline(trainingFile, query, ',');
        getline(trainingFile, user, ',');

        // get tweet
        getline(trainingFile, tweet);

        // use the tokenizer to tokenize the tweets
        std::vector<DSString> tokens = CleanData::tokenizeTweets(tweet);
        
        for (auto& curWord : tokens) {  // loops through every word in tokens, where the current word is "curWord"
            curWord = curWord.toLower();
            if (trainTokens.find(curWord) == trainTokens.end()) {
                trainTokens.insert({curWord, SentimentFinder()});
            }

            trainTokens[curWord].addTrainingData(sentiment);
        }
    }
}

void SentimentAnalyzer::analyze(std::istream& testingFile) {
    /**
     * read in the line one by one
     * read sentiment
     * skip irrelevant data
     * tokenize words in tweet
     * add each word in tweet to trainTokens
     */
    DSString line;
    getline(testingFile, line);
    // the line format is : id,Date,Query,User,Tweet
    // we need to read the sentiment
    // we need to skip the first 4 to reach the tweet
    // get sentiment value
    DSString id, date, query, user, tweet;

    int posGuessCounter = 0;
    int negGuessCounter = 0;
    while (getline(testingFile, id, ',')) {  // uses getline function to read characters from the stream, until it reaches ","
        // get the other values in order to reach the tweet
        getline(testingFile, date, ',');
        getline(testingFile, query, ',');
        getline(testingFile, user, ',');

        // get tweet
        getline(testingFile, tweet);

        // use the tokenizer to tokenize the tweets

        std::vector<DSString> tokens = CleanData::tokenizeTweets(tweet);

        // integers to keep track of the pos and neg occurances of the word
        unsigned int sumPositive = 0;
        unsigned int sumNegative = 0;

        for (auto& curWord : tokens) {  // loops through every word in tokens, where the current word is "curWord"
            curWord = curWord.toLower();
            if (trainTokens.find(curWord) == trainTokens.end()) {
                continue;
            }
            sumPositive += trainTokens[curWord].getPosCount();
            sumNegative += trainTokens[curWord].getNegCount();
        }

        if (sumPositive >= sumNegative) {
            tweets.insert({id, POSITIVE});
            posGuessCounter++;
        } else {
            tweets.insert({id, NEGATIVE});
            negGuessCounter++;
        }
    }

    for (auto& item : tweets) {
        std::cout << item.second << ' ' << item.first << std::endl;  // to print sentiment first and id later, i do second-first
    }

    std::cout << "Positive guesses: " << posGuessCounter << std::endl;
    std::cout << "Negative guesses: " << negGuessCounter << std::endl;
}

// this functions prints the predictions output to predicted_dataset.csv
void SentimentAnalyzer::printPredictions(std::ostream& predictedData) {
    predictedData << "Sentiment"
                  << ","
                  << "id" << std::endl;
    for (auto& item : tweets) {
        predictedData << item.second << ',' << item.first << std::endl;
    }
}

// this fucntion returns he accuracy of the results by comparing it to the test_dataset_sentiment.cvs values
void SentimentAnalyzer::evaluateAccuracy(std::istream& testSentimentFile, std::ostream& resultsFile) {
    int correctGuess = 0;
    int total = 0;

    DSString testFileLine;
    DSString sentimentStr, tweetIdStr;

    SentimentValue sentiment;

    getline(testSentimentFile, testFileLine);  // to skip the first line
    while (testSentimentFile.eof() == false) {

        // split the line into sentiment and tweet id using ',' as the delimiter
        if (getline(testSentimentFile, sentimentStr, ',') && getline(testSentimentFile, tweetIdStr)) {
            SentimentValue guess = (tweets[tweetIdStr] > 0) ? POSITIVE : NEGATIVE;

            if (guess == POSITIVE && sentimentStr[0] == '4') {  // if the prediction is positive and matches the actual sentiment '4', it's a correct guess
                correctGuess++;
            } else if (guess == NEGATIVE && sentimentStr[0] == '0') {  // if the prediction is negative and matches the actual sentiment '0', it's a correct guess
                correctGuess++;
            } else {  // if the prediction is incorrect, log the actual sentiment, the wrong prediction, and the tweet ID to the resultsFile, this is to output the wrong guesses
                char wrongGuess = (guess == POSITIVE) ? '4' : '0';
                char rightAnswer = sentimentStr[0];
                resultsFile << rightAnswer << ", " << wrongGuess << ", " << tweetIdStr << std::endl;
            }

            // increment the total count to keep track of the number of predictions made.
            total++;
        }
    }
    // calculate and print accuracy in output and the resultsFile
    double accuracy = (static_cast<double>(correctGuess) / total) * 100.0;
    std::cout << "Accuracy: " << accuracy << "%" << std::endl;
    resultsFile << "Accuracy: " << accuracy << "%" << std::endl;
}
