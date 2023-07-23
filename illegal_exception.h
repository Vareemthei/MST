#ifndef ILLEGAL_EXCEPTION_H
#define ILLEGAL_EXCEPTION_H

#include <iostream>
using namespace std;

class illegal_exception
{
private:
    string message;

public:
    illegal_exception(const string &theMessage = "")
        : message(theMessage) {}
    void outputMessage() { cout << message << endl; }
};

#endif // ILLEGAL_EXCEPTION_H