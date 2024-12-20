#include <iostream>
#include "Game.h"
#include "mersenne-twister.h"
#include <sstream>

using namespace std;



using namespace std;

// Constructor to initialize the game state
// Chooses random numbers and the target (goal)
// Parameter numLarge is the number (0-4) of large numbers
// Remaining of random numbers will be small
Game::Game(int numLarge) {
	// Sets the random numbers
	for (int i = 0; i < NUMBERS_COUNT; i++) {
		if (i < numLarge) {
			numbers[i] = chooseRandomNumber(1, 4) * 25;
		}
		else {
			numbers[i] = chooseRandomNumber(1, 10);
		}
	}

	// Sets the target
	target = chooseRandomNumber(101, 999);
}
// default constructor
Game::Game() {
	// Sets the random numbers
	for (int i = 0; i < NUMBERS_COUNT; i++) {
		numbers[i] = 0;
	}

	// Sets the target
	target = 0;
}

// Display numbers left for the users to choose and the target
void Game::displayNumbers() {
	cout << "Your numbers are: ";

	// Display all numbers remaining (skip 0s which indicate an open spot)
	for (int i = 0; i < NUMBERS_COUNT; i++) {
		if (numbers[i] != 0) {
			cout << numbers[i] << " ";
		}
	}
	cout << endl;

	cout << "The target is: " << target << endl;
}

// Add a number to the numbers available for the user to choose
// Parameter addNum is the number to add
void Game::addNumber(int addNum) {
	// Go through the available spots and put the new number at the first 0 (empty spot)
	for (int i = 0; i < NUMBERS_COUNT; i++) {
		if (numbers[i] == 0) {
			numbers[i] = addNum;
			return;
		}
	}

	cout << "Error: no space for added number!" << endl;
}

// Determine if the user has lost the game
// Returns true if the user has lost, falst if they have not (they've won or game is still going)
bool Game::lostGame() {
	// Winning takes priority--not a loss if the game has been won
	if (wonGame()) {
		return false;
	}

	// Look through each number, count the numbers that remain (aren't 0)
	int countNumbersRemain = 0;
	for (int i = 0; i < NUMBERS_COUNT; i++) {
		if (numbers[i] != 0) {
			countNumbersRemain++;
		}
	}
	if (countNumbersRemain <= 1){
		return true;
	}

	// If there is 1 or fewer number left, the user has lost
	return false;
}

// Removes the given number from the list of numbers to work with
// userNumber is the number to remove
// Returns true if the userNumber was found (and removed)
// Returns false if userNumber is not in the list
bool Game::removeNumber(int userNumber) {
	for (int i = 0; i < NUMBERS_COUNT; i++) {
		if (numbers[i] == userNumber) {
			numbers[i] = 0;
			// Return true, number was false
			return true;
		}
	}

	// Number wasn't found, return false
	return false;
}

// Calculates the answer of the specified operation
// operation is a character, either '+', '-', '*', or '/' to specify the type of calculation
// num1 and num2 are the two numbers (where order matters, num1 comes first, e.g. num1 - num2)
// Returns the result of the calculation
int Game::performOperation(int num1, char operation, int num2) {
	// Perform the calculation depending on the operation chosen
	// (Note: breaks not needed since return statement leaves the function)
	switch (operation) {
	case '+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	case '/':
		return num1 / num2;
	case '*':
		return num1 * num2;
	}

	// Error: invalid operation, return 0
	return 0;
}

// Determines if the user has won the game
// Returns true if user has won, false if they have lost or game still going
bool Game::wonGame() {
	// Look through available numbers
	for (int i = 0; i < NUMBERS_COUNT; i++) {
		// If target is found, return true
		if (numbers[i] == target) {
			return true;
		}
	}

	// Target not found
	return false;
}

// Determines if the game is over
// Returns true if game is over (user has either won or lost)
// Returns false if game still going
bool Game::gameOver() {
	return wonGame() || lostGame();
}

