#include "Games.h"

// Code for Craps =================================================================================================================================

// PRE: None
// POST: Rolls 2 dice, displays the rolls and the sum
int rollDiceCraps() {
	int die1, die2, sum;
	// roll 2 die
	die1 = rand() % 6 + 1;
	die2 = rand() % 6 + 1;
	// get sum of 2 die
	sum = die1 + die2;
	// print dice rolls
	cout << "\tYou rolled: " << die1 << " + " << die2 << " = " << sum << endl;
	return sum;
}

// PRE: Receives a string
// POST: Returns true or false if string contains only digits
bool isDigits(string str) {
	return str.find_first_not_of("0123456789") == string::npos;
}

/*
* while loop to keep playing
	*	greet the user and tell them their networth
	*	receive their bet
	*	roll dice - calculate the sum
	*	if sum is 7 or 11 win
	*	else if sum is 2,3,12 lose
	*	else
	*		point = sum
	*		roll until point (win) or 7 (lose)
	*		increase/decrease networth accordingly
	*	check if bankrupt (if so gameover)
*	ask to play again while retaining their networth (continue while loop)
*/

void craps() {

	// Variables
	int sum, point, betInt;
	int networth = 50;
	string bet;
	string again = "Y";

	// Greet and display networth
	cout << "WELCOME TO CRAPS!" << endl;
	while (again == "Y") {
		cout << "Your net worth is: $" << networth << ". Please enter your bet: ";

		// Get user bet
		bool valid = false;
		while (valid == false) {
			valid = true;
			getline(cin, bet);
			// Check if digits
			while (!isDigits(bet)) {
				cout << "Please type a positive integer: ";
				getline(cin, bet);
			}
			// Convert to int
			betInt = stoi(bet);
			// Check if proper bet
			if (betInt > networth) {
				cout << "Your net worth is only: " << networth << ". Please adjust your bet: ";
				valid = false;
			}
		}

		// Roll die and get sum
		sum = rollDiceCraps();

		// Win if sum is 7 or 11
		if (sum == 7 || sum == 11) {
			networth += betInt;
			cout << "You win! You now have: " << networth << endl;
		}
		// Lose if sum is 2, 3, or 12
		else if (sum == 2 || sum == 3 || sum == 12) {
			networth -= betInt;
			cout << "You Lost! You now have : " << networth << endl;
		}
		// Else point = sum and roll until you get point (win) or 7 (lose)
		else
		{
			point = sum;
			cout << "\tPoint is: " << point << endl;
			sum = rollDiceCraps();
			while (sum != point && sum != 7) {
				sum = rollDiceCraps();
			}
			if (sum == point) {
				networth += betInt;
				cout << "You win! You now have: " << networth << endl;
			}
			else {
				networth -= betInt;
				cout << "You Lost! You now have : " << networth << endl;
			}
		}
		// GAME OVER if they go bankrupt
		if (networth <= 0) {
			cout << "You have gone bankrupt... GAME OVER" << endl;
			networth = 50;
		}

		// Prompt to play again?
		cout << "Would you like to go again? Y or N ";
		getline(cin, again);
		while (again != "Y" && again != "N") {
			cout << endl;
			cout << "Enter a valid choice: ";
			getline(cin, again);
		}
	}
}

/*
* while loop to keep playing
	*	greet the user and tell them their networth
	*	receive their bet
	*	roll dice - calculate the sum
	*	if sum is 9,10,14 or if any die is 8 - win
	*	else if sum is 8, 20, 23, 24, or die is 1 (lose)
	*	else
	*		point = sum
	*		roll until point (win) or sum is 15 or any die is 8
	*		increase/decrease networth accordingly
	*	check if bankrupt (if so gameover)
*	ask to play again while retaining their networth (continue while loop)
*/
// Code for Scraps ================================================================================================================================

void scraps() {

	// NOTE: GAME RULES WORK ASSUMING WINNING CONDITIONS TAKE PRECIDENCE OVER LOSING CONDITIONS
	// EX: IF ONE DIE IS 8, BUT THE SUM IS 20, THEN WE STILL WIN

	int sum, point, betInt, die1, die2, die3;
	int networth = 50;
	string bet;
	string again = "Y";

	// Greet and display networth
	cout << "WELCOME TO SCRAPS!" << endl;
	while (again == "Y") {
		cout << "Your net worth is: $" << networth << ". Please enter your bet: ";

		// Get user bet
		bool valid = false;
		while (valid == false) {
			valid = true;
			getline(cin, bet);
			// Check if digits
			while (!isDigits(bet)) {
				cout << "Please type a positive integer: ";
				getline(cin, bet);
			}
			// Convert to int
			betInt = stoi(bet);
			// Check if proper bet
			if (betInt > networth) {
				cout << "Your net worth is only: " << networth << ". Please adjust your bet: ";
				valid = false;
			}
		}

		// Roll die and get sum
		CrapsDie die;
		die.RollDice();
		sum = die.sum;
		die1 = die.die1;
		die2 = die.die2;
		die3 = die.die3;

		// Win if sum is 9, 10, or 14 ----- OR if any die is exactly 8
		if (sum == 9 || sum == 10 || sum == 14 || (die1 == 8 || die2 == 8 || die3 == 8)) {
			networth += betInt;
			cout << "You win! You now have: " << networth << endl;
		}
		// Lose if sum is 8, 20, 23, 24 ------ OR if any die is exactly 1
		else if (sum == 8 || sum == 20 || sum == 23 || sum == 24 || (die1 == 1 || die2 == 1 || die3 == 1)) {
			networth -= betInt;
			cout << "You Lost! You now have : " << networth << endl;
		}
		// Else point = sum and roll until you get point or lose if single 8 or sum 15
		else
		{
			point = sum;
			cout << "\tPoint is: " << point << endl;
			// Reroll
			die.RollDice();
			while (die.sum != point && die.sum != 15 && (die.die1 != 8 || die.die2 != 8 || die.die3 != 8)) {
				die.RollDice();
			}
			if (die.sum == point) {
				networth += betInt;
				cout << "You win! You now have: " << networth << endl;
			}
			else {
				networth -= betInt;
				cout << "You Lost! You now have : " << networth << endl;
			}
		}
		// GAME OVER if they go bankrupt
		if (networth <= 0) {
			cout << "You have gone bankrupt... GAME OVER" << endl;
			networth = 50;
		}

		// Prompt to play again?
		cout << "Would you like to go again? Y or N ";
		getline(cin, again);
		while (again != "Y" && again != "N") {
			cout << endl;
			cout << "Enter a valid choice: ";
			getline(cin, again);
		}
	}

}

// Code for Rock, Paper, Scissors =================================================================================================================
bool isRockPaperScissors(string str) {
	return (str == "rock" || str == "paper" || str == "scissors");
}

/*
* Greet user
* begin while loop
*	prompt and receive choice of rock, paper scissors
*	randomly generate the computer's choice
*	find winner:
*		if the choices were the same its a tie
*		else if user chose rock, paper, or scissors while the computer chose scissors, rock, or paper respectively (win)
*		esle computer wins
*	ask to play again (continue loop accordingly)
*/
void rockPaperScissors() {
	
	// Variables
	string computerChoice, userChoice;
	string again = "Y";

	// Display Game
	cout << "WELCOME TO Rock, Paper, Scissors!" << endl;
	while (again == "Y") {
		cout << "Enter rock, paper, or scissors: ";

		// Get User Choice
		getline(cin, userChoice);
		while (!isRockPaperScissors(userChoice)) {
			cout << "Please enter a valid choice: ";
			getline(cin, userChoice);
		}

		// Get Computer Choice
		int randNum = rand() % 3;
		switch (randNum) {
			case 0:
				computerChoice = "rock";
				break;
			case 1:
				computerChoice = "paper";
				break;
			case 2:
				computerChoice = "scissors";
				break;
		}
		cout << "Computer chose: " << computerChoice << endl;

		// Find Winner
		if (userChoice == computerChoice) // Tie
			cout << "It's a tie!" << endl;
		else if ((userChoice == "rock" && computerChoice == "scissors") || (userChoice == "paper" && computerChoice == "rock") || (userChoice == "scissors" && computerChoice == "paper")) // User wins
			cout << "You win!" << endl;
		else // Computer wins
			cout << "Computer wins!" << endl;

		// Ask to play again
		cout << "Would you like to go again? Y or N: ";
		getline(cin, again);
		while (again != "Y" && again != "N") {
			cout << "Please enter a valid choice: ";
			getline(cin, again);
		}
	}

}

// Code for Rock, Paper, Scissors, Spock ==========================================================================================================
bool isRockPaperScissorsSpock(string str) {
	return (str == "rock" || str == "paper" || str == "scissors" || str == "spock");
}

/*
* Greet user
* begin while loop
*	prompt and receive choice of rock, paper, scissors, or spock
*	randomly generate the computer's choice
*	find winner:
*		if the choices were the same its a tie
*		else if (userChoice equals "rock" and computerChoice equals "scissors") or (userChoice equals "paper" and (computerChoice equals "rock" or computerChoice equals "spock")) or (userChoice equals "scissors" and computerChoice equals "paper")
*		esle computer wins
*	ask to play again (continue loop accordingly)
*/
void rockPaperScissorsSpock() {

	// Variables
	string computerChoice, userChoice;
	string again = "Y";

	// Display Game
	cout << "WELCOME TO Rock, Paper, Scissors, Spock!" << endl;
	while (again == "Y") {
		cout << "Enter rock, paper, scissors, or spock: ";

		// Get User Choice
		getline(cin, userChoice);
		while (!isRockPaperScissorsSpock(userChoice)) {
			cout << "Please enter a valid choice: ";
			getline(cin, userChoice);
		}

		// Get Computer Choice
		int randNum = rand() % 4;
		switch (randNum) {
			case 0:
				computerChoice = "rock";
				break;
			case 1:
				computerChoice = "paper";
				break;
			case 2:
				computerChoice = "scissors";
				break;
			case 3:
				computerChoice = "spock";
				break;
		}
		cout << "Computer chose: " << computerChoice << endl;

		// Find Winner
		if (userChoice == computerChoice) // Tie
			cout << "It's a tie!" << endl;
		else if ((userChoice == "rock" && computerChoice == "scissors") || (userChoice == "paper" && (computerChoice == "rock" || computerChoice == "spock")) || (userChoice == "scissors" && computerChoice == "paper")
				|| (userChoice == "spock" && (computerChoice == "rock" || computerChoice == "scissors"))) // User wins
			cout << "You win!" << endl;
		else // Computer wins
			cout << "Computer wins!" << endl;

		// Ask to play again
		cout << "Would you like to go again? Y or N: ";
		getline(cin, again);
		while (again != "Y" && again != "N") {
			cout << "Please enter a valid choice: ";
			getline(cin, again);
		}
	}

}
/*
* while loop to repeat
*	create a deck, shuffle, while also creating user and dealer's hand
*	draw cards into user and dealer's hand
*	display user and dealer hand (one card showing 1 hidden)
*	if player went over 21, bust
*	if player == 21 - blackjack
*	else ask to draw another card if total <= 21
*	
*	if drawing again
*		while they want to keep drawing
*			draw card
*			display hand and calcuulate total
*			if over 21 - bust
*			less than 21, ask to keep drawing
*			exactly 21 then stop
* 
*	if player did not bust then computer draws
*		while computer total <= 16 keep drawing
*			if over 21 - bust
*			if >= 16 check to see if they won by comparing the users points
*		find winner
* 
*	ask to play again and continue
*	if so, reset the deck, hands, and turn count
*/
// Code for Blackjack =============================================================================================================================
void blackjack() {
	// Greet
	cout << "WELCOME TO BLACKJACK!\n" << endl;
	int playerTotal = 0;
	int dealerTotal = 0;
	int turn = 0;
	string keepDrawing = "Y";
	string again = "Y";
	Deck gameDeck;
	Hand hand;
	Hand dealerHand;

	while (again == "Y") {
		// Clear vectors
		gameDeck.clearDeck();
		hand.clearHand();
		dealerHand.clearHand();
		
		// Generate Deck
		gameDeck.createDeck();
		gameDeck.shuffle();


		// Get Player's Hand
		hand.drawStartingHand(gameDeck);

		// Get Computer Hand
		dealerHand.drawStartingHand(gameDeck);

		// Player's turn
		while (keepDrawing == "Y") {
			turn += 1;

			// Display player hand and total
			cout << "============================================================" << endl;
			cout << "Player has the following cards:" << endl;
			hand.displayHand();
			playerTotal = hand.calculateTotal();
			cout << "\tTOTAL: " << playerTotal << endl << endl;
			// Display dealer's hand
			dealerHand.displayDealerHand();
			cout << "============================================================" << endl;

			// Check if they bust, if not ask them if they want to draw again
			if (playerTotal > 21) {
				cout << "OOPS - Player went over 21. COMPUTER WINS!!" << endl;
				break;
			}
			else if (playerTotal == 21) {
				if (turn == 1) {
					cout << "YOU GOT A BLACKJACK, let's see if the dealer has one too..." << endl;
					break;
				}
				else {
					cout << "You have 21, lets see what the dealer has..." << endl;
				}
			}
			else { // ask if they want to draw again
				cout << "Would you like to take another card? Y or N: ";
				getline(cin, keepDrawing);
				while (keepDrawing != "Y" && keepDrawing != "N") {
					cout << "\nPlease enter a valid choice: ";
					getline(cin, keepDrawing);
				}
			}
			// draw if they want to draw, break if they don't
			if (keepDrawing == "Y") {
				hand.addCard(gameDeck);
			}
		}

		// Dealer's Turn
		if (playerTotal <= 21) {

			// Reveal Dealer's Hand and Total
			cout << "============================================================\nREVEALING DEALER'S HAND: " << endl;
			dealerTotal = dealerHand.calculateTotal();
			dealerHand.displayHand();
			cout << "\tTOTAL: " << dealerTotal << endl << endl;

			// Dealer immediate bust
			if (dealerTotal > 21) {
				cout << "Dealer Busts - YOU WIN!" << endl;
			}
			// Player and Dealer both got a blackjack (push)
			else if (playerTotal == 21 && turn == 1 && dealerTotal == 21) {
				cout << "Its a push! Nobody wins this round" << endl;
			}
			// Player got a blackjack but dealer didn't
			else if (playerTotal == 21 && turn == 1 && dealerTotal < 21) {
				cout << "Dealer does not have a blackjack! YOU WIN!" << endl;
			}
			// Dealer got a blackjack but Player didn't
			else if (playerTotal < 21 && dealerTotal == 21) {
				cout << "Dealer got a blackjack! YOU LOSE!" << endl;
			}
			// Player did not get a blackjack and dealer has not busted or gotten a blackjack
			else if (playerTotal <= 21 && dealerTotal <= 21)
			{
				// Draw until they get over 16
				while (dealerTotal <= 16) {
					// Draw card
					dealerHand.addCard(gameDeck);
					dealerTotal = dealerHand.calculateTotal();
					cout << "============================================================" << endl;
					cout << "Dealer will draw...\nDealer has the following cards:" << endl;
					dealerHand.displayHand();
					cout << "\tTOTAL: " << dealerTotal << endl << endl;
				}
				// Check for bust
				if (dealerTotal > 21) {
					cout << "Dealer busted. YOU WIN!" << endl;
				}
				// check to see who won
				else if (dealerTotal > playerTotal) {
					cout << "Dealer has a higher total. YOU LOSE!" << endl;
				}
				else if (dealerTotal < playerTotal) {
					cout << "You have a higher total. YOU WIN!" << endl;
				}
				else {
					cout << "You have the same total. Its a push! (TIE)" << endl;
				}
			}
		}

		// Ask to play again
		cout << "Would you like to go again? Y or N: ";
		getline(cin, again);
		while (again != "Y" && again != "N") {
			cout << "Please enter a valid choice: ";
			getline(cin, again);
		}
		// Reset totals if yes
		if (again == "Y") {
			turn = 0;
			playerTotal = 0;
			dealerTotal = 0;
			keepDrawing = "Y";
		}
		else {
			break;
		}
	}


}
// Code for Hangman ===============================================================================================================================

// PRE: receives a string
// POST: returns true or false if string contains only lowercase alphabetical characters
bool isAlphabet(string str) {
	return str.find_first_not_of("abcdefghijklmnopqrstuvwxyz") == string::npos;
}


/*
* open file and check if its good
* read the fike and add each word to a vector
* greet the user
* begin game while loop
*	display hidden word (for each character in real word, add a ? to the hidden word)
*	get user guess
*	for each character
*		check if the guess character matches the character in the real string
*		update hidden word for every correct character
*	if the hidden word is the same as it was before (then the guess was not right)
*		remove a guess remaining
*	else
*		continue on with the game
*	if hidden word matches real word
*		user wons - prompt accordingly
*	else if guesses left is 0
*		user loses - prompt accordingly
* 
*	if the hidden word is the same as the real word or guesses is 0 (game is over)
*		ask if they want to play again
*	
*	if play again
*		generate a new random word
*		create a new hidden word
*		reset guesses remaining
* end while
* 
* close file
*		
*	
*	
*/
void hangman() {
	// Open file
	ifstream inFile;
	inFile.open("words.txt");

	// Check if file is good
	if (!inFile.good()) {
		cout << "error in input file" << endl;
		return;
	}

	// Read the file and put words into the vector
	string word, hiddenWord, realWord, guess, tempWord;
	vector<string> words;
	int guessesRemaining = 6;
	string again = "Y";

	while (getline(inFile, word)) {
		words.push_back(word);
	}

	// Pick a random word
	int wordPos = rand() % words.size();
	realWord = words[wordPos];

	// Setup guess word
	hiddenWord = "";
	for (char ch : realWord)
		hiddenWord += "?";

	// Greet and tell how many lives
	cout << "WELCOME TO HANGMAN!\nYou have 6 tries to guess the hidden word!" << endl;

	// Keep going until the user doesn't want to play
	while (again == "Y") {

		// Display hidden
		cout << "\nThe hidden word is: " << hiddenWord << endl;

		// Enter guess
		cout << "Enter a letter to guess: ";
		getline(cin, guess);
		while (!isAlphabet(guess) || guess.length() != 1) {
			cout << endl;
			cout << "Invalid guess input. Please try again: ";
			getline(cin, guess);
		}

		// Check if correct and update hidden word and number of guesses left
		tempWord = hiddenWord;
		for (int i = 0; i < realWord.length(); i++) {
			if (realWord[i] == guess[0]) {
				hiddenWord[i] = guess[0];
			}
		}

		// Compare to previous
		if (hiddenWord == tempWord) { // Guessed Incorrectly
			guessesRemaining -= 1;
			cout << "\nIncorrect Guess. You now have: " << guessesRemaining << " guesses remaining" << endl;
		}
		else // Guesses correctly
			cout << "\nNice Guess! You still have: " << guessesRemaining << " guesses remaining" << endl;

		// Check win
		if (hiddenWord == realWord) {
			cout << "You WON! The hidden word was: " << realWord << endl;
		}
		else if (guessesRemaining == 0){
			cout << "You LOST! :P The hidden word was: " << realWord << endl;
		}

		// Ask to play again
		if (hiddenWord == realWord || guessesRemaining == 0) {
			cout << "\nDo you want to play again? Y or N: ";
			getline(cin, again);
			while (again != "Y" && again != "N") {
				cout << "Please enter a valid choice: ";
				getline(cin, again);
			}
			// Game will quit if again became N, reset game if still Y
			if (again == "Y") { // Reset Game
				// Pick a random word
				int wordPos = rand() % words.size();
				realWord = words[wordPos];
				guessesRemaining = 6;

				// Setup guess word
				hiddenWord = "";
				for (char ch : realWord)
					hiddenWord += "?";

			}
		}

	}
	// close file
	inFile.close();
}