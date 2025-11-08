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

void Grid::Draw(int offsetX, int offsetY) const {
    // Draw subtle grid lines on top of any colored cells
    const Color lineColor = Fade(colors[0], 0.45f);
    for(int row = 0; row < numRows; row++){
        for(int column =0; column < numCols; column++){
            int cellValue = grid[row][column];
            int x = offsetX + column * cellSize;
            int y = offsetY + row * cellSize;

            if (cellValue > 0) {
                DrawRectangle(x + 1, y + 1, cellSize - 2, cellSize - 2, colors[cellValue]);
            }

            DrawRectangleLines(x, y, cellSize, cellSize, lineColor);
        }

    }
}
