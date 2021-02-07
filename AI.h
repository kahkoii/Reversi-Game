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
	AiMove getBestMove(Board board, bool dispAI);

private:
	int performMiniMax(Board board, int depth, int player, bool dispAI);
	int heuristic(Board b);

	int _aiPlayer;
	int _humanPlayer;
};

