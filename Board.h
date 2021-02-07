#include <iostream>
#include <vector>
#include <string>
#include "Node.h"
#pragma once
using namespace std;

// Start from 0, x and y correspond to col and row respectively
struct Coordinates {
	int x, y;
	Coordinates(int a, int b) { x = a; y = b; }
};

class Board
{
private:
	Node* board[8][8];
	int totalPieces;
	bool CheckValidity(int row, int col, int colour);

	// method to iterate through the board in one direction
	bool Iterate(int& y, int& x, const int mode, const int direction);

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

	// checks whether a piece is on the frontier
	bool OnFrontier(int y, int x);

	// Returns a vector with the coordinates of all possible moves
	vector<Coordinates> UpdateMoveSet(int colour, bool print = false);

	// Check if coordinate is in the moveset
	bool ValidCoordinates(vector<Coordinates>& vec, Coordinates c);

	// Get score of selected colour
	int GetScore(int colour);

	// Returns the winner, 'w' - white, 'b' - black, 't' - tie
	char GetWinner();

	// Prints the current board state, W - white, B- Black, O - Empty
	void Print();
};

