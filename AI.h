#pragma once
#include "Board.h"

struct AiMove {
	AiMove() {};
	AiMove(int Score) : score(Score) {};
	int x{};
	int y{};
	int score{};
};

class AI {
public:
	// Initialize AI player
	void init(int aiPlayer);
	// Perform AI move
	AiMove performMove(Board& board);

private:
	AiMove getBestMove(Board& board, int depth, int player, AiMove move);

	int _aiPlayer;
	int _humanPlayer;
};

