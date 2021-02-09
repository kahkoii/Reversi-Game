#include <iostream>
#include <ctime>
#include "Board.h"
#include "AI.h"
#include "MoveHistory.h"
#include "HistoryLog.h"
using namespace std;

MoveHistory play(int gameMode);
int getGameMode();
int getStartingPlayer();
bool getDisplayAiProcess();
void viewHistory(MoveHistory hist);

int main()
{
    int gameMode;
    //declare history logs here
    HistoryLog histLog;

    // Game setup
    while (true) {
        gameMode = getGameMode();
        // If playing a game
        if (gameMode == 1 || gameMode == 2) {
            MoveHistory hist;
            hist = play(gameMode);
            histLog.insertRecord(hist);
        }
        else if (gameMode == 3){
            int n;
            while (true) {
                cout << "\n===================\n      History\n===================\n";
                histLog.display();
                if (histLog.isEmpty()) { cout << "History log is empty!\n"; }
                cout << "\nSelect action [1 - View] [2 - Delete]: ";
                cin >> n;
                // View specific match history
                if (n == 1) {
                    cout << "\nSelect match to view: ";
                    cin >> n;
                    MoveHistory hist = histLog.get(n);
                    viewHistory(hist);
                }
                // Delete history from logs
                else if (n == 2) {
                    cout << "\nSelect match to delete: ";
                    cin >> n;
                    histLog.deleteRecord(n);
                }
                else if (n == -1) {
                    cout << "\n";
                    break;
                }
                else {
                    cout << "\nInvalid input, please try again.\n";
                }
            }
        }
        else {
            break;
        }
    }
}

// Plays the game and returns the move history
MoveHistory play(int gameMode) {
    
    MoveHistory hist;
    Grid grid;

    Grid temp = {
        { 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 1, 1, 1, 1, 1, 1, 1},
        { 1, 1, -1, -1,-1, -1, 1, 1},
        { 1, 1, -1, -1, -1, -1, 0, 1},
        { 1, 1, -1, -1, -1, -1, 0, 1},
        { 1, 1, -1, -1, -1, -1, 1, 1},
        { 1, 1, 1, 1, 0, 1, 1, 1},
        { 1, 1, 1, 1, 0, 1, 1, 1}
    };

    // AI setup
    AI reversiAI;
    int startingPlayer;
    bool displayAiProcess;
    if (gameMode == 2) {
        startingPlayer = getStartingPlayer();
        reversiAI.init(startingPlayer);
        displayAiProcess = getDisplayAiProcess();
    }

    // Board setup 
    int x, y, colour = 1, turn = 1;
    bool skipped = false;
    string currentPlayer = "Black";
    vector<Coordinates> moveSet;
    Coordinates current(0, 0);
    Board board;
    //board.SetBoard(temp); //TEST

    // Game Loop
    cout << "\n===================\n     Play Game\n===================\n  [ -1 to exit ]\n";
    board.Print();
    while (true) {
        // Check win condition
        moveSet = board.UpdateMoveSet(colour, true);
        if (turn > 4 && moveSet.empty()) {
            if (board.GetPieces() == 64) {
                cout << "\nBoard has been filled.\n";
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
        if (gameMode == 2)
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
                            reversiAI.movesMade++;
                            board.Print();
                            // History
                            board.UpdateGrid(grid);
                            hist.Insert(grid);
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
                    cout << "States explored: " << reversiAI.movesMade << "\n";
                    reversiAI.accumulatedMoves += reversiAI.movesMade;
                    cout << "Accumulated states: " << reversiAI.accumulatedMoves << "\n";
                    current.x = move.x; current.y = move.y;
                    board.Print();
                    // History
                    board.UpdateGrid(grid);
                    hist.Insert(grid);
                }
            }
            else {
                cout << "[ " << currentPlayer << " ] Enter coordinates (x space y): ";
                cin >> x;
                // Force exit game
                if (x == -1)
                    return hist;
                cin >> y;

                if (x > 8 || x < 1 || y > 8 || y < 0) {
                    cout << "<Invalid Move> Not a valid tile location. <Invalid Move>\n";
                    continue;
                }

                if (turn <= 4) {
                    if ((x == 4 || x == 5) && (y == 4 || y == 5)) {
                        if (board.Foresight(y - 1, x - 1, colour) == 0) {
                            board.PlacePiece(y - 1, x - 1, colour);
                            board.Print();
                            // History
                            board.UpdateGrid(grid);
                            hist.Insert(grid);
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
                        // History
                        board.UpdateGrid(grid);
                        hist.Insert(grid);
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
            cin >> x;
            // Force exit game
            if (x == -1)
                return hist;
            cin >> y;

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
                        // History
                        board.UpdateGrid(grid);
                        hist.Insert(grid);
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
                    // History
                    board.UpdateGrid(grid);
                    hist.Insert(grid);
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
    if (winner == 'w') cout << "White wins!\n\n";
    else if (winner == 'b') cout << "Black wins!\n\n";
    else cout << "It's a tie!\n\n";

    hist.SetWinner(winner);
    return hist;
}

int getGameMode()
{
    int gameMode;
    while (true) {
        cout << "Game Modes:\nMultiplayer  - Enter 1\nSingleplayer - Enter 2\nView History - Enter 3\nExit         - Enter 4\n\nSelect game mode: ";
        cin >> gameMode;
        if (gameMode < 1 || gameMode > 4) {
            cout << "Invalid Gamemode!\n\n";
        }
        else { break; }
    }
    cout << "-----------------------------------\n";
    return gameMode;
}

int getStartingPlayer()
{
    char choice{};
    while (true) {
        cout << "Would you like to go first? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'n') {
            cout << "Invalid Choice!\n\n";
        }
        else { break; }
    }
    cout << "-----------------------------------\n";
    if (choice == 'y') {
        return 0;
    }
    else { return 1; }
}

bool getDisplayAiProcess()
{
    char choice{};
    while (true) {
        cout << "Would you like to display AI move finding process? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'n') {
            std::cout << "Invalid Choice!\n\n";
        }
        else { break; }
    }
    cout << "-----------------------------------\n";
    if (choice == 'y') {
        return true;
    }
    else { return false; }
}

void viewHistory(MoveHistory hist) {
    if (hist.GetTotalMoves() == 0) {
        cout << "This game is invalid. No history to be viewed.\n\n";
    }
    else {
        string input;
        hist.Print();
        while (true) {
            cout << "\nCurrent Move: " << hist.GetCurrentMove() + 1 << "\n[1] Show Previous [2] Show Next [3] Exit\n";
            cin >> input;
            if (input == "1") {
                if (hist.Previous()) {
                    hist.Print();
                }
                else    
                    cout << "\nThis is the first move, there is no previous.\n";
            }
            else if (input == "2") {
                if (hist.Next()) {
                    hist.Print();
                }
                else
                    cout << "\nThis is the last move, there is no next.\n";
            }
            else if (input == "3") {
                break;
            }
            else {
                cout << "\n<Error> Invalid command, please try again. <Error>\n";
            }
        }
    }
}