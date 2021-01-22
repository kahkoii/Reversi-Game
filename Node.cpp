#include "Node.h"
Node::Node() {
	Colour = NULL;
	N = NULL;
	NE = NULL;
	E = NULL;
	SE = NULL;
	S = NULL;
	SW = NULL;
	W = NULL;
	NW = NULL;
}

Node::~Node() {
	Colour = NULL;
	N = NULL;
	NE = NULL;
	E = NULL;
	SE = NULL;
	S = NULL;
	SW = NULL;
	W = NULL;
	NW = NULL;
}

void Node::LinkNodes(Node* n, Node* ne, Node* e, Node* se, Node* s, Node* sw, Node* w, Node* nw) {
	N = n;
	NE = ne;
	E = e;
	SE = se;
	S = s;
	SW = sw;
	W = w;
	NW = nw;
}

void Node::SetColour(int colour) {
	Colour = colour;
}

int Node::GetColour() {
	return Colour;
}

void Node::Flip() {
	Colour = (Colour == 0) ? 1 : 0;
}

bool Node::FlipRequest(int colour, string direction) {
	// This function flips pieces accordingly, and returns 
	// a boolean that determines if something has been flipped
	if (Colour == NULL) {
		// If the edge is reached, stop the flip request
		return false;
	}
	else if (Colour != colour) {
		// If the current colour still does not match the colour of the
		// placed piece, continue sending requests in the same direction
		bool status;
		if (direction == "N")
			status = N->FlipRequest(colour, direction);
		else if(direction == "NE")
			status = NE->FlipRequest(colour, direction);
		else if (direction == "E")
			status = E->FlipRequest(colour, direction);
		else if (direction == "SE")
			status = SE->FlipRequest(colour, direction);
		else if (direction == "S")
			status = S->FlipRequest(colour, direction);
		else if (direction == "SW")
			status = SW->FlipRequest(colour, direction);
		else if (direction == "W")
			status = W->FlipRequest(colour, direction);
		else
			status = NW->FlipRequest(colour, direction);

		// Flip for the current one and return
		if (status)
			Flip();
		return status;
	}
	else {
		// If the same colour is reached, flip everything in between
		return true;
	}
}