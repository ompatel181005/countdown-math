/* This is the Math Countdown game in which the player is given 6 random numbers and one random
target number and user have to use mathematical operation on those 6 numbers to reach the target
if they are able to do so they win the game or else they lose it. out of 6 numbers user is given option
to have upto 4 big numbers which are multiples of 25(25,50,75,100) and other are small numbers between 1-10.
In cotinuation of the math countdon game there is option to undo and solve. when user undo's he gets the 
numbers before doing the last calculation and solve tries to find a solution with the existing numbers and prints it out to user.  
Om Patel / CS 141 / Project 6 / 12/06/2024  
*/
#include <iostream>
#include <string>
#include <sstream>
#include "mersenne-twister.h"
#include "Game.h"
#include "GameList.h"
#include <vector>
using namespace std;

int promptAndGetNumLarge();
void processCalculation(string userInput, int& num1, char& operation, int& num2);
// function of game class to solve to reach the target with given numbers
bool Game :: solve(Game game, vector<string>& solutionsteps){
	// if game is already won return true
    if (game.wonGame()){
		return true;
	
	}
    // iterate through every number perform operations on them 
	for (int i = 0; i < Game::NUMBERS_COUNT; ++i){
        // operate with the next number
		for(int j =0; j < Game::NUMBERS_COUNT; ++j ){
            // if i and j are same or either of the number is 0 don't do any operations
			if (i != j && game.numbers[i] != 0 && game.numbers[j] != 0){
                // all the operands that we use to do operations
				char operations[] = {'+','-','*','/'};
				for (char op : operations){
                    // create a copy of the current game and do the operations and save results in that copy
					Game tempGame = game;
                    
					int num1 = tempGame.numbers[i];
					int num2 = tempGame.numbers[j];
					int result = tempGame.performOperation(num1,op,num2);
					
                    // remove the numbers on which operation is done and add the result of it game array
					tempGame.removeNumber(num1);
					tempGame.removeNumber(num2);
					tempGame.addNumber(result);
					
                    // make a string stream to store the operation that was done
					stringstream step;
					step << num1 << " " << op << " " << num2 << " = " << result;
                    // store it in the solution steps vector
					solutionsteps.push_back(step.str());
                    // recursively call the function again to try it on other numbers and check for other combinations
					if (solve (tempGame,solutionsteps)){
						return true;
					}
                    // if there is no solution then delete the stored stringstream 
					solutionsteps.pop_back();


				}
            }
        }
    }
    //check again if the target is met 
    if (game.wonGame()){
		return true;
	
	}
    //check again for the same numbers with reverse order to make sure that no case is left 
	for (int i = 0; i < Game::NUMBERS_COUNT; ++i){
		for(int j =0; j < Game::NUMBERS_COUNT; ++j ){
			if (i !=j && game.numbers[i] != 0 && game.numbers[j] != 0){
                char operations[] = {'+','-','*','/'};
                for (char op : operations){
					Game tempGame = game;
					int num1 = tempGame.numbers[j];
					int num2 = tempGame.numbers[i];
					int result =  tempGame.performOperation(num1,op,num2);

					tempGame.removeNumber(num1);
					tempGame.removeNumber(num2);
					tempGame.addNumber(result);

					stringstream step;
					step << num1 << " " << op << " " << num2 << " = " << result;
					solutionsteps.push_back(step.str());

					if (solve (tempGame,solutionsteps)){
						return true;
					}

					solutionsteps.pop_back();
					

				}
            }
		}
	}
    // return false in the end if no solution is find 
	return false;

}

int main() {
	// Input a random seed for the program, and call the seed function
	int randSeed;
	cout << "Enter random seed: ";
	cin >> randSeed;
	seed(randSeed);

	// userContinue is used to input whether the user wants to continue to play another game
	string userContinue;
	do {
		// Get the quantity of large numbers
		int numLarge = promptAndGetNumLarge();

		// Create the game variable, using that quantity of large numbers
		Game game(numLarge);
        // create linked list
        GameList gameHistory;
        gameHistory.addGame(game);

		// Clear newline from previous input
		string userInput;
		getline(cin, userInput);

		// Repeat until the game is over
		while (!game.gameOver()) {
			// Display the available numbers and get the user's calculation input
			game.displayNumbers();
			cout << "Enter a calculation (or U to Undo, S to Solve, or Q to Quit): ";
			getline(cin, userInput);

			// Quit this game if the user choses Q, but don't exit the program (the user might play another game)
			if (userInput == "q" || userInput == "Q") {
				cout << "Exiting this game." << endl;
				break;
			}
            //  if the user enters u then perorm undo
            if (userInput == "u" || userInput == "U"){
                if (gameHistory.undoGame()){
                    // if undo is possible then update it with the latest game 
                    game = gameHistory.getCurrentGame();
                }
                continue;
                
                
                
            }
            // if the user enter s solve and print the solution
			if (userInput == "s" || userInput == "S"){
                vector<string> solutionsteps;
                Game gamecopy = game;
                // if solution exists then print the solution 
                if (gamecopy.solve(gamecopy,solutionsteps)){
					cout << endl;
					cout << "Solution:" << endl;
					for (string& step: solutionsteps){
						cout << step << endl;
					}
					cout << endl;
					continue;
                    
                }
                // else print out no solution is find 
				else{
					cout<< "Unable to find a solution." << endl;
					continue;
				}
                
            }

			// Get the numbers and operation from the user's input
			int num1;
			char operation;
			int num2;
			processCalculation(userInput, num1, operation, num2);

			// Make sure num1 and num2 are in the list of numbers
			if (!game.removeNumber(num1)) {
				// num1 was not found, display error message
				cout << num1 << " is not a valid number." << endl;
			}
			else if (!game.removeNumber(num2)) {
				// num2 was not found, display error message
				cout << num2 << " is not a valid number." << endl;
				// add num1 back into the list, since it was removed in the previous if condition
				game.addNumber(num1);
			}
			else {
				// num1 and num2 are in our list, perform the operation and display the equation
				int result = game.performOperation(num1, operation, num2);
				cout << num1 << " " << operation << " " << num2 << " = " << result << endl << endl;

				// Add the result to the list of numbers
				game.addNumber(result);
                // add  the new game to linked list
                gameHistory.addGame(game);
				// Display win or lose messages if appropriate
				if (game.wonGame()) {
					cout << "You win!" << endl;
				} else if (game.lostGame()) {
					cout << "You lose." << endl;
				}
			}
		}

		// Ask user if they want to continue, do so if they type Y or y
		cout << endl;
		cout << "Would you like to play again (y/n)? ";
		getline(cin, userContinue);
	} while (userContinue == "y" || userContinue == "Y");
}

// Display the greeting and the prompt for choosing big numbers
// Repeats until a valid big number is entered (must be 0-4)
// Returns a valid number of big numbers chosen by the user (0-4)
int promptAndGetNumLarge() {
	int numLarge = 0;

	// Display prompt and get the input
	cout << endl;
	cout << "Let's play Countdown!" << endl;
	cout << "How many big numbers would you like (0-4)? ";
	cin >> numLarge;

	// Repeat if the input isn't valid (valid is between 0 and 4, inclusive)
	while (numLarge < 0 || numLarge > 4) {
		cout << "That's not a valid number. You must choose between 0 and 4." << endl;
		cout << "How many large numbers would you like? ";
		cin >> numLarge;
	}

	// Return the number chosen
	return numLarge;
}

// Determines the pieces of a calculation from the user input
// Parameters:
// userInput is the string, for example "2+3"
// num1 is passed by reference to return the first number in the calculation (the 2 in the above example)
// operation is passed by reference to return the operation in the calculation ('+' in the above example)
// num2 is passed by reference to return the second number in the calculation (the 3 in the above example)
// Function doesn't return a value, it uses the reference variables to return the information
// Will cause an exception if userInput is anything but a valid operation
void processCalculation(string userInput, int& num1, char& operation, int& num2) {
	// Use a stringstream (essentially turning the given string into a stream)
	stringstream ss(userInput);

	// Input the first number, then the operation, and then the second number from that stream
	ss >> num1 >> operation >> num2;
}