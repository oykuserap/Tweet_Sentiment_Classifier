#include "DSString.h"
#include <iostream>
#include <vector>
#include <sstream>

#ifndef CLEANDATA_H
#define CLEANDATA_H

namespace CleanData
{
    std::vector<DSString> tokenizeTweets(const DSString& tweets); // tokenizes the tweet and returns it
    DSString wordStemmer(DSString tokenizedWord);                 // returns a stemmed version of the word
};

#endif