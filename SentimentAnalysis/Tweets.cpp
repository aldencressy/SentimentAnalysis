#include "Tweets.h"
#include "DSTweet.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
using namespace std;

void Tweets::train(DSString fileName) {
    ifstream file;
    ifstream file2;
    file.open(fileName.c_str());
    file2.open("data/stop_words_english.txt");

    if (!file.is_open()) {
        cout << "file is not open!" << endl;
        return;
    }

    if (!file2.is_open()) {
        cout << "file is not open!" << endl;
        return;
    }

    DSVector<DSTweet> positiveTweets;
    DSVector<DSTweet> negativeTweets;
    DSVector<DSToken> stopWords;
    char * input = new char[500]; //This is so I can use the file.getline() function

    file.getline(input, 500);
    while (file.getline(input, 500)) {
        DSTweet newTweet(input); //Creates a new DSTweet with char * input as a parameter
        int len1 = newTweet.getInformation();
        int len2 = newTweet.getLength();
        if (newTweet[0] == '0') { negativeTweets.push_back(newTweet.getTweet(len1, len2));} //If the tweet is negative, pushes back the parsed tweet into the negativeTweet vector
        if (newTweet[0] == '4') { positiveTweets.push_back(newTweet.getTweet(len1, len2)); } //If the tweet is positive, pushes back the parsed tweet into the negativeTweet vector
    }

    while(file2 >> input) {
        DSToken token(input);
        stopWords.push_back(token);
    }


    file.close();

    for (const auto &i: positiveTweets) { //Range based for loop iterates through positiveTweets vector.
        stringstream ss (i.c_str()); //Stringstream library used to parse the tweet into individual words
        while (ss >> input) {
            DSToken token(input); //Creates a new DSToken with char * input as a parameter
            if (token[0] == '@' || token[0] == '#') { continue; } //If the word is a username, hashtag, or less than 3 characters long, it will not be pushed back into the dictionary vector
            if (token.getLength() < 3) { continue; }
            auto foundStopWord = std::find(stopWords.begin(), stopWords.end(), token);
            if (foundStopWord != stopWords.end()) { continue; } //If the word is a stop word, it will not be pushed back into the vector
            auto foundNegative = std::find(dictionary.begin(), dictionary.end(), token);//STD algorithm used to determine if the word is already in the vector. If it is, it will not be pushed back again.
            if (foundNegative != dictionary.end()) { continue; }
            dictionary.push_back(token); //If none of the above if statements are called, the word will be pushed back into the dictionary vector.
        }
    }

    for (const auto &i: negativeTweets) { //Exact same thing as above except with the negativeTweets vector.
        stringstream ss(i.c_str());
        while (ss >> input) {
            DSToken token (input);
            if (token[0] == '@' || token[0] == '#') { continue; }
            if (token.getLength() < 3) { continue; }
            auto foundStopWord = std::find(stopWords.begin(), stopWords.end(), token);
            if (foundStopWord != stopWords.end()) { continue; }
            auto foundPositive = std::find(dictionary.begin(), dictionary.end(), token);
            if (foundPositive != dictionary.end()) { continue; }
            dictionary.push_back(token);
        }
    }


    for (auto &i: negativeTweets) { //Triple for loop used to classify each of the negative words in dictionary
        stringstream ss (i.c_str());
        while (ss >> input) { //Takes all the words in negativeTweets and compares them to the words in dictionary
            DSToken token(input);
            for (auto &j : dictionary) {
                if (j == token) {
                    j.negative(); //This is where the tokenization occurs. j.negative() increments the negative counter for the word by -1
                }
            }
        }
    }

    for (auto &i: positiveTweets) { //Exact same thing as above except for positive words
        stringstream ss (i.c_str());
        while (ss >> input) {
            DSToken token(input);
            for (auto &j : dictionary) {
                if (j == token) {
                    j.positive(); //Increments the words positiveCounter by +1
                }
            }
        }
    }

delete [] input; //Deletes char * input because it is on the heap

}

void Tweets::test(DSString testingFile, DSString testingFileSentiment, DSString accuracy_results, DSString classify_results) {
    DSVector<DSTweet> newTweets;
    DSVector<DSTweet> tweetID;
    DSVector<DSTweet>::iterator ptr; //This will be used to iterate through the tweetID vector later
    double accuracy = 0;
    char * input = new char[500];

    ifstream file;
    file.open(testingFile.c_str());
    ofstream file2(classify_results.c_str(), ios::out); //ios::out used to make sure the file is cleared everytime before writing to it
    ofstream file3(accuracy_results.c_str(), ios::out);

    if (!file.is_open()) {
        cout << "File is not open!" << endl;
        return;
    }

    if (!file2.is_open()) {
        cout << "File is not open!" << endl;
        return;
    }

    file.getline(input, 500);
    while (file.getline(input, 500)) { //This while loop pushes back all the tweets in the test dataset to a vector
        DSTweet newTweet(input);
        int len1 = newTweet.getInformation();
        int len2 = newTweet.getLength();
        newTweets.push_back(newTweet.getTweet(len1, len2));
    }

    file.close();
    file.open(testingFileSentiment.c_str());

    if (!file.is_open()) {
        cout << "File is not open!" << endl;
        return;
    }

    file.getline(input, 500);
    while (file.getline(input, 500)) { //This while loop pushes back all the ID's of the tweets in the newTweet vector.
        DSTweet newTweet(input);
        tweetID.push_back(newTweet.ID());
    }

    file.close();
    ptr = tweetID.begin(); //Sets the iterator to point to the beginning of the tweetID vector
    file3.seekp(ios::beg + 6); //Found this function online, it just changes which line the file is outputting to.

    for (auto &i: newTweets) {
        stringstream ss(i.c_str());
        while (ss >> input) { //Parses out each individual word in the newTweets vector
            DSToken token(input);
            if (token[0] == '@' || token[0] == '#' || token.getLength() < 3) { continue; } //If the word is a username, hashtag, or less than 3 characters, it will not be compared to the words in dictionary
            for (auto &j: dictionary) {
                //i is for the entire tweet, j is for the individual word in dictionary
                if (token == j) { //If a word in the newTweets vector equals a word in dictionary

                    if (j.getPositiveCounter() + j.getNegativeCounter() > 0) {  //The word is positive

                        //Depending on how "positive" the word is, the positiveCounter for the tweet itself is incremented

                        for (int k = 0; k <= j.getPositiveCounter(); ++k) {
                            i.positive();
                        }

                    }


                    if (j.getPositiveCounter() + j.getNegativeCounter() < 0) { //The word is negative

                        //The same algorithm for incrementing the positiveCounter for the tweet itself is used here for the negativeCounter

                        for (int k = j.getNegativeCounter(); k <= 0; ++k) {
                            i.negative();
                        }
                    }
                    break;
                } //(if token ==j)

            } // for (auto&j: dictionary)

        } //while (ss >> token)

        if (ptr->c_str()[0] == '0') { //The tweet is actually negative
            if (i.getPositive() + i.getNegative() > 0) { //Algorithm classified the tweet as positive
                file2 << "4, ";
                for (int j = 2; j < 10; ++j) {
                    file2 << ptr->c_str()[j]; //Outputs the ID of the tweet to the file
                }
                file2 << endl;

                file3 << "4, 0, ";
                for (int j = 2; j < 10; ++j) { //Since the tweet was incorrectly classified, it will output it to the file displaying all the incorrectly classified tweets
                    file3 << ptr->c_str()[j];
                }
                file3 << endl;
            }

            if (i.getPositive() + i.getNegative() < 0) { //Algorithm classifies the tweet as negative
                file2 << "0, ";
                for (int j = 2; j < 10; ++j) {
                    file2 << ptr->c_str()[j];
                }
                file2 << endl;
                ++accuracy; //Since the algorithm classified the tweet correctly, it will increment the accuracy variable
            }

            if (i.getPositive() + i.getNegative() == 0) {//Algorithm classified the tweet as neutral, meaning the negativeCounter and positiveCounter are the same
                //I have neutral tweets automatically being classified as positive, so this algorithm will automatically mark all neutral tweets as incorrectly classified
                file2 << "4, ";
                for (int j = 2; j < 10; ++j) {
                    file2 << ptr->c_str()[j];
                }
                file2 << endl;

                file3 << "4, 0, ";
                for (int j = 2; j < 10; ++j) {
                    file3 << ptr->c_str()[j];
                }
                file3 << endl;
            }


        } //if (ptr->c_str()[0] == '0')

        if (ptr->c_str()[0] == '4') { //Tweet is actually positive
            if (i.getPositive() + i.getNegative() > 0) { //Algorithm classifies the tweet as positive
                file2 << "4, ";
                for (int j = 2; j < 10; ++j) {
                    file2 << ptr->c_str()[j];
                }
                file2 << endl;
                ++accuracy;
            }

            if (i.getPositive() + i.getNegative() < 0) { //Algorithm classifies the tweet as negative
                file2 << "0, ";
                for (int j = 2; j < 10; ++j) {
                    file2 << ptr->c_str()[j];
                }
                file2 << endl;

                file3 << "0, 4, ";

                for (int j = 2; j < 10; ++j) {
                    file3 << ptr->c_str()[j];
                }
                file3 << endl;
            }

            if (i.getPositive() + i.getNegative() == 0) { //Algorithm classifies the tweet as neutral
                //This algorithm automatically marks all neutral tweets as correct, and increments the accuracy variable

                file2 << "4, ";
                for (int j = 2; j < 10; ++j) {
                    file2 << ptr->c_str()[j];
                }
                file2 << endl;
                ++accuracy; //Classifies all neutral tweets as positive for the sake of accuracy
            }

        } //if (ptr->c_str()[0] == '4')

        ++ptr; //Points to the next element in the tweetID vector. The iterator increments evenly with the newTweets vector

    } //for (auto &i: newTweets)

    file3.seekp(ios::beg); //Outputs to the first line in the file, the directions said the accuracy needs to be on the first line

    file3 << setprecision(3) << accuracy/newTweets.size() << endl; //Simple equation converts the accuracy to a percentage.

    file2.close();
    file3.close();

    delete [] input; //input was declared on the heap

}