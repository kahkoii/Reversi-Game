#include "Board.h"

const int iterateModes[4] = { 1, 2, 3, 4 };
const int iterateDirections[2] = { -1, 1 };

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
		for (int j = 1; j < 7; j++) {
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
	
	// Intialize variables
	totalPieces = 0;
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

int Board::GetPieceColour(int x, int y) {
	return board[y][x]->GetColour();
}

void Board::UpdateGrid(int grid[8][8]){
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			grid[i][j] = board[i][j]->GetColour();
		}
	}
}

bool Board::PlacePiece(int row, int col, int colour) {
	// Check if there is already a piece
	if (board[row][col]->GetColour() == -1){
		if (CheckValidity(row, col, colour)) {
			board[row][col]->SetColour(colour);
			board[row][col]->FlipRequest(colour);
			totalPieces += 1;
			return true;
		}
	}
	return false;
}

bool Board::CheckValidity(int row, int col, int colour) { //TODO
	return true;
}

void Board::SetBoard(int grid[8][8]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j]->SetColour(grid[i][j]);
		}
	}
}

int Board::Foresight(int row, int col, int colour) {
	int currentGrid[8][8], changes = -1;
	UpdateGrid(currentGrid);
	PlacePiece(row, col, colour);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j]->GetColour() != currentGrid[i][j])
				changes += 1;
		}
	}
	SetBoard(currentGrid);
	return changes;
}

bool Board::Iterate(int& y, int& x, const int mode, const int direction) {

	if ((direction != 1) && (direction != -1))
		return false;

	switch (mode) {
	case(1):
		x += direction;
		return true;
	case(2):
		y += direction;
		return true;
	case(3):
		y += direction;
		x += direction;
		return true;
	case(4):
		y += direction;
		x -= direction;
		return true;
	default:
		cout << "THROWING BECAUSE mode = " << mode << endl;
		throw;
	}
}

bool Board::OnFrontier(int y, int x) {
	if (board[y][x]->GetColour() == -1)
		return false;
	for (int n = 0; n < 4; n++) {
		int mode = iterateModes[n];
		for (int m = 0; m < 2; m++) {
			int direction = iterateDirections[m];
			int Y = y, X = x;
			Iterate(Y, X, mode, direction);
			if (x > 8 || x < 1 || y > 8 || y < 0)
				if (board[Y][X]->GetColour() != -1)
					return true;
		}
	}
	return false;
}

vector<Coordinates> Board::UpdateMoveSet(int colour, bool print) {
	vector<Coordinates> vec;
	string moves = "\nPossible Moves: ";
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			// If the tile is null, check if move captures
			if (board[i][j]->GetColour() == -1) {
				if (Foresight(i, j, colour) > 0) {
					Coordinates c = Coordinates(j, i);
					moves = moves + "(" + to_string(j + 1) + ", " + to_string(i + 1) + ") ";
					vec.push_back(c);
				}
			}
			else continue;
		}
	}
	if (print) cout << moves << endl << endl;
	return vec;
}

bool Board::ValidCoordinates(vector<Coordinates> &vec, Coordinates c) {
	for (Coordinates &i : vec) {
		if (i.x == c.x && i.y == c.y)
			return true;
	}
	return false;
}

int Board::GetScore(int colour) {
	int score = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j]->GetColour() == colour)
				score++;
		}
	}
	return score;
}

char Board::GetWinner() {
	int w = 0, b = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j]->GetColour() == 0)
				w++;
			else if (board[i][j]->GetColour() == 1)
				b++;
		}
	}
	cout << "\n==============================\n[Final Score]\n";
	cout << "White: " << w << " Black: " << b << "\n==============================\n";
	if (w > b) return 'w';
	else if (b > w) return 'b';
	else return 't';
}

void Board::Print() {
	int current;
	cout << endl << "   1   2   3   4   5   6   7   8\n";
	for (int i = 0; i < 8; i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < 8; j++) {
			current = board[i][j]->GetColour();
			if (current == 0)
				cout << "\033[42;37m O \033[0m";
			else if (current == 1)
				cout << "\033[42;30m O \033[0m";
			else
				cout << "\033[42;31m   \033[0m";
			if (j != 7)
				cout << "\033[42;30m|\033[0m";
		}
		if (i == 3)
			cout << "\033[30; 30m . \033[0m" << "\n  \033[42;30m-------------------------------\033[0m Y\n";
		else if (i != 7)
			cout << "\033[30; 30m . \033[0m" << "\n  \033[42;30m-------------------------------\033[0m" << "\033[30; 30m . \033[0m\n";
	}
	cout << "\033[30; 30m . \033[0m" << "\n   . . . . . . . X . . . . . . . .\n\n";
}