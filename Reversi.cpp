#include <iostream>
#include "Board.h"

void printGrid(int grid[8][8]);

int main()
{
    Board board;
    int grid[8][8];
    board.UpdateGrid(grid);
    printGrid(grid);
}

void printGrid(int grid[8][8]) {
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