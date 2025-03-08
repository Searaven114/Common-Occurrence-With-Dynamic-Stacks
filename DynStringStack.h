#ifndef _DYN_STRING_STACK
#define _DYN_STRING_STACK

#include <string>
#include <iostream>

using namespace std;

struct StackNode
{
    string value;
    StackNode* next;
};


class DynStringStack
{
private:
    StackNode* top;

public:
    DynStringStack(void); //default constructor
    ~DynStringStack(void); //Implicit destructor
    void push(const string&); //mutator
    void pop(string&); //mutator
    bool isEmpty() const; //util
    void print() const; //util
    bool contains(const string& word) const; //util & helper of ProcessStacks function
    int countOccurrences(const string& word) const; //util & helper of ProcessStacks function
};

#endif