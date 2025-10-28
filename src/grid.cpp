#include "grid.h"
#include <iostream>
#include "colors.h"
using namespace std;

Grid::Grid() {
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize() {
    for(int row = 0; row < numRows; row++){
        for (int column = 0; column < numCols; column++){
            grid[row][column] = 0;
        }
    }
}

void Grid::print(){
    for(int row = 0; row < numRows; row++){
        for(int column = 0; column < numCols; column++){
            cout << grid[row][column] << " ";
        }
        cout << endl;
    }
}

void Grid::LockBlock(const vector<Position>& positions, int id) {
    for (const Position& pos : positions) {
        if (pos.row >= 0 && pos.row < numRows && pos.column >= 0 && pos.column < numCols) {
            grid[pos.row][pos.column] = id;
        }
    }
}

void Grid::Draw(int offsetX, int offsetY) {
    for(int row = 0; row < numRows; row++){
        for(int column =0; column < numCols; column++){
            int cellValue = grid[row][column];
            int x = offsetX + column * cellSize + 1;
            int y = offsetY + row * cellSize + 1;
            DrawRectangle(x, y, cellSize-1, cellSize-1, colors[cellValue]);
        }
    
    }
}
