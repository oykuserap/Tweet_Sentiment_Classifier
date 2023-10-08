#include "DSString.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

/*
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project.
 *
 * Note that c-strings use `\0` as a terminator symbol
 * but your class should store its length in a member variable. Do not use c-string functions
 * from <string.h> or <cstring> other than for conversion from a c-string.
 */

DSString::DSString() {  // default constructor
    len = 0;
    data = new char[1];
    data[0] = '\0';
}

// constructor that converts a cstring to a DSString
DSString::DSString(const char *x) {
    len = std::strlen(x);
    // allocate memory for dsstring on the heap, add 1 to account for null character
    data = new char[len + 1];
    // copy the inputted cstring into data
    std::strcpy(data, x);
}

// constructor that converts a std::string
DSString::DSString(const std::string &str) {
    len = str.length();
    data = new char[len + 1];

    // Copy each character from string into char array
    for (size_t i = 0; i < len; i++) {
        data[i] = str.at(i);
    }

    // Add null terminator
    data[len] = '\0';
}

// Rule of three :copy constructor, overloaded assignment operator, destructor

// Copy constructor
DSString::DSString(const DSString &copy) {
    len = copy.len;
    data = new char[len + 1];

    // copy contents of copy into data
    for (size_t i = 0; i < len; ++i) {
        data[i] = copy.data[i];
    }

    // null-terminate
    data[len] = '\0';
}
// Destructor
DSString::~DSString() {
    // delete dynamically allocated memory
    delete[] data;
}
// assignment operator
DSString &DSString::operator=(const DSString &assign) {
    // Check for self-assignment to prevent data loss
    if (this != &assign) {
        // delete existing dynamically allocated memory
        delete[] data;

        // get length of "assign" DSString
        len = assign.len;

        // dynamically allocate memory (+1 for null) and copy contents of "assign" DSString
        data = new char[len + 1];
        // FIX manually
        std::strcpy(data, assign.data);
    }

    return *this;
}

// returns the length of the string
size_t DSString::length() const {
    return len;
}

char &DSString::operator[](size_t index) {  // returns a reference to the character at given index

    // check valid index
    if (index >= len) {
        throw std::runtime_error("ERROR: index out of range");
    }

    return data[index];
}

char DSString::at(size_t index) const {
    if (index >= len) {
        throw std::runtime_error("ERROR: index out of range");
    }

    return data[index];
}

// overloaded operator+ which appends the string in the argument to this string
DSString DSString::operator+(const DSString &add) const {
    size_t combinedLen = len + add.length() + 1;
    char *newData = new char[combinedLen];
    newData[len] = '\0';

    for (size_t i = 0; i < len; i++) {
        newData[i] = data[i];
    }
    for (size_t i = 0; i < add.length(); i++) {
        newData[len + i] = add.data[i];
    }

    return DSString(newData);
}

// Standard relational operators to compare and order strings

bool DSString::operator==(const DSString &compare) const {
    // check if DSStrings are the same size
    if (len != compare.len) {
        return false;
    }

    // compare contents of DSStrings at each index
    for (size_t i = 0; i < len; ++i) {
        if (data[i] != compare.data[i]) {
            return false;
        }
    }

    return true;  // both are equal
}

// compare current string with the new string
bool DSString::operator<(const DSString &compare) const {
    // find minimum length
    size_t minLength;
    if (len > compare.len) {
        minLength = compare.len;
    } else {
        minLength = len;
    }

    // compare characters in current and compare string one by one
    for (size_t i = 0; i < minLength; ++i) {
        if (data[i] < compare.data[i]) {
            return true;  // current string less than compare string
        } else if (data[i] > compare.data[i]) {
            return false;  // current string is not less than compare string
        }
    }

    // if all chars up to minLength are equal, compare lengths
    return (len < compare.len);
}

bool DSString::operator>(const DSString &compare) const {
    // find the minimum length
    size_t minLength;
    if (len > compare.len) {
        minLength = compare.len;
    } else {
        minLength = len;
    }
}

bool DSString::operator!=(const DSString &rhs) const {
    // check if lengths are equal
    if (len != rhs.len) {
        // if lengths are not equal, strings are not equal
        return true;
    }

    // Loop through each char and compare
    for (size_t i = 0; i < len; i++) {
        if (data[i] != rhs.data[i]) {
            // if any char is not equal we can return true
            return true;
        }
    }

    // All chars are equal
    return false;
}
/**
 * The substring method returns a new string object that contains a
 * sequence of characters from this string object.
 *
 * param start - the index of where to start
 * param numChars - the number (count) of characters to copy into
 *    the substring
 * @return a DSString object containing the requested substring
 **/

DSString DSString::substring(size_t start, size_t numChars) const {
    if (numChars > len || start > len) {
        throw std::runtime_error("ERROR: Out of range");
    }

    // allocate memory for substring
    char *subData = new char[numChars + 1];

    // copy characters from current dsstring into new substring
    for (size_t i = 0; i < numChars; ++i) {
        // assign characters to substring beginning at "start" index
        subData[i] = data[start + i];
    }

    // cstring null-termination
    subData[numChars] = '\0';

    // create new DSString for the substring
    DSString newSub(subData);

    // delete dynamically allocated memory
    delete[] subData;

    return newSub;
}

/**
 * @brief Returns a new string object with all characters in lowercase
 *
 * @return DSString
 */

DSString DSString::toLower() const {
    // copy the current DSString
    DSString lowercaseString(*this);

    for (size_t i = 0; i < lowercaseString.len; ++i) {
        // if the letter is uppercase, we add 32 to get the lowercase value(this is according to ASCII)
        if ((lowercaseString.data[i] >= 'A') && (lowercaseString.data[i] <= 'Z')) {
            lowercaseString.data[i] += 32;
        }
    }

    return lowercaseString;
}

/**
 * the c_str function returns a pointer a null-terminated c-string holding the
 * contents of this object. Since data already has a `\0`
 * at the end of the string in DSString so you can just return a pointer to data.
 **/

const char *DSString::c_str() const {
    return data;
}

bool DSString::empty() {
    return (len == 0);
}

void DSString::clear() {  // resets DSString to default form
    delete[] data;

    // set the variables up with their old values
    len = 0;
    data = new char[1];
    data[0] = '\0';
}

/**
 * Overloaded stream insertion operator to print the contents of this
 * string to the output stream in the first argument. Remember:
 * This operator needs to be implemented outside of the class as
 * a friend because it operates on the stream and not the DSString object.
 **/

//overloaded output stream operator for DSString objects
std::ostream &operator<<(std::ostream &output, const DSString &myDSString) {
    output << myDSString.data;
    return output;
}

//overloaded input stream operator for DSString objects
std::istream &operator>>(std::istream &input, DSString &add) {
    char *buffer;
    buffer = new char[16000];
    input.getline(buffer, 16000, ' ');
    add = DSString(buffer);
    delete[] buffer;
    return input;
}
