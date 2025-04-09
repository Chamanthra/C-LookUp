#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <chrono>  
#include "Dictionary.h"  //The header file for the class Dictionary .

using namespace std;
/*
* Author name:Chamanthra Gurulumulla
* date :2024/10/16
* Create Improved Dicctionary class inheriting from the class Dictionary.
* This class will extend the functionality of the Dictionary class
* The additional functionaities are  a game to guess the fourth word of the definition,manages the highest score
* Add new word to the file dictionary .
*/
class ImprovedDictionary : public Dictionary {
private:
    int highScore;  //Attibute to score current high score.

public:
    //Initialize a constructor to load the highest score to the highScore.
    ImprovedDictionary() {
        highScore = loadHighScore();  // Load the high score when the object is created
    }

    /*
    * The method allows the user to play a game to guess the fourth of word of the definition.
    * A word is selected randomly and it's definition.
    * The game continues until the  user guessed incorrectly.
    * Task 03
    */
    void guessFourthWordGame() {
        //Check if the dictionary is empty.
        if (dictionary.empty()) {
            cout << "Dictionary is empty. Please add words first.\n";
            return;
        }

        int score = 0; //Initialize the player's score.
        cout << "Welcome to the Guess the Fourth Word Game!\n";
        cout << "Try to guess the fourth word in each word definition.\n";
        cout << "The Current High Score: " << highScore << " points.\n";

        // Initialize the random number generator only once
        srand(static_cast<unsigned int>(time(0)));

        // Game loop: keep playing until the player guesses incorrectly
        while (true) {
            // Select a random word from the dictionary.
            int index = rand() % dictionary.size(); //Get a random index
            Word selectedWord = dictionary[index];  //Select the word at that index.
            string definition = selectedWord.getDefinition();  //Get the definition of that word.

            // Ensure the definition has at least four words
            size_t pos = 0; //position for finding spaces in the definition.
            int wordCount = 0;  //set a counter to count numbber of words in the definition.

            //count the words in the definition.
            while (pos != string::npos && wordCount < 4) {
                pos = definition.find(" ", pos + 1);  //find the next  space.
                wordCount++;  //increment the word count.
            }

            if (wordCount < 4) continue; // Skip words with fewer than 4 words in the definition

            cout << "\nWord: " << selectedWord.getName() << endl; 

            // Locate the fourth word
            pos = 0; //reset the position to find the fourth word.
            size_t start = 0;   //start posiition for word extraction.
            for (int i = 0; i < 3; i++) {
                start = definition.find(" ", pos);  //find the space before the fourth word 
                pos = start + 1;                   //move to the next character
            }
            size_t end = definition.find(" ", pos);  //find the end of the fourth word.
            string fourthWord = definition.substr(pos, end - pos);   //extract the fourth word.

            // Replace the fourth word with underscores in the definition
            string maskedDefinition = definition;      //creates a copy of the definition.
            maskedDefinition.replace(pos, fourthWord.length(), string(fourthWord.length(), '_'));  //mask  the fourth word.
            cout << "Definition: " << maskedDefinition << endl;

            // Prompt for  user to make a guess.
            cout << "Guess the fourth word: ";
            string guess;
            cin >> guess;

            //If the guess is correct .Add 10 pints .
            if (guess == fourthWord) {
                score += 10;  // Increase score by 10 for a correct guess
                cout << "Congratulations! Your current score: " << score << " points.\n";

                continue;       //continue the game 
            }
            else {
                // Inform the player of the correct word and end the game
                cout << "Incorrect! The correct word was: " << fourthWord << endl;
                cout << "Your final score: " << score << " points.\n";

                // Update high score if the player has beaten it
                if (score > highScore) {
                    cout << "New high score! Saving your score...\n";
                    highScore = score;
                    saveHighScore();
                }
                break;  // Exit the loop to end the game
            }
        }
    }

    /*
    * This method adds new word to the dictionary.
    * Prompts the user for new word,the type and definition.
    * If the word exists an error message should be displayed.
    */

    void addNewWord() {
        string newWord, newType, newDefinition;  //variables for new word details.

        cout << "Enter the new word: ";
        cin.ignore();               //Clear the input buffer.
        getline(cin, newWord);      //Get the new word from the user.

        //Check if the new word is in the dictionary.
        for (const Word& word : dictionary) {
            if (word.getName() == newWord) {
                cout << "error: word exists, elevated privileges required to edit existing words.\n";
                return;     //exits if the word already exists .
            }
        }

        cout << "Enter the definition for the new word: ";
        getline(cin, newDefinition);       //Get a definition from the  user.

        cout << "Enter the type for the new word: ";
        getline(cin, newType);             //Get the type of thword from the user.

        Word word(newWord, newType, newDefinition);  //create a new Word object.
        dictionary.push_back(word);                  //Add the new word to the dictionary.
        cout << "New word added successfully!\n";      
    }

    /*
    * load the highest score from the file named "highscore.txt".
    * Read from the file to get the highest score and if the file does nnot exist creates a file 
    * And initialize tthe score to 0.
    * The method will return the currrent highest score available.
    */
    int loadHighScore() {
        ifstream inFile("highscore.txt"); //open the file .
        int score = 0;                    //set to 0 
        if (inFile.is_open()) {
            inFile >> score;  //Read the highest score 
            inFile.close();  //close the file .
        }
        else {
            // If the file doesn't exist, create it and set initial score to 0
            cout << "No high score file found. Starting from 0.\n";
            ofstream outFile("highscore.txt");
            if (outFile.is_open()) {
                outFile << 0;  // Initialize the score file with 0
                outFile.close();  //close the file.
            }
        }
        return score;  //return the loaded score.
    }

    /*
    *This method will save the current highest score to the file.
    * Writes the current high score to the file "highscore.txt".
    */

    void saveHighScore() {
        ofstream outFile("highscore.txt");
        if (outFile.is_open()) {
            outFile << highScore;  // Save the high score
            outFile.close();
        }
        else {
            cout << "Error saving high score!\n"; //Display an error message if the hihgest score is not saved.
        }
    }
    /*
    * overridden the menue method of the Dictionary class.
    * The menue   method for the improved dictionary .
    * This menue will offer options to the user to search a word,play the guessing game ,add a new word or exit the program.
    * This method will iterate until the user chooses to exit the program.
    */
    void menu() override {
        int choice;
        while (true) {
            cout << "\nImproved Dictionary Menu\n";
            cout << "1) Search for a Word\n";
            cout << "2) Play the 'Guess the Fourth Word' Game\n";
            cout << "3) Add New Word\n";
            cout << "4) Exit\n";
            cout << "Enter your choice: ";
            cin >> choice; //Get the user's choice 

            //Using the switch statements to handle the users choices .
            switch (choice) {
            case 1: {
                string wordToSearch;
                cout << "Enter the word to search: ";
                cin.ignore();
                getline(cin, wordToSearch);
                searchWord(wordToSearch);  //Call the searchWord method in Dictionary class.
                break;
            }
            case 2:
                guessFourthWordGame();  //call the guessFourthWordGame method.
                break;
            case 3:
                addNewWord();  //Call the addNewWord method.
                break;
            case 4:
                cout << "Exiting...\n";          
                return;  //Exit the  menue loop.
            default:
                cout << "Invalid choice! Please try again.\n"; //Display an error message to invalid entries.
            }
        }
    }
};

