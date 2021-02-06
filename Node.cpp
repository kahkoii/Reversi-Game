#include "Node.h"
Node::Node() {
	Colour = -1;
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
	Colour = -1;
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

bool Node::FlipRequest(int colour) {
	int n = 0;
	if (N != NULL)
		n += N->FlipRequest(colour, "N");
	if (NE != NULL)
		n += NE->FlipRequest(colour, "NE");
	if (E != NULL)
		n += E->FlipRequest(colour, "E");
	if (SE != NULL)
		n += SE->FlipRequest(colour, "SE");
	if (S != NULL)
		n += S->FlipRequest(colour, "S");
	if (SW != NULL)
		n += SW->FlipRequest(colour, "SW");
	if (W != NULL)
		n += W->FlipRequest(colour, "W");
	if (NW != NULL)
		n += NW->FlipRequest(colour, "NW");
	if (n > 0)
		return true;
	return false;
}

bool Node::FlipRequest(int colour, string direction) {
	// This function flips pieces accordingly, and returns 
	// a boolean that determines if something has been flipped
	if (Colour == -1) {
		// If the edge is reached, stop the flip request
		return false;
	}
	else if (Colour != colour) {
		// If the current colour still does not match the colour of the
		// placed piece, continue sending requests in the same direction
		bool status;
		if (direction == "N") {
			if (N == NULL)
				return false;
			status = N->FlipRequest(colour, direction);
		}
		else if (direction == "NE") {
			if (NE == NULL)
				return false;
			status = NE->FlipRequest(colour, direction);
		}
		else if (direction == "E") {
			if (E == NULL)
				return false;
			status = E->FlipRequest(colour, direction);
		}
		else if (direction == "SE") {
			if (SE == NULL)
				return false;
			status = SE->FlipRequest(colour, direction);
		}
		else if (direction == "S") {
			if (S == NULL)
				return false;
			status = S->FlipRequest(colour, direction);
		}
		else if (direction == "SW") {
			if (SW == NULL)
				return false;
			status = SW->FlipRequest(colour, direction);
		}
		else if (direction == "W") {
			if (W == NULL)
				return false;
			status = W->FlipRequest(colour, direction);
		}
		else {
			if (NW == NULL)
				return false;
			status = NW->FlipRequest(colour, direction);
		}

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