#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>


using namespace std;

// Creates a struct for the dice in craps that rolls 3 die and calculates the sum
struct CrapsDie {

	// Create the dice
	int die1, die2, die3, sum;

	// Roll the dice
	void RollDice() {

		// Roll 3 dice
		die1 = rand() % 8 + 1;
		die2 = rand() % 8 + 1;
		die3 = rand() % 8 + 1;
		sum = die1 + die2 + die3;

		// Display each dice roll and the sum
		cout << "\tYou rolled: " << die1 << " + " << die2 << " + " << die3 << " = " << sum << endl;
	}
	
};

// Card structure that holds the suit, face, and and int value
struct Card {
	string suit;
	string face;
	int value;
};

// Deck structure is a vector of 52 cards with the ability to shuffle, draw, anc clear
struct Deck {
	vector<Card> deck;

	string suits[4] = { "Hearts", "Spades", "Diamonds", "Clubs" };
	string face[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "K", "Q", "A" };
	int value[13] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };
	bool created = false;

	// Creates a deck with each suit assigned with each face and respective value
	void createDeck() {
		for (string suit : suits) {
			for (int i = 0; i < 13; i++) {
				// Create Empty Card
				Card tempCard;
				// Assign values
				tempCard.suit = suit;
				tempCard.face = face[i];
				tempCard.value = value[i];
				// Push back to deck
				deck.push_back(tempCard);
			}
		}
		created = true;
	}

	// Shuffles each card in the deck with another random card in the deck.
	void shuffle() {
		int random;
		if (created == true) {
			for (int i = 0; i < deck.size(); i++) {
				// Random index
				random = rand() % 52;
				// Switch the card at i with a random card in the deck
				swap(deck[i], deck[random]);
			}
		}
	}

	// Testing purposes
	//void printDeck() {
	//	for (Card card : deck) {
	//		cout << card.face << " of " << card.suit << " - Value: " << card.value << endl;
	//	}
	//}

	// Picks a random card from the deck, removes it, and returns it.
	Card drawCard() {
		// Random num from card size
		int randNum = rand() % deck.size();
		// Get random card from deck
		Card drawnCard = deck[randNum];
		// Remove random card from deck
		deck.erase(deck.begin() + randNum);
		// Return drawn card
		return drawnCard;
	}

	// Clears the deck
	void clearDeck() {
		deck.clear();
	}

};

// Vector to contain the player's and dealer's cards
struct Hand {
	vector<Card> hand;
	int total = 0;

	// Function made by asking chatgpt for assistance - did not copy directly from it, the rest of my code is completely original by me
	// Essentially, I asked it how to print special characters and change text color. Through the accumulation of several questions
	// I managed to put together this code which receives the suit string, and prints the symbol with the proper color for each suit
	void printSymbol(string suit) {

		_setmode(_fileno(stdout), _O_U8TEXT);  // Set the mode for Unicode output

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // Get the console handle

		// Check suit and set color
		if (suit == "Hearts" || suit == "Diamonds") {
			// Set color to red - Hearts and Diamonds
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
		else {
			// Set color to default - Spades and Clubs
			SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
		}

		// Print corresponding symbol
		if (suit == "Hearts") {
			wcout << L"\u2665";  // Heart 
		}
		else if (suit == "Spades") {
			wcout << L"\u2660";  // Spade 
		}
		else if (suit == "Diamonds") {
			wcout << L"\u2666";  // Diamond 
		}
		else if (suit == "Clubs") {
			wcout << L"\u2663";  // Club 
		}
		else {
			wcout << L"Unknown Suit";  // Handle unexpected values
		}

		// Reset color to default after printing
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		_setmode(_fileno(stdout), _O_TEXT);  // Reset the mode to normal text, if not it breaks
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	// Starting Hand
	void drawStartingHand(Deck deck) {
		hand.push_back(deck.drawCard());
		hand.push_back(deck.drawCard());
	}

	// Function to add card to hand
	void addCard(Deck deck) {
		hand.push_back(deck.drawCard());
	}


	// Function to calculate hand total value
	int calculateTotal() {
		total = 0;
		// Calculate total value of hand
		for (Card card : hand) {
			total += card.value;
		}
		// Check if hand is over 21, see if there are any aces
		if (total > 21) {
			for (Card card : hand) { // find first instance of an ace if there is
				if (card.face == "A") {
					total -= 10;
					break;
				}
			}
		}
		return total;
	}

	// Returns true if the total value of the hand is greater than 21
	bool isBust() {
		return total > 21;
	}

	// Displays each card in the hand
	void displayHand() {
		for (Card card : hand) {
			cout << setw(10) << left << "";
			printSymbol(card.suit);
			cout << " " << card.face << endl;
		}
	}

	// Displays the first card while hiding the last one
	void displayDealerHand() {
		cout << "Dealer's Hand" << endl;
		for (int i = 0; i < hand.size() - 1; i++) {
			cout << setw(10) << left << "";
			printSymbol(hand[i].suit);
			cout << " " << hand[i].face << endl;
		}
		cout << setw(8) << left << "HIDDEN:";
		cout << "| *?* |" << endl;
	}

	// Clears the hand
	void clearHand() {
		hand.clear();
	}

};

// PRE: None
// POST: Plays Craps
void craps();
// PRE: None
// POST: Plays Scraps


void scraps();
// PRE: None
// POST: Plays Rock, Paper, Scissors
void rockPaperScissors();
// PRE: None
// POST: Plays Rock, Paper, Scissors, Spock
void rockPaperScissorsSpock();
// PRE: None
// POST: Plays Hangman
void hangman();
// PRE: None
// POST: Plays Blackjack
void blackjack();
