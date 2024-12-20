#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
// Game class keeps track of the state of a single game
class Game
{
public:
	// Quantity of numbers that are part of the game
	static const int NUMBERS_COUNT = 6;

	

private:
	// Array of numbers (0 if a spot is empty)
	int numbers[NUMBERS_COUNT];

	// Target (goal the user is going for)
	int target;

public:
	Game(int numLarge);
    Game();
	void displayNumbers();
	void addNumber(int num);
	bool wonGame();
	bool lostGame();
	bool gameOver();
	bool removeNumber(int userNumber);
	int performOperation(int num1, char operation, int num2);
    bool solve(Game game, std::vector <std::string>& solutionsteps);

};

