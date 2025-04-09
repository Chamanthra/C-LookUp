#pragma once
#include <vector>
#include <string>
#include "Word.h"   //Include the header file of the Word class to handle word.

using namespace std;

/*
* Class name :Dictionary
* Author name :Chamanthra Gurulumulla
* Date :2024/10/14
* The Dictionary class will encapsulate the dictionary of  word objects .
* Provides the functionality to load  words from the dictionary file .
* Searching for words given by the user from the file.
* Display of the menue to interact with the user.
*/
class Dictionary {
protected:
    vector<Word> dictionary;    //A vector storing the Word object.

private:
    const string defaultFileName = "dictionary_2024S2.txt";   //The default file name to laod the dictionary.
    const string typeTag = "Type: ";                          //Tag for the type of the word.
    const string nameTag = "Word: ";                          //Tag for the name of the word .
    const string defTag = "Definition: ";                     //Tag for the definnition of the word.

public:
    /*
    *  Load dictionary from a sspecific file given by the user or the default file .
    * Read words from the file and populates the dictionary.
    * have vector of Word object where each word name,type and the definition is present in the file.
    * Parameter is the fileName,which is the name of the file that wanted to  be read from.
    */
    void loadDictionary(string fileName);                    

    /*
    * Method to search  a specific word from the dictionary .
    * looks for the word in dictionary  vector and if found will display the type and definition of the  word.
    * parameters of the method is word ,the word that is been searched in the dictionary.
    */
    void searchWord(string& word);

    /*
    * This method is used to interact with the user by providing options to load the dictionary,search for words and exit.
    * This method will be overridden in the derived class to add more functionality to the method.
    */
    virtual void menu();
};

