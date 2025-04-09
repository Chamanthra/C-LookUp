#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <exception>
#include "Dictionary.h"   // The header file for the class Dictionary .

using namespace std;

/*
* This method is used to load dictionary from a specific file.
* Attempts to load the file provided by the user,if the file is not found tries to open the default file given.
* If the default file or the file given opens the method will read the lines from the file to create Word objects 
* including  type,definition and name.
* Each Word object is added to the dictionary vector.
* parameters :fileName,the file that needed to be loaded.
*/
void Dictionary::loadDictionary(string fileName) {
    //Attempts to open the file.
    ifstream dictionaryReader(fileName);

    //Check iff the file opens successfully.
    if (!dictionaryReader.is_open()) {
        cout << "File not found, trying default...\n";
        fileName = defaultFileName;    //set the fileName to the default file name.
        dictionaryReader.open(fileName);      //Attempts to  open the default file.

        //Check if the deafault file opens succcessfully .
        if (!dictionaryReader.is_open()) {
            cout << "Default file also not found, giving up...\n";
            return;
        }
        else {
            cout << "Default file opened!\n";
        }
    }
    else {
        cout << "Your file has been opened!\n";
    }

    string buffer;            //Generate a buffer to hold each line  read from the file.
    Word currentWord;         //Temporary  word object to read data.

    //Read each line from the file.
    while (getline(dictionaryReader, buffer)) {
        //process only the not empty lines.
        if (!buffer.empty()) {
            //Check for type Tag and set type for the current Word object.
            if (buffer.find(typeTag) != string::npos) {
                currentWord.setType(buffer.substr(typeTag.size()));   //set type 
            }
            //Check for definition Tag and set definiition for the current Word object.
            else if (buffer.find(defTag) != string::npos) {
                currentWord.setDefinition(buffer.substr(defTag.size()));   //set Definition
            }
            //Check for the name Tag and set name for the current Word object.
            else if (buffer.find(nameTag) != string::npos) {
                currentWord.setName(buffer.substr(nameTag.size()));    //set name
            }
        }
        else {
            //if an empty line is encounted ,add the current word to the dictionary.
            if (!currentWord.getName().empty()) {
                dictionary.push_back(currentWord); //Add the current Word object to the dictionary.
                currentWord = Word(); // Reset for the next entry.
            }
        }
    }

    // Add the last word if the file doesn't end with a newline
    if (!currentWord.getName().empty()) {
        dictionary.push_back(currentWord);   //Add the last Word object to the dictionary.
    }

    dictionaryReader.close();  //Close the file
}

/*
* Loop throught the dictionary vector to find a specific word wanted to be searched.
* If found the word ,print the type and definition of the word 
* if not found ,notify the user that word is not found.
* parameter:word,the word needed to be searched.
*/
void Dictionary::searchWord(string& word) {
    //Iterates through each Word object in the dictionary.
    for (Word& currentWord : dictionary) {
        //Check if the current word matches the searched word.
        if (currentWord.getName() == word) {
            currentWord.printDefinition();
            return;
        }
    }
    cout << "Word not found!\n";
}
/*
* Display the menue options of load the dictionary ,search words and exit to the user.
*loops until the user chooses the exit .
*/
void Dictionary::menu() {
    int choice;  //Variable holding the users choice .
    string fileName, wordToSearch;    //varaibles holding file name and word needed to be searched.
    while (true) {
        cout << "Dictionary Menu\n";
        cout << "1) Load a dictionary file\n";
        cout << "2) Search for a word\n";
        cout << "3) Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;   //get  user's choice 
        cin.ignore();  //Ignore new line of character left in the input buffer.

        if (choice == 1) {
            cout << "Enter the file name: ";
            cin >> fileName;
            loadDictionary(fileName);   //call the method loadDictionary.
        }
        else if (choice == 2) {
            cout << "Enter the word to search: ";
            getline(cin, wordToSearch);  //get the word needed to be searched.
            searchWord(wordToSearch);   //call the method searchWord to  search the given word.
        }
        else if (choice == 3) {
            break;                      //exit the loop 
        }
        else {
            cout << "Invalid choice, try again.\n";  //prompt the user to try again .
        }
    }
}
