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

AiMove AI::performMove(Board& board) {
	AiMove bestMove = getBestMove(board, 3, _aiPlayer, AiMove(0));
	return bestMove;
}

AiMove AI::getBestMove(Board& board, int depth, int player, AiMove moveTemp) {
	if (depth == 0) {
		std::cout << "depth0: " << moveTemp.x + 1 << "-" << moveTemp.y + 1 << "\n";
		if (player == _humanPlayer) {
			int flips = board.Foresight(moveTemp.y, moveTemp.x, _aiPlayer);
			std::cout << "a flips: " << flips << "\n";
			return AiMove(flips);
		}
		if (player == _aiPlayer) {
			int flips = board.Foresight(moveTemp.y, moveTemp.x, _humanPlayer);
			std::cout << "h flips: "<< flips << "\n";
			return AiMove(-flips);
		}
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

				std::cout << move.x + 1 << move.y + 1 << "-" << depth << "-" << player << "\n";
				board.Print();

				if (player == _aiPlayer) {
					move.score = getBestMove(board, depth - 1, _humanPlayer, move).score;
				}
				else {
					move.score = getBestMove(board, depth - 1, _aiPlayer, move).score;
				}

				std::cout << move.x + 1 << move.y + 1 << "-" << move.score << "-" << depth <<"\n";
				moves.push_back(move);
				board = boardCopy; // Return board to previous state
				board.Print();
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