#include "CleanData.h"

#include "DSString.h"
#include "porter2_stemmer.h"

// TOKENIZER
//  Define a custom function to tokenize a tweet into words
// tokenizes the tweet and returns it
std::vector<DSString> CleanData::tokenizeTweets(const DSString &tweet) {
    std::vector<DSString> words;  // Assuming DSStringList is a class or data structure that can hold DSString objects
    char currentWord[tweet.length() + 1];
    size_t j = 0;

    for (size_t i = 0; i < tweet.length(); ++i) {
        char currentChar = tweet.at(i);

        // check if the current character is a word character
        if (isalnum(currentChar))  // checks if it is alpha or not
        {
            currentWord[j] = tolower(currentChar);  // Append the character to the current word
            ++j;
        } else if (j != 0 && currentChar != '\'') {
            currentWord[j] = '\0';
            words.push_back(CleanData::wordStemmer(DSString(currentWord)));  // Add the current word to the list of words
            j = 0;                                                           // reset j
        }
    }
    // add the last word if it exists (not separated by a non-word character)
    if (j != 0) {
        currentWord[j] = '\0';
        words.push_back(CleanData::wordStemmer(DSString(currentWord)));  // Add the current word to the list of words
    }
    return words;
}

// returns a stemmed version of the word
DSString CleanData::wordStemmer(DSString tokenizedWord) {
    std::string strResult(tokenizedWord.c_str());  // we have to change it to a string because porter2stemmer accepts string
    Porter2Stemmer::stem(strResult);
    return DSString(strResult);  // then we switch it back to DSString
}