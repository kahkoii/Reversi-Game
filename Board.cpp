#include "Board.h"
Board::Board() {
	// Creates and sets up the board with standard config
	// Fill the board array with empty nodes
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Node* node = new Node;
			board[i][j] = node;
		}
	}
	// Link the nodes after all nodes have been made
	// Top row
	board[0][0]->LinkNodes(NULL, NULL, board[0][1], board[1][1], board[1][0], NULL, NULL, NULL); //TOP L
	board[0][7]->LinkNodes(NULL, NULL, NULL, NULL, board[1][7], board[1][6], board[0][6], NULL); //TOP R
	for (int i = 1; i < 7; i++) {
		board[0][i]->LinkNodes(NULL, NULL, board[0][i + 1], board[1][i + 1], board[1][i], board[1][i - 1], board[0][i - 1], NULL);
	}

	// Middle rows
	for (int i = 1; i < 7; i++) {
		board[i][0]->LinkNodes(board[i - 1][0], board[i - 1][1], board[i][1], board[i + 1][1], board[i + 1][0], NULL, NULL, NULL); //L Node
		for (int j = 0; j < 7; j++) {
			board[i][j]->LinkNodes(board[i - 1][j], board[i - 1][j + 1], board[i][j + 1], board[i + 1][j + 1], board[i + 1][j], board[i + 1][j - 1], board[i][j - 1], board[i - 1][j - 1]);
		}
		board[i][7]->LinkNodes(board[i - 1][7], NULL, NULL, NULL, board[i + 1][7], board[i + 1][6], board[i][6], board[i - 1][6]); //R Node
	}

	// Bottom row
	board[7][0]->LinkNodes(board[6][0], board[6][1], board[7][1], NULL, NULL, NULL, NULL, NULL); //BTM L
	board[7][7]->LinkNodes(board[6][7], NULL, NULL, NULL, NULL, NULL, board[7][6], board[6][6]); //BTM R
	for (int i = 1; i < 7; i++) {
		board[7][i]->LinkNodes(board[6][i], board[6][i + 1], board[7][i + 1], NULL, NULL, NULL, board[7][i - 1], board[6][i - 1]);
	}

	// Set middle pieces
	board[3][3]->SetColour(0);
	board[3][4]->SetColour(1);
	board[4][3]->SetColour(1);
	board[4][4]->SetColour(0);
}

Board::~Board() {
	totalPieces = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j]->~Node();
		}
	}
}

int Board::GetPieces() {
	return totalPieces;
}

int* Board::GetBoard(){
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			grid[i][j] = board[i][j]->GetColour();
		}
	}
	return *grid;
}

bool Board::PlacePiece(int row, int col, int colour) {
	// Check if there is already a piece
	if (board[row][col]->GetColour() == NULL){
		if (CheckValidity(row, col, colour)) {
			board[row][col]->SetColour(colour);
			board[row][col]->FlipRequest(colour, "N");
			board[row][col]->FlipRequest(colour, "NE");
			board[row][col]->FlipRequest(colour, "E");
			board[row][col]->FlipRequest(colour, "SE");
			board[row][col]->FlipRequest(colour, "S");
			board[row][col]->FlipRequest(colour, "SW");
			board[row][col]->FlipRequest(colour, "W");
			board[row][col]->FlipRequest(colour, "NW");
			totalPieces += 1;
			return true;
		}
	}
	return false;
}

bool CheckValidity(int row, int col, int colour) { //TODO
	return true;
}