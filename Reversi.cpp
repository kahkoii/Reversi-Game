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

    //Declarations 
    int x, y, colour = 1, turn = 1;
    bool playing = true, skipped = false;
    string currentPlayer = "Black";
    vector<Coordinates> moveSet;
    Coordinates current(0, 0);
    Board board;
    //board.SetBoard(debug);
    board.Print();

    // Game Loop
    while (playing) {

        // Check win condition
        moveSet = board.UpdateMoveSet(colour, true);
        if (turn > 4 && moveSet.empty()) {
            if (board.GetPieces() == 64) {
                break;
            }
            else {
                cout << "\n<Turn Skip> There are no valid moves for " << currentPlayer << ". <Turn Skip>\n";
                if (skipped == true)
                    break;
                else {
                    skipped = true;
                    colour = (colour ? 0 : 1);
                    currentPlayer = (currentPlayer == "Black" ? "White" : "Black");
                    turn++;
                    continue;
                }
            }
        }

        // Get input
        cout << "[ " << currentPlayer <<" ] Enter coordinates (x space y): ";
        cin >> x >> y;

        // Input validation
        if (x > 8 || x < 1 || y > 8 || y < 0) {
            cout << "<Invalid Move> Not a valid tile location. <Invalid Move>\n";
            continue;
        }

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
            current.x = x - 1; current.y = y - 1;
            if (board.ValidCoordinates(moveSet, current)) {
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

    // Declaring winner
    char winner = board.GetWinner();
    if (winner == 'w') cout << "White wins!\n";
    else if (winner == 'b') cout << "Black wins!\n";
    else cout << "It's a tie!\n";
}