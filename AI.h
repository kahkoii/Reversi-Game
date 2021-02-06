#pragma once
#include "Board.h"

struct AiMove {
	int x;
	int y;
	int score;
};

class AI {
public:
	// Initialize AI player
	void init(int aiPlayer);
	// Perform AI move
	void performMove(Board& board);

private:
	AiMove getBestMove(Board& board, int depth, int player);

	int _aiPlayer;
	int _humanPlayer;
};

