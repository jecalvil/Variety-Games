#include "Functions.h"

// PRE: Input string
// POST: Returns true or false if the string is not a menu option
bool isMenuItem(string str) {
    return str.find_first_not_of("BSCREHQ") == string::npos && str.length() == 1;
}

// PRE: None
// POST: returns a string of a character of what game the user wants to play

/*
* display menu
* get the users choice for the game
* return user choice
*/
string menu() {
    string choice;

    // Display Options
    cout << "Your Games List" << endl;
    cout << "C - Craps" << endl;
    cout << "S - Scraps" << endl;
    cout << "R - Rock, Paper, Scissors" << endl;
    cout << "E - Rock, Paper, Scissors, Spock" << endl;
    cout << "B - Blackjack" << endl;
    cout << "H - Hangman" << endl;
    cout << "Q - Quit" << endl;
    cout << "What game would you like to play? ";

    // Get user choice until valid
    getline(cin, choice);
    cout << endl;
    while (!isMenuItem(choice)) {
        cout << endl;
        cout << "Please enter a valid option: ";
        getline(cin, choice);
    }

    // Returnt the selected option
    return choice;
}