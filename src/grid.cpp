#include "grid.h"
#include "config.h"
#include <iostream>
#include "colors.h"
using namespace std;

Grid::Grid()
    : numRows(GameConfig::GRID_ROWS),
      numCols(GameConfig::GRID_COLS),
      cellSize(GameConfig::CELL_SIZE),
      colors(GetCellColors())
{
    Initialize();
}

void Grid::Initialize() {
    for(int row = 0; row < numRows; row++){
        for (int column = 0; column < numCols; column++){
            grid[row][column] = 0;
        }
    }
}

void Grid::print() const {
    for(int row = 0; row < numRows; row++){
        for(int column = 0; column < numCols; column++){
            cout << grid[row][column] << " ";
        }
        cout << endl;
    }
}

void Grid::Draw() const {
    for(int row = 0; row < numRows; row++){
        for(int column =0; column < numCols; column++){
            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize+1, row * cellSize+1, cellSize-1, cellSize-1, colors[cellValue]);
        }

    }
    ClearBackground(colors[1]);
}


