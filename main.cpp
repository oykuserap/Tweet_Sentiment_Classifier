#include <fstream>

#include "DSString.h"           // Include your DSString header
#include "SentimentAnalyzer.h"  // Include your DSString header

int main(int argc, char** argv) {
    if(argc < 6) { return -1; }

    SentimentAnalyzer sa;
    std::ifstream trainingFile(argv[1]);        if (!trainingFile.is_open()) { throw std::invalid_argument("did not open file"); }
    std::ifstream testingFile(argv[2]);         if (!testingFile.is_open()) { throw std::invalid_argument("did not open file"); }
    std::ofstream resultsOutput(argv[4]);       if (!resultsOutput.is_open()) { throw std::invalid_argument("did not open file"); }
    std::ifstream testSentimentFile(argv[3]);   if (!testSentimentFile.is_open()) { throw std::invalid_argument("did not open file"); }
    std::ofstream accuracyFile(argv[5]);        if (!accuracyFile.is_open()) { throw std::invalid_argument("did not open file"); }
    
    sa.train(trainingFile);
    sa.analyze(testingFile);
    sa.printPredictions(resultsOutput);
    sa.evaluateAccuracy(testSentimentFile, accuracyFile);
    
    trainingFile.close(); testingFile.close(); resultsOutput.close(); testSentimentFile.close(); accuracyFile.close();
}
