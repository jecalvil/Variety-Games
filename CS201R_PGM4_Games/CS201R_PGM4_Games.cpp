// CS201R_PGM4_Games.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// NAME: Esteban Calderon
// DATE: Due: 02/23/25
// PROGRAM: Program 4 - Games
// This Program contains a menu with the option to play of 6 selected games: Craps, Scrraps, Rock Paper Scissors, Rock Paper Scissors Spock,
// Hangman, and Blackjack. They all present the option to play again within the game, and we can choose different games within the menu
/*
* LINK TO VIDEO BELOW
* 
* https://umsystem.hosted.panopto.com/Panopto/Pages/Viewer.aspx?id=4b4a157e-a121-412e-9b3e-b28e000b21c9 
* 
* LINK TO VIDEO ABOVE
*/

#include "Games.h"
#include "Functions.h"

/*
* while continue
*   if choice is C, S, R, E, B, H, Q
*   then play craps, scraps, rock paper scissors, rock paper scissors spock, blackjack, hangman, or quit respective to the choice
* 
*   if they quit
*       continue is false
*/
  
int main()
{
    // Generate randomness
    srand(time(0));
    string choice;
    // Greet
    cout << "Welcome to My Games!\n\n";

    bool isContinue = true;
    // Game will continue until the user types "Q"
    while (isContinue) {
        choice = menu();
        if (choice == "C") {
            craps();
        }
        else if (choice == "S") {
            scraps();
        }
        else if (choice == "R") {
            rockPaperScissors();
        }
        else if (choice == "E") {
            rockPaperScissorsSpock();
        }
        else if (choice == "B") {
            blackjack();
        }
        else if (choice == "H") {
            hangman();
        }
        else if (choice == "Q") {
            cout << "Quitting..." << endl;
            isContinue = false;
        }

    }
    
 
}

 
