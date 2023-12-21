#include "DSString.h"
#include "DSVector.h"
#include <iostream>

class DSToken : public DSString { //This class is nearly identical to DSString. In my program, a token is a single word and a DSString is a sentence or phrase
private:
    int positiveCounter;
    int negativeCounter;
public:
    DSToken();
    DSToken(const char *);
    DSToken(const DSToken &);
    ~DSToken();
    DSToken &operator=(const DSToken &);
    int positive();
    int negative();
    int getPositiveCounter();
    int getNegativeCounter();
    void setPositive(int);
    void setNegative(int);


};