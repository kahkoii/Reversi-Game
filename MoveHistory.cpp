#include "MoveHistory.h"

MoveHistory::MoveHistory() : first(NULL), current(NULL), last(NULL), currentMove(0), totalMoves(0) {}

MoveHistory::~MoveHistory(){
	/*
	while (first != NULL) {
		current = first;
		first = first->next;
		delete current;
	}*/
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
	ApplyChangeFilter();
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

void MoveHistory::ApplyChangeFilter() {
	if (last->previous != NULL) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				// Check if latest tile is null
				if (last->grid[i][j] != -1) {
					// Check if current tile is diff from previous
					if (last->previous->grid[i][j] != last->grid[i][j]) {
						// Change null to placed
						if (last->previous->grid[i][j] == -1) {
							if (last->grid[i][j] == 0)
								last->grid[i][j] = 4;
							else
								last->grid[i][j] = 5;
						}
						else if (last->previous->grid[i][j] == 2) {
							// If new white has no changes, return to white
							if (last->grid[i][j] == 0)
								last->grid[i][j] = 0;
							// Replace new white with new black
							else
								last->grid[i][j] = 3;
						}
						else if (last->previous->grid[i][j] == 3) {
							// If new black no changes, return to black
							if (last->grid[i][j] == 1)
								last->grid[i][j] = 1;
							// Replace new black with new white
							else
								last->grid[i][j] = 2;
						}
						else if (last->previous->grid[i][j] == 4) {
							// If placed white has no changes, return to white
							if (last->grid[i][j] == 0)
								last->grid[i][j] = 0;
							// Replace placed white with captured black
							else
								last->grid[i][j] = 3;
						}
						else if (last->previous->grid[i][j] == 5) {
							// If placed black has no changes, return to black
							if (last->grid[i][j] == 1)
								last->grid[i][j] = 1;
							// Replace placed black with captured white
							else
								last->grid[i][j] = 2;
						}
						// Replace new white to white
						else if (last->grid[i][j] == 0) {
							last->grid[i][j] = 2;
						}
						// Replace new black to black
						else {
							last->grid[i][j] = 3;
						}
					}
				}
			}
		}
	}
}

void MoveHistory::Print() {
	cout << endl << "   1   2   3   4   5   6   7   8\n";
	for (int i = 0; i < 8; i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < 8; j++) {
			if (current->grid[i][j] == 0)
				cout << "\033[43;37m O \033[0m"; // white
			else if (current->grid[i][j] == 1)
				cout << "\033[43;30m O \033[0m"; // black
			else if (current->grid[i][j] == 2)
				cout << "\033[42;37m O \033[0m"; // new white
			else if (current->grid[i][j] == 3)
				cout << "\033[42;30m O \033[0m"; // new black
			else if (current->grid[i][j] == 4)
				cout << "\033[44;37m O \033[0m"; // placed white
			else if (current->grid[i][j] == 5)
				cout << "\033[44;30m O \033[0m"; // placed black
			else
				cout << "\033[43;31m   \033[0m"; // null
			if (j != 7)
				cout << "\033[43;30m|\033[0m";
		}
		if (i == 3)
			cout << "\033[30; 30m . \033[0m" << "\n  \033[43;30m-------------------------------\033[0m Y\n";
		else if (i != 7)
			cout << "\033[30; 30m . \033[0m" << "\n  \033[43;30m-------------------------------\033[0m" << "\033[30; 30m . \033[0m\n";
	}
	cout << "\033[30; 30m . \033[0m" << "\n   . . . . . . . X . . . . . . . .\n\n";
}