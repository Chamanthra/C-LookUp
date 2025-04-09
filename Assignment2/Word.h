#pragma once
#include <iostream> 
#include <string>  

using namespace std;
/*
* Class Name: Word
* Author name :Chamanthra Gurulumulla
* Date :2024/10/12
* Class  named as Word 
* encapsulate the attributes of the word name,type and the definition  in private mode.
* And using setters and getters to set and retrieve these attributes for the methods.
* Inlcudes a method to print the details belong to the word  as  name,type and definition.
*/

class Word {
private:
    string name;                  //name of the word.
    string type;                     //type of the word.
    string definition;              //definition of the word.

public:
    // Create a constructor for Word  having default values as empty strings for the name,type and definition with no arguments.
    Word() {
        name = "";
        type = "";
        definition = "";
    }
    //Create a constructor for the Word class with the provided name,type and definition.  
    Word(string name, string type , string definition ) {
        this->name = name;                       //Assiign the name.
        this->type = type;                       //Assign the type.
        this->definition = definition;           //Assign the definition.
    }

    // Create a setter for the name of the Word.Update the name attribute of the Word Object as wordName set  as the new name for the word.
    void setName(string wordName) {
        name = wordName;
    }

    //Create a getter for the name of the Word.Retrieves the name attribute of the Word Object.
    string getName() const {
        return name;
    }

    // Create a setter for the type of the Word.Update the type attribute of the Word object as wordType set as the new type for the word.
    void setType(string wordType) {
        type = wordType;
    }

    //Create a getter for the type of the Word.Retrieves the type attribute of the Word object.
    string getType() const {
        return type;
    }

    //Create  a setter for the definition of the Word.Update the definition attribute of the Word object as wordDefinition set as the new definition for the word.
    void setDefinition(string wordDefinition) {
        definition = wordDefinition;
    }

    //Create a getter for the definition of the Word.Retrieves the definition attribute of the Word object.
    string getDefinition() const {
        return definition;
    }

    // Create a method to print the details of the word.Outputs the name,type and definition of the word on the console.
    void printDefinition() const {
        cout << "\nWord name: " << name << "\n";
        cout << "Word type: " << type << "\n";
        cout << "Word definition: " << definition << "\n";
    }
};

