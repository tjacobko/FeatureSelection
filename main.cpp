#include "DataSet.h"
#include "Instance.h"

#include <iostream>
#include <string>

using namespace std;

int main () {
    string userFile;
    int userInput = -1;
    char end;
    
    cout << "Welcome to Jacob Ko's Feature Selection Algorithm!" << endl;
    cout << "Type in the name of the file to test (i.e. cs_170_small80.txt): ";
    cin >> userFile;
    cout << endl;
    Dataset* userSet = new Dataset(userFile);
    
    cout << "Please wait while I normalize the data...";
    userSet->normalize();
    
    while (end != 'n') {
        cout << "Type the number of the algorithm you want to run." << endl << endl;
        cout << "1) Forward Selection" << endl;
        cout << "2) Backward Elimination" << endl << endl;
        cin >> userInput;
        
        if (userInput == 1) {
        cout << "Using Forward Selection." << endl;
        userSet->forwardSelection();
        }
        else if (userInput == 2) {
            cout << "Using Backward Elimination." << endl;
            userSet->backwardElimination();
        }
        else {
            cout << "Error. Invalid input." << endl;
        }
        
        cout << "Would you like to run another search algorithm? (y/n): ";
        cin >> end;
        cout << endl;
    }
    cout << "Goodbye!" << endl;
    
    return 0;
}