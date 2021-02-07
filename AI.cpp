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

AiMove AI::getBestMove(Board board, bool dispAI) {
	int depth, eval, moveNum;
	// int depthLimit = 64 - board.GetPieces();
	int depthLimit = 3;
	AiMove move, bestMove;

	vector<AiMove> moves;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if ((board.GetPieceColour(x, y) == emptyCell) && (board.Foresight(y, x, _aiPlayer)) > 0) {
				AiMove move2;
				move2.x = x;
				move2.y = y;
				moves.push_back(move2);
			}
		}
	}
	for (depth = 0; depth < depthLimit; depth++) {
		int alpha = INT_MIN, beta = INT_MAX, randMove = 1;
		for (int i = 0; i < moves.size(); i++) { //maximize alpha
			int currentGrid[8][8];
			board.UpdateGrid(currentGrid);
			Board child;
			child.SetBoard(currentGrid);

			child.PlacePiece(moves[i].y, moves[i].x, _aiPlayer);
			eval = performMiniMax(child, depth, _aiPlayer, dispAI);

			if (eval > alpha) {
				move = moves[i];
				moveNum = i;
				alpha = eval;
			}
			else if (eval == alpha) {
				//use the new move instead of the existing one with uniform probabilty
				if (((rand() % randMove++) - 1) == 0) {
					move = moves[i];
					moveNum = i;
				}
			}
		}

	}
	bestMove = move;
	
	return bestMove;
}

int AI::heuristic(Board b) {
	double piececount, corners, potentialCorners, edges, frontier, mobility;
	int mine, opp;

	//set weights of heuristic parameters
	int pW = 2 * (b.GetScore(_aiPlayer) + b.GetScore(_humanPlayer));
	int cW = 5000;
	int pcW = 2000;
	int fW = 200;
	int eW = 50;
	int mW = 10 * (100 - (b.GetScore(_aiPlayer) + b.GetScore(_humanPlayer)));

	//piece count
	piececount = (100.0 * b.GetScore(_aiPlayer)) / (b.GetScore(_aiPlayer) + b.GetScore(_humanPlayer));

	//corners
	mine = 0, opp = 0;
	if (b.GetPieceColour(0, 0) == _aiPlayer) mine++;
	else if (b.GetPieceColour(0, 0) == _humanPlayer) opp++;
	if (b.GetPieceColour(0, 7) == _aiPlayer) mine++;
	else if (b.GetPieceColour(0, 7) == _humanPlayer) opp++;
	if (b.GetPieceColour(7, 0) == _aiPlayer) mine++;
	else if (b.GetPieceColour(7, 0) == _humanPlayer) opp++;
	if (b.GetPieceColour(7, 7) == _aiPlayer) mine++;
	else if (b.GetPieceColour(7, 7) == _humanPlayer) opp++;
	corners = 25.0 * (mine - opp);

	//edges and frontier
	int myEdges = 0, oppEdges = 0;
	int myFrontier = 0, oppFrontier = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == 0 || i == 8 - 1 || j == 0 || j == 8 - 1) {
				if (b.GetPieceColour(i, j) == _aiPlayer) myEdges++;
				else if (b.GetPieceColour(i, j) == _humanPlayer) oppEdges++;
			}
			else if (b.GetPieceColour(i, j) != '0') {
				if (b.OnFrontier(i, j)) {
					if (b.GetPieceColour(i, j) == _aiPlayer) myFrontier++;
					else if (b.GetPieceColour(i, j) == _humanPlayer) oppFrontier++;
				}
			}
		}
	}
	edges = 100.0 * myEdges / (myEdges + oppEdges);
	frontier = -100 * (myFrontier - oppFrontier); //frontier pieces are bad!

	//mobility
	vector<AiMove> aiMoves;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if ((b.GetPieceColour(x, y) == emptyCell) && (b.Foresight(y, x, _aiPlayer)) > 0) {
				AiMove move;
				move.x = x;
				move.y = y;
				aiMoves.push_back(move);
			}
		}
	}
	vector<AiMove> humanMoves;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if ((b.GetPieceColour(x, y) == emptyCell) && (b.Foresight(y, x, _humanPlayer)) > 0) {
				AiMove move;
				move.x = x;
				move.y = y;
				aiMoves.push_back(move);
			}
		}
	}
	mobility = 100.0 * aiMoves.size() / (aiMoves.size() + humanMoves.size());

	//potential corners (pseudo-expand node)
	opp = 0;
	for (int i = 0; i < humanMoves.size(); i++) {
		if (humanMoves[i].y == 0 && humanMoves[i].x == 0) opp++;
		else if (humanMoves[i].y == 0 && humanMoves[i].x == (8 - 1)) opp++;
		else if (humanMoves[i].y == (8 - 1) && humanMoves[i].x == 0) opp++;
		else if (humanMoves[i].y == (8 - 1) && humanMoves[i].x == (8 - 1)) opp++;
	}
	potentialCorners = -25.0 * opp;

	return pW * piececount + cW * corners + pcW * potentialCorners + eW * edges + fW * frontier + mW * mobility;
}

int AI::performMiniMax(Board board, int depth, int player, bool dispAI) {
	if (dispAI) {
		board.Print();
	}
	if (depth == 0) {
		return heuristic(board);
	}
	else
		depth--;

	vector<AiMove> moves;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if ((board.GetPieceColour(x, y) == emptyCell) && (board.Foresight(y, x, player)) > 0) {
				AiMove move;
				move.x = x;
				move.y = y;
				moves.push_back(move);
			}
		}
	}
	int msize = moves.size();

	if (player == _aiPlayer) {
		int v = INT_MIN;
		for (int i = 0; i < msize; i++) {
			int currentGrid[8][8];
			board.UpdateGrid(currentGrid);
			Board child;
			child.SetBoard(currentGrid);

			child.PlacePiece(moves[i].y, moves[i].x, player);
			int eval = performMiniMax(child, depth, _humanPlayer, dispAI);

			v = ((v > eval) ? v : eval);
		}
		return v;
	}
	else {
		int v = INT_MAX;
		for (int i = 0; i < msize; i++) {
			int currentGrid[8][8];
			board.UpdateGrid(currentGrid);
			Board child;
			child.SetBoard(currentGrid);

			child.PlacePiece(moves[i].y, moves[i].x, player);
			int eval = performMiniMax(child, depth, _aiPlayer, dispAI);

			v = ((v < eval) ? v : eval);
		}
		return v;
	}
	
}

