#include <iostream>
#include "Board.h"

int main()
{
    int debug[8][8] = 
    {
        { -1, -1, -1, -1, -1, -1, -1, -1},
        { -1, -1, -1, -1, -1, 0, 1, -1},
        { -1, -1, -1, -1, 1, 0, -1, -1},
        { -1, -1, -1, 1, 1, 0, -1, -1},
        { -1, -1, -1, 0, 0, 0, 0, 0},
        { -1, -1, -1, -1, -1, -1, -1, -1},
        { -1, -1, -1, -1, -1, -1, -1, -1},
        { -1, -1, -1, -1, -1, -1, -1, -1}
    };

    //TODO: Check for number of valid moves OR skip, 
    int x, y, colour = 1, turn = 1;
    bool playing = true, alreadySkipped = false;
    string currentPlayer = "Black";
    Board board;
    //board.SetBoard(debug);
    board.Print();
    while (playing) {
        cout << "[ " << currentPlayer <<" ] Enter coordinates (x space y): ";
        cin >> x >> y;
        if (x > 8 || x < 1 || y > 8 || y < 0) {
            cout << "<Invalid Move> Not a valid tile location. <Invalid Move>\n";
            continue;
        }
        if (turn == 5) break;
        if (turn <= 4) {
            if ((x == 4 || x == 5) && (y == 4 || y == 5)) {
                if (board.Foresight(y - 1, x - 1, colour) == 0) {
                    board.PlacePiece(y - 1, x - 1, colour);
                    board.Print();
                }
                else {
                    cout << "<Invalid Move> Tile already occupied. <Invalid Move>\n";
                    continue;
                }
            }
            else {
                cout << "<Invalid Move> First 2 moves must be in the middle. <Invalid Move>\n";
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
        currentPlayer = (currentPlayer == "Black" ? "White" : "Black");
        turn++;
    }
    char winner = board.GetWinner();
    if (winner == 'w') cout << "White wins!";
    else if (winner == 'b') cout << "Black wins!";
    else cout << "It's a tie!";
}