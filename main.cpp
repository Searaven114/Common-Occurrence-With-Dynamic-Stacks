
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "DynStringStack.h"

//#define DEBUG

using namespace std;

void fileOpenner(ifstream &file, string temp);
void loadFileIntoStack(ifstream &file, DynStringStack &stack);
void ProcessStacks(DynStringStack& stack1, DynStringStack& stack2, int choice);

int main() {

    cout << "This program finds the common words of two files using stacks.\n---" << endl;

    //handling file io for file 1
    ifstream ifile1;
    fileOpenner(ifile1,"first");

    //Loading the contents of now openned file 1 into a DynStringStack object
    DynStringStack s1;
    loadFileIntoStack(ifile1, s1);

    #ifdef DEBUG
    s1.print();
    #endif


    //handling file io for file 2
    ifstream ifile2;
    fileOpenner(ifile2,"second");

    //Loading the contents of now openned file 2 into another DynStringStack object
    DynStringStack s2;
    loadFileIntoStack(ifile2, s2);

    #ifdef DEBUG
    s2.print();
    #endif


    int choice;
    while (true) {
        cout << "Choose with respect to which file the result will be sorted to (1: first file, 2: second file):" << endl;
        cin >> choice;

        if (cin.fail()) {

            //Clear error state of cin for the cases of non-int entries
            cin.clear();
            cin.ignore(9999999,'\n');

            cout << "---\nInvalid choice\n---" << endl;
            continue;
        }

        //if the choice is of correct type but is neither 1 or 2, declare invalidity
        if ((choice != 1) && (choice != 2)) {
            cout << "---\nInvalid choice\n---" << endl;
        } else {
            //If the user enters 1 or 2, break the while loop and proceed forward to main processing
            cout << "---\n";
            break;
        }
    }

    //Execute main processing of 2 stacks that are filled with words from the files.
    ProcessStacks(s1,s2,choice);

    ifile1.close();
    ifile2.close();

    return 0;
}

//*********************************************************************************************************************************************************************



/* @brief Processes two stacks to find common words between two files and prints the occurrences in the predetermined format.
 * @param "stack1" [in][out] Reference to the first dynamic string stack.
 * @param "stack2" [in][out] Reference to the second dynamic string stack.
 * @param "choice" [in] An integer to decide the sorting order (1 for the first file, 2 for the second).
 * @pre Both stacks are filled with words, user has given a choice for processing order, nothing is printed to the console yet
 * @post stacks will be processed and each common word that appears in the files will be printed with its minimum occurrence.
 * @note Debug code included.
 * @note code is not complete for full programs since stack1 doesnt get restored, uncomment "chosenStack.push(word);" if initial stacks must be retained
 * @see "contains" and "countOccurrences" in DynStringStack.cpp
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void ProcessStacks(DynStringStack& stack1, DynStringStack& stack2, int choice) {

    DynStringStack& chosenStack = (choice == 1) ? stack1 : stack2; //Reference to the first stack, which itself will depend on user's choice
    DynStringStack& otherStack = (choice == 1) ? stack2 : stack1;  //Reference to the second stack, which will be the "other" of first stack

    DynStringStack tempStack; //Temporary stack to preserve chosenStack
    DynStringStack processedWords; //Stack to keep track of processed words

    string word;

    //Reversed the chosen stack to process words in the correct order
    while (!chosenStack.isEmpty()) {
        chosenStack.pop(word);
        tempStack.push(word);
    }

    //One by One, iterate through the elements of tempStack by popping the current top to "word" variable until its empty. (MAIN ITERARION LOOP)
    while ( !tempStack.isEmpty() ) {

        tempStack.pop(word); //assign the currently handled element of the stack to "word" variable

        //Check if the word has already been processed (occurs in processedWords = skip)
        if (processedWords.contains(word) == false) {

            int counter1 = tempStack.countOccurrences(word) + 1; // Increment by 1 to include the current word since we already have 1 at the hand under "word" variable.
            int counter2 = otherStack.countOccurrences(word); //count its occurrances in the other stack which will be used for commonness and min-deciding.

            if (counter2 > 0) { // <--- If the word currently handled is a common word do this:

                int minCount = (counter1 < counter2) ? counter1 : counter2; //decide the min occurrance, if count2 is bigger than count1 than count1 it is, count2 otherwise

                #ifdef DEBUG
                cout << "DEBUG: count1 for word " << word << " is " << counter1 << endl;
                cout << "DEBUG: count2 for word " << word << " is " << counter2 << endl;
                cout << "DEBUG: choosen minimum for occurrences of word " << word << " is " << minCount << endl;
                #endif

                cout << "The word \"" << word << "\" occurred at least " << minCount << " time(s) in both files." << endl; // Finalize the print operations for the currently handled element of tempStack
            }

            processedWords.push(word);// <---- Add the word to the processedWords stack so that it wont be handled as unique word again
        } else {

            #ifdef DEBUG
            cout << "DEBUG: " << word << " HAS BEEN DISCARDED DUE TO ITS PRESENCE IN processedWords STACK !" << endl;
            #endif
        }
        //Restore the original s1 stack if further operations will be needed in the program, for the sake of reducing the amount of processing (.push) ive commented out this functionality.
        //chosenStack.push(word);
    }
}



/* @brief Prompts the name of the file and attempts to open it and bound it to a ifstream object, fail check incorporated
 * @param "file" [in][out] Ifstream object which the function will return
 * @param "temp" [in] A string that will be used for formatting cout to match with sample run's format
 * @note Debug code included
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void fileOpenner(ifstream &file, string temp){

    cout << "Enter the " << temp << " file name:" << endl;

    string filename;
    cin >> filename;
    file.open(filename.c_str());

    while( file.fail() ){

        cout << "Enter the " << temp << " file name:" << endl;
        cin >> filename;
        file.open(filename.c_str());
    }

    #ifdef DEBUG
    cout << "DEBUG: " << temp << " FILE HAS BEEN SUCCESSFULLY OPENNED !" << endl;
    #endif
}



/* @brief Takes an ifstream object that is bound to a file, push'es the contents of the file into the given stack object one by one
 * @param "file" [in][out] Ifstream object which will be read.
 * @param "stack" [in][out] Stack object that will be load with string from file.
 * @pre file is ready to be worked on, stack object is present and empty.
 * @post file is readed and every word is pushed into the stack one by one
 * @note Takes "line being empty" and "multiple words in 1 line" conditions into account.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void loadFileIntoStack(ifstream &file, DynStringStack &stack) {
    string line;
    while (getline(file, line)) {// <--- read the file line by line

        //Move to the next line if the currently held line is blank
        if ( line.empty() ){
            continue;
        }

        istringstream iss(line); // "iss" the currently held line to take multiple words in 1 line into account
        string word;

        //As long as there are words in that currently handled line, push them to the stack.
        while (iss >> word) {
            stack.push(word);
        }
    }
}

