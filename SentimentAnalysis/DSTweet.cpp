//
// Created by Alden Cressy on 9/30/22.
//

#include "DSTweet.h"

DSTweet::DSTweet() : DSString() { //Calls the DSString() constructor and initializes the positive and negative counters to 0
positiveCounter = 0;
negativeCounter = 0;
}

DSTweet::DSTweet(const char *x) : DSString(x){ //Again, constructor calls the DSString() constructor, then initializes the two counters to 0
positiveCounter = 0;
negativeCounter = 0;
}

DSTweet::DSTweet(const DSTweet &x) : DSString(x) {
    this->positiveCounter = x.negativeCounter;
    this->negativeCounter = x.negativeCounter;
}

DSTweet &DSTweet::operator=(const DSTweet &tweet) {
    if (this != &tweet) {
        DSString::operator=(tweet);
        this->negativeCounter = tweet.negativeCounter;
        this->positiveCounter = tweet.positiveCounter;
    }
    return *this;
}

DSTweet::~DSTweet() = default; //Since DSTweet does not declare anything on the heap, it just uses the same destructor as DSString()

//Getters, Setters, and functions to increment the counters by 1

void DSTweet::positive() {
    positiveCounter++;
}

void DSTweet::negative() {
    negativeCounter--;
}

int DSTweet::getPositive() {
    return positiveCounter;
}

int DSTweet::getNegative() {
    return negativeCounter;
}

void DSTweet::setNeg(int x) {
    negativeCounter = x;
}

void DSTweet::setPos(int x) {
    positiveCounter = x;
}

int DSTweet::getInformation() { //This functions returns an integer which is the length of the character array that holds all the information from the sentiment, to the username
    int length = 51;
    for (int i = 51; data[i] != ','; ++i) {
        ++length;
}
    return length;
}


DSTweet DSTweet::getTweet(int start, int numChars) { //This function parses out all of the information except the actual tweet
    DSTweet newString;
    delete [] newString.data;
    newString.data = new char[500];
    int z = 0;

    for (int i = start; i < numChars; ++i) {

        if (data[i] == '\0') { break; }

        if (i == start && data[i] == ',') { continue; } //If the very first character is a comma, it will not be copied
        if (i == start + 1 && data[i] == '"') { continue; } //If the very first character is a quotation mark, it will not be copied

        if (data[i] == ' ') { //If the character is a space, it will be copied
            newString.data[z] = ' ';
            z++;
            ++newString.len; //Increments the length of newString
            continue;
        }

        if (isupper(data[i])) { //If the character is an uppercase letter
            char c = tolower(data[i]); //Converts the uppercase letter to lowercase
            newString.data[z] = c; //Copies the lowercase letter to newString
            z++;
            ++newString.len;
            continue;
        }


        if (data[i] == '_' || data[i] == '@' || data[i] == '#') { //These characters are not parsed out so my algorithm for creating the dictionary knows not to push these words back
            newString.data[z] = data[i];
            ++newString.len;
            z++;
            continue;
        }


        if (!islower(data[i])) { //If the character is anything but a lowercase letter
            if (data[i] != '\'' && data[i + 1] != ' ' && !isnumber(data[i])) { //If the character is not an apostrophe and the next character is not a space, it will be copied over
                newString.data[z] = ' ';
                ++z;
                ++newString.len;
            }
            continue; //Continues the loop and does not copy anything to newString unless the above if statement is called
        }

        else {
            newString.data[z] = data[i]; //If none of the above if statements are called, the data will be copied over to newString
            ++z;
            ++newString.len;
        }

    }

    newString.data[newString.len] = '\0'; //Since this function is working with C-strings, it sets the very last index as the null terminator
    return newString;
}

DSTweet DSTweet::ID() { //This function returns a DSTweet with the sentiment and tweet ID
    DSTweet newString;
    delete [] newString.data;
    newString.data = new char[500];
    int z = 0;
    for (int i = 0; i < 10; ++i) {
        newString.data[z] = data[i];
        ++z;
    }
    newString.data[z + 1] = '\0';
    newString.len = strlen(newString.data);
    return newString;
}

char DSTweet::at(int index) {
    return data[index];
}

DSTweet DSTweet::substring(int start, int numChars) const { //This function works exactly how std::substring() would work
    DSTweet newString;
    delete [] newString.data;
    newString.data = new char[500];
    int z = 0;
    for (int i = start; i <= numChars + start; i++) {
        newString.data[z] = this->data[i];
        z++;
        newString.len++;
        if (data[i] == '\0') {
            break;
        }
    }

    newString.len = z;
    newString.data[z] = '\0';

    return newString;

}






