#include <iostream>
#include <ctime>
#include "Board.h"
#include "AI.h"

int getGameMode();
int getStartingPlayer();
bool getDisplayAiProcess();

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

    // Startup
    int gameMode{ getGameMode() };
    AI reversiAI;
    int startingPlayer;
    bool displayAiProcess;
    if (gameMode == 1) {
        startingPlayer = getStartingPlayer();
        reversiAI.init(startingPlayer);
        displayAiProcess = getDisplayAiProcess();
    }

    // Declarations 
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

        // Single Player (Against AI)
        if (gameMode == 1) 
        {
            if (colour == startingPlayer) {
                cout << "[ " << currentPlayer << " ] AI turn\n";

                if (turn <= 4) {
                    while (true) {
                        srand(time(0));
                        int arr[] = { 4, 5 };
                        int x = arr[rand() % 2];
                        int y = arr[rand() % 2];
                        if (board.Foresight(y - 1, x - 1, colour) == 0) {
                            board.PlacePiece(y - 1, x - 1, colour);
                            board.Print();
                            break;
                        }
                    }
                }
                else {
                    int currentGrid[8][8];
                    board.UpdateGrid(currentGrid);
                    Board child;
                    child.SetBoard(currentGrid);
                    AiMove move = reversiAI.getBestMove(child, displayAiProcess);
                    board.PlacePiece(move.y, move.x, colour);
                    cout << "AI Move: (" << move.x + 1 << ", " << move.y + 1 << ")\n";
                    current.x = move.x; current.y = move.y;
                    board.Print();
                }
            }
            else {
                cout << "[ " << currentPlayer << " ] Enter coordinates (x space y): ";
                cin >> x >> y;

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
            }
        }
        // Multiplayer
        else
        {
            // Get input
            cout << "[ " << currentPlayer << " ] Enter coordinates (x space y): ";
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

int getGameMode()
{
    int gameMode{};
    while (true) {
        std::cout << "Game Modes:\nSingleplayer - Enter 1\nMultiplayer  - Enter 2\n\nSelect game mode: ";
        std::cin >> gameMode;
        if (gameMode != 1 && gameMode != 2) {
            std::cout << "Invalid Gamemode!\n\n";
        }
        else { break; }
    }
    std::cout << "-----------------------------------\n";
    return gameMode;
}

int getStartingPlayer()
{
    char choice{};
    while (true) {
        std::cout << "Would you like to go first? (y/n): ";
        std::cin >> choice;
        if (choice != 'y' && choice != 'n') {
            std::cout << "Invalid Choice!\n\n";
        }
        else { break; }
    }
    std::cout << "-----------------------------------\n";
    if (choice == 'y') {
        return 0;
    }
    else { return 1; }
}

bool getDisplayAiProcess()
{
    char choice{};
    while (true) {
        std::cout << "Would you like to display AI move finding process? (y/n): ";
        std::cin >> choice;
        if (choice != 'y' && choice != 'n') {
            std::cout << "Invalid Choice!\n\n";
        }
        else { break; }
    }
    std::cout << "-----------------------------------\n";
    if (choice == 'y') {
        return true;
    }
    else { return false; }
}