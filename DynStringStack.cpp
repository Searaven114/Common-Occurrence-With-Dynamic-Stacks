
#include "DynStringStack.h"

using namespace std;

//#define DEBUG

// Constructor (Generates an empty stack where top points to nullptr)
DynStringStack::DynStringStack()
{
    #ifdef DEBUG
    cout << "CONSTRUCTOR HAS BEEN INVOKED" << endl;
    #endif

	top = NULL;
}

// Mutator (Pushes a new node with the given value to the list)
void DynStringStack::push(const std::string& str)
{
	StackNode* newNode;

	// Allocate a new node with the value of "str" parameter
	newNode = new StackNode;
	newNode->value = str;

	// If there are no nodes in the list make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

// Mutator (stores the value of removed element to "str" and returns it, then deletes the top)
void DynStringStack::pop(std::string& str)
{
	StackNode* temp;

	if (isEmpty())
	{
		cout << "The stack is empty, nothing can be pop'd\n";
	}
	else	// pop value off top of stack and lower the top pointer
	{
		str = top->value;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//Utility (If empty, returns true)
bool DynStringStack::isEmpty(void) const
{
	return (top == NULL);
}

//Utility (self explanatory)
void DynStringStack::print(void) const
{
	if (top == NULL) { cout << "The stack is empty!" << endl; return; }
	StackNode* ptr = top;

	while (ptr != nullptr)
	{
		cout << ptr->value << " ";
		ptr = ptr->next;
	}
	cout << endl;
}


//Utility (checks the caller stack object if the given string appears in the elements of that stack, if present returns true, returns false Otherwise)
bool DynStringStack::contains(const string & word) const {

    StackNode* tempStack = top;
    while (tempStack != nullptr) { // <---- Linear searching the stack
        if (tempStack->value == word) {
            return true;
        }
        tempStack = tempStack->next;
    }

    return false;
}


//Utility (counts the occurrences of a particular string in the caller stack, returns the total occurrence)
int DynStringStack::countOccurrences(const string & word) const {

    int count = 0;

    StackNode* tempStack = top;
    while (tempStack != nullptr) {

        if (tempStack->value == word) {
            count++; // <-- match found
        }
        tempStack = tempStack->next;
    }

    return count;
}

//Implicit destructor (free's the allocated memory of the DynStringStack object)
DynStringStack::~DynStringStack(){

    #ifdef DEBUG
	cout << "DESTRUCTOR HAS BEEN CALLED!" << endl;
    #endif

    StackNode* ptr;
    while(top != NULL){

        ptr = top->next;
        delete top;
        top = ptr;
    }

}

