#include <iostream>
#include "Board.h"

void printGrid(Board board);

int main()
{
    Board board;
    printGrid(board);
}

void printGrid(Board board) {
    int grid[8][8];
    board.UpdateGrid(grid);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] == 0)
                cout << "W ";
            else if (grid[i][j] == 1)
                cout << "B ";
            else
                cout << "O ";
        }
        cout << endl;
    }
}