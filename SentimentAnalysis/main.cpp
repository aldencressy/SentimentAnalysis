#include <iostream>
#include "DSVector.h"
#include "DSString.h"
#include <iostream>
#include <stdexcept>
#include "Tweets.h"

using namespace std;

int main(int argc, char **argv)
{
//For command line arguments
DSString trainingFile = argv[1];
DSString testingFile = argv[2];
DSString testingFileSentiment = argv[3];
DSString classify_results = argv[4];
DSString accuracy_results = argv[5];

Tweets twitter;
twitter.train(trainingFile);
twitter.test(testingFile, testingFileSentiment, accuracy_results, classify_results);

    return 0;
}
