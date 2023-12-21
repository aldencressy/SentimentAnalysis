#ifndef ASSIGNMENT2_SENTIMENT_TWEETS_H
#define ASSIGNMENT2_SENTIMENT_TWEETS_H
#include "DSString.h"
#include "DSVector.h"
#include "DSToken.h"

class Tweets {
private:
DSVector<DSToken> dictionary;

public:
    void train(DSString);
    void test(DSString, DSString, DSString, DSString);
};


#endif