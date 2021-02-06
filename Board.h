#include <iostream>
#include "Node.h"
#pragma once
using namespace std;

class Board
{
private:
	Node* board[8][8];
	int totalPieces;
	bool CheckValidity(int row, int col, int colour);

public:
	Board();

	~Board();

	// Gets the total number of pieces on the board
	int GetPieces();

	// Gets the colour of the piece at the stated coordinates
	int GetPieceColour(int x, int y);

	// Updates the 8x8 array passed in with the board state
	void UpdateGrid(int grid[8][8]);

	// Places a piece and updates the board accordingly
	bool PlacePiece(int row, int col, int colour);

	// Takes in an 8x8 array and sets the board to that state
	void SetBoard(int grid[8][8]);

	// Returns the number of enemy pieces captured if the move is made
	int Foresight(int row, int col, int colour);

	// Prints the current board state, W - white, B- Black, O - Empty
	void Print();
};

