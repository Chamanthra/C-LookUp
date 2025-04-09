/*
* Student Name:G.G.A.Chamanthra.C.Gurulumulla
* Student ID:10664500
*/

#include <iostream>
#include "ImprovedDictionary.h"  //Include the header file for the ImprovedDictionary class.

using namespace std;

int main() {
    ImprovedDictionary dictionary;   //Create an instance of the ImprovedDictionary .
    string fileName;                 //Variable to hold the filname.

    cout << "Enter the dictionary file name (or press Enter for default): "; //Ask the suer for an file name .
    getline(cin, fileName);

    if (fileName.empty()) {
        fileName = "dictionary_2024S2.txt";  //use the default filename if no filename is given.
    }

    dictionary.loadDictionary(fileName);  //Load the dictionary from the file.
    dictionary.menu();  //Display the menue for the users.

    return 0; 
}

