#include <iostream>
#pragma once
using namespace std;

class Node
{
private:
	int Colour; //0 for white, 1 for black, -1 for empty
	Node* N;
	Node* NE;
	Node* E;
	Node* SE;
	Node* S;
	Node* SW;
	Node* W;
	Node* NW;

public:
	Node();

	~Node();

	void LinkNodes(Node* n, Node* ne, Node* e, Node* se, Node* s, Node* sw, Node* w, Node* nw);

	void SetColour(int colour);

	int GetColour();

	void Flip();

	bool FlipRequest(int colour);

	bool FlipRequest(int colour, string direction);
};

