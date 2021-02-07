#include <iostream>
#include <vector>
#pragma once
using namespace std;

typedef int Grid[8][8];

struct Move {
	Move* previous;
	Move* next;
	Grid grid;
};

class MoveHistory
{
private:
	Move* first;
	Move* current;
	Move* last;
	int currentMove;
	int totalMoves;
	char winner;

	// Changes the latest grid to reflect what changed
	void ApplyChangeFilter();
	// -1 null, 0 white, 1 black, 2 new white, 3 new black

public:
	MoveHistory();

	~MoveHistory();

	// Insert a move to the back of the linked list
	void Insert(Grid);

	// Get current move
	int GetCurrentMove();

	// Get the total number of moves
	int GetTotalMoves();

	// Set winner of the match
	void SetWinner(char result);

	// Get winner
	char GetWinner();

	// Move to the next move
	bool Next();

	// Move to the previous move
	bool Previous();

	// Print the current move in the history list
	void Print();

};

