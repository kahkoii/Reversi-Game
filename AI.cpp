#include <vector>
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
	AiMove bestMove = getBestMove(board, 3, _aiPlayer, AiMove(0));
	board.PlacePiece(bestMove.y, bestMove.x, _aiPlayer);
}

AiMove AI::getBestMove(Board board, int depth, int player, AiMove moveTemp) {
	if (depth == 0) {
		int flips = board.Foresight(moveTemp.y, moveTemp.x, player);
		return AiMove(flips);
	}

	std::vector<AiMove> moves;

	// Do recursive function calls and construct moves vector
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if ((board.GetPieceColour(x, y) == emptyCell) && (board.Foresight(y, x, player)) > 0) {
				AiMove move;
				move.x = x;
				move.y = y;

				Board boardCopy = board;
				if (depth > 1) { board.PlacePiece(y, x, player); }

				if (player == _aiPlayer) {
					move.score = getBestMove(board, depth - 1, _humanPlayer, move).score;
				}
				else {
					move.score = getBestMove(board, depth - 1, _aiPlayer, move).score;
				}

				moves.push_back(move);
				board = boardCopy; // Return board to previous state
			}
		}
	}

	// Pick best move for current player
	int bestMove = 0;
	if (player == _aiPlayer) {
		// AI is Maximizer
		int bestScore = -1000000;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score > bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}
	else {
		// Human is Minimizer
		int bestScore = 1000000;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score < bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}
	
	// Return best move
	return moves[bestMove];
}