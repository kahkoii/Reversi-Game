#include "AI.h"

const int blackDisc = 1;
const int whiteDisc = 0;
const int emptyCell = -1;


void AI::init(int aiPlayer) {
	_aiPlayer = aiPlayer;
	if (_aiPlayer == blackDisc) {
		_humanPlayer = whiteDisc;
	}
	else {
		_humanPlayer = blackDisc;
	}
}

void AI::performMove(Board& board) {

}

AiMove AI::getBestMove(Board& board, int depth, int player) {
	if (depth == 0) {
		
	}

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (board.GetPieceColour(x, y) == -1) {
				AiMove move;
				move.x = x;
				move.y = y;

			}
		}
	}
}