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

public:
	Board();

	~Board();

	int GetPieces();

	// Gets a pointer to a 2D array
	int* GetBoard();

	bool PlacePiece(int row, int col, int colour);
};

