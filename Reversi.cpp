#include <iostream>
#include "Board.h"

int main()
{
    //TODO: Check for number of valid moves OR skip | Verify first 4 moves
    int x, y, colour = 1, turn = 1;
    bool playing = true;
    Board board;
    board.Print();
    while (playing) {
        cout << "Enter coordinates (x space y): ";
        cin >> x >> y;
        if (turn <= 4) {
            if (board.Foresight(y - 1, x - 1, colour) == 0) {
                board.PlacePiece(y - 1, x - 1, colour);
                board.Print();
            }
            else {
                cout << "<Invalid Move> First 2 moves must be non-capturing moves. <Invalid Move>\n";
                continue;
            }
        }
        else {
            if (board.Foresight(y - 1, x - 1, colour) > 0) {
                board.PlacePiece(y - 1, x - 1, colour);
                board.Print();
            }
            else {
                cout << "<Invalid Move> Move must capture at least 1 piece, try again. <Invalid Move>\n";
                continue;
            }
        }
        // Switch colour at the end of the turn
        colour = (colour ? 0 : 1);
        turn++;
    }
}