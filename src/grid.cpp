/******************************************************************
 * grid.cpp -- Tetris game grid implementation
 *
 * Description: Manages the 20x10 Tetris game grid where blocks land
 *              and tracks which cells are occupied by block pieces.
 *
 * Authors: Jethro Rolfe, Carson Chen, Howard Li, Jason Mai, Shayan Sharvini
 *
 *******************************************************************/
#include "grid.h"
#include "config.h"
#include <iostream>
#include "colors.h"
using namespace std;

/******************************************************************
 * Grid -- Constructor, initializes the game grid
 *
 * Parameters: none
 * Modifies: Initializes all member variables and clears grid
 *
 * Returns: Grid object
 *******************************************************************/
Grid::Grid()
    : numRows(GameConfig::GRID_ROWS),       // 20 rows
      numCols(GameConfig::GRID_COLS),       // 10 columns
      cellSize(GameConfig::CELL_SIZE),      // 30 pixels per cell
      colors(GetCellColors())               // Color palette
{
    Initialize();
}

/******************************************************************
 * Initialize -- Set all grid cells to empty (0)
 *
 * Parameters: none
 * Modifies: grid array - sets all cells to 0
 *
 * Returns: nothing
 *******************************************************************/
void Grid::Initialize() {
    for(int row = 0; row < numRows; row++){
        for (int column = 0; column < numCols; column++){
            grid[row][column] = 0;          // 0 = empty cell
        }
    }
}

/******************************************************************
 * print -- Print grid contents to console (for debugging)
 *
 * Parameters: none
 * Modifies: cout - outputs grid state
 *
 * Returns: nothing
 *******************************************************************/
void Grid::print() const {
    for(int row = 0; row < numRows; row++){
        for(int column = 0; column < numCols; column++){
            cout << grid[row][column] << " ";
        }
        cout << endl;
    }
}

/******************************************************************
 * Draw -- Render the grid to the screen
 *
 * Parameters: none
 * Modifies: Screen output via raylib DrawRectangle
 *
 * Returns: nothing
 *******************************************************************/
void Grid::Draw() const {
    for(int row = 0; row < numRows; row++){
        for(int column =0; column < numCols; column++){
            int cellValue = grid[row][column];  // Get cell color index
            // Draw cell with 1px padding
            DrawRectangle(column * cellSize+1, row * cellSize+1, cellSize-1, cellSize-1, colors[cellValue]);
        }

    }
    ClearBackground(colors[1]);  // Set background color
}


