#include "DSString.h"
#include <iostream>
#include <cstring>

using namespace std;

DSString::DSString() { //Sets data to a nullptr and the length to 0
   data = nullptr;
   len = 0;
}

DSString::DSString(const char *x) {
    len = strlen(x); //Uses strlen function to calculate the length of the C-String
    data = new char[len + 1]; //dynamically allocates space for data based off of the length of the c-string. +1 is used for the null terminator
    strcpy(data, x); //strcpy function copies the c-string x to data
}

DSString::DSString(const DSString &string) { //Copy constructor copies over the data from string
    this->len = string.len;
    this->data = new char[len + 1];
    strcpy(this->data, string.data);
}

DSString & DSString::operator=(const DSString & string) { //Copy assignment operator
    if (this != &string) {
        delete [] data;
        len = string.len;
        this->data = new char[len + 1];
        strcpy(data, string.data); //copies each index
    }
    return *this;
}


DSString::~DSString() { delete [] data; } //Destructor deletes data because it is on the heap

std::ostream &operator<<(std::ostream &out, const DSString &x) { //Overloads the << operator so I could use cout when testing my program
    out << x.data;
    return out;
}


bool DSString::operator==(const DSString &x) const { //Determines if two DSStrings are equal to each other
    if (this->len != x.len) { return false; }

    for (int i = 0; i < this->len; ++i) {
        if (this->data[i] != x.data[i]) { return false; }
    }

    return true;

}

bool DSString::operator<(const DSString &x) const { // Determines if one DSString length is less than the other
    if (this->len < x.len) { return true; }
    return false;
}

DSString DSString::operator+(const DSString &x) const { //This function adds two strings together. I never use it in my program
    DSString newString;
    DSString string1;
    DSString string2;
    newString.data = new char[this->len + x.len];
    string1 = this->data;
    string2 = x.data;
    data[0] = '\0';

    for (int i = 0; i < this->len; i++) {
        newString.data[i] = string1.data[i];
    }

    int z = 0;
    for (int i = this->len; i < x.len + this->len; i++) {
        newString.data[i] = string2.data[z];
        z++;
    }

    newString.len = this->len + x.len;
    return newString;
}

void DSString::clear() { //This function will completely clear out the string
    delete [] data;
    data = new char[1];
    data[0] = '\0';
    len = 0;
}

DSString DSString::substring(int start, int numChars) const { //substring function is overloaded in DSTweet
    DSString newString;
    int z = 0;
    for (int i = start; i <= numChars + start; i++) {
        newString.data[z] = this->data[i];
        z++;
        newString.len++;
        if (data[i] == '\0') {
            break;
        }

    }

    newString.len = numChars - start + 1;

    return newString;
}

const char *DSString::c_str() const {  //This function returns the DSString as a C-String
    data[len] = '\0';
    return data;
}

char DSString::operator[](int i) { //Overloads the [] operator to return the character at that index
    char x = data[i];
    return x;
}

char DSString::operator[](int i) const {
    char x = data[i];
    return x;
}


std::istream &operator>>(std::istream &in, DSString &x) { //Overloads the >> operator in case stringstream or cin needs it
    in >> x.data;
    return in;
}

int DSString::getLength() const { //Returns the length of the DSString
    return len;
}








