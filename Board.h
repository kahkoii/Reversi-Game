#include <iostream>
#include "Node.h"
#pragma once
using namespace std;

class Board
{
private:
	Node* board[8][8];
	int grid[8][8];
	int totalPieces;
	bool CheckValidity(int row, int col, int colour);

public:
	Board();

	~Board();

	// Gets the total number of pieces on the board
	int GetPieces();

	// Updates the 8x8 array passed in with the board state
	void UpdateGrid(int grid[8][8]);

	// Places a piece and updates the board accordingly
	bool PlacePiece(int row, int col, int colour);

	// Prints the current board state, W - white, B- Black, O - Empty
	void Print();
};

