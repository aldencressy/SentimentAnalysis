#include "DSToken.h"
#include "DSString.h"
using namespace std;

DSToken::DSToken() : DSString() { //Calls the DSString constructor and initializes the positive and negative counter to zero
    this->positiveCounter = 0;
    this-> negativeCounter = 0;
}

DSToken::DSToken(const char *x) : DSString(x){ //Same thing here
    this->positiveCounter = 0;
    this-> negativeCounter = 0;
}

DSToken::DSToken(const DSToken &token) : DSString(token) { //Same thing here
    this->positiveCounter = token.positiveCounter;
    this->negativeCounter = token.negativeCounter;
}

DSToken &DSToken::operator=(const DSToken &token)  {
    if (this != &token) {
       DSString::operator=(token);
        this->positiveCounter = token.positiveCounter;
        this->negativeCounter = token.negativeCounter;
    }
    return *this;
}

DSToken::~DSToken() = default; //Since DSToken does not declare anything on the heap, it just uses the DSString destructor

//Getters and setters for positive and negative counters

int DSToken::positive() {
    positiveCounter++;
}

int DSToken::negative() {
    negativeCounter--;
}


int DSToken::getPositiveCounter() {
    return positiveCounter;
}

int DSToken::getNegativeCounter() {
    return negativeCounter;
}


void DSToken::setPositive(int x) {
    positiveCounter = x;
}

void DSToken::setNegative(int x) {
    negativeCounter = x;
}