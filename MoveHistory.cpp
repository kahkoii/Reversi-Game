#include "MoveHistory.h"

MoveHistory::MoveHistory() : first(NULL), current(NULL), last(NULL), currentMove(0), totalMoves(0) {}

MoveHistory::~MoveHistory(){
	first = NULL;
	current = NULL;
	last = NULL;
	currentMove = 0;
	totalMoves = 0;
}

void MoveHistory::Insert(Grid grid) {
	Move* move = new Move;
	move->previous = NULL;
	move->next = NULL;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			move->grid[i][j] = grid[i][j];
		}
	}
	if (totalMoves == 0) {
		first = move;
		current = move;
		last = move;
	}
	else if (totalMoves == 1){
		first->next = move;
		move->previous = first;
		last = move;
	}
	else {
		last->next = move;
		move->previous = last;
		last = move;
	}
	totalMoves++;
}

int MoveHistory::GetCurrentMove() { return currentMove; }

int MoveHistory::GetTotalMoves() { return totalMoves; }

bool MoveHistory::Next() {
	if (currentMove == totalMoves - 1)
		return false;
	else {
		current = current->next;
		currentMove++;
		return true;
	}
}

bool MoveHistory::Previous() {
	if (currentMove == 0)
		return false;
	else {
		current = current->previous;
		currentMove--;
		return true;
	}
}

void MoveHistory::Print() {
	cout << endl << "   1   2   3   4   5   6   7   8\n";
	for (int i = 0; i < 8; i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < 8; j++) {
			if (current->grid[i][j] == 0)
				cout << "\033[43;37m O \033[0m"; //TEST 42 to 43
			else if (current->grid[i][j] == 1)
				cout << "\033[43;30m O \033[0m";
			else
				cout << "\033[43;31m   \033[0m";
			if (j != 7)
				cout << "\033[43;30m|\033[0m";
		}
		if (i == 3)
			cout << "\033[30; 30m . \033[0m" << "\n  \033[42;30m-------------------------------\033[0m Y\n";
		else if (i != 7)
			cout << "\033[30; 30m . \033[0m" << "\n  \033[42;30m-------------------------------\033[0m" << "\033[30; 30m . \033[0m\n";
	}
	cout << "\033[30; 30m . \033[0m" << "\n   . . . . . . . X . . . . . . . .\n\n";
}