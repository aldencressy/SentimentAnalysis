//
// Created by Alden Cressy on 9/30/22.
//

#ifndef ASSIGNMENT2_SENTIMENT_DSTWEET_H
#define ASSIGNMENT2_SENTIMENT_DSTWEET_H
#include "DSString.h"

class DSTweet : public DSString {
private:
    int positiveCounter;
    int negativeCounter;
public:

    DSTweet(); //Constructor with no parameters
    DSTweet(const char *); //Constructor with an array of charactters as a parameter
    DSTweet(const DSTweet &); //Copy constructor
    ~DSTweet(); //Destructor
    DSTweet &operator=(const DSTweet &); //Assignment operator overload
    DSTweet substring(int start, int numChars) const;
    void positive();
    void negative();
    int getPositive();
    int getNegative();
    void setNeg(int);
    void setPos(int);
    int getInformation();
    DSTweet getTweet(int, int);
    DSTweet ID();
    char at(int index);






};


#endif //ASSIGNMENT2_SENTIMENT_DSTWEET_H
