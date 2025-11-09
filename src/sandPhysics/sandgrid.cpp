/******************************************************************
 * sandgrid.cpp -- Sand particle grid implementation
 *
 * Description: Higher resolution grid (120x60) for simulating falling
 *              sand particles using cellular automata. Each sand cell
 *              has its own color for visual variety.
 *
 * Authors: Jethro Rolfe, Carson Chen, Howard Li, Jason Mai, Shayan Sharvini
 *
 *******************************************************************/
#include <iostream>
#include "sandPhysics/sandgrid.h"
#include "colors.h"
using namespace std;

/******************************************************************
 * Sand -- Constructor, initializes the sand grid
 *
 * Parameters: none
 * Modifies: Initializes grid dimensions and clears all cells
 *
 * Returns: Sand object
 *******************************************************************/
Sand::Sand()
	: numRows(SandConfig::SAND_ROWS),        // 120 rows (6x subdivision)
	  numCols(SandConfig::SAND_COLS),        // 60 columns (6x subdivision)
	  cellSize(SandConfig::SAND_CELL_SIZE),  // 5 pixels per cell
	  colors(GetCellColors())                // Color palette
{
	Initialize();
}

/******************************************************************
 * Initialize -- Clear the sand grid and color grid
 *
 * Parameters: none
 * Modifies: grid and colorGrid arrays - sets all to empty/black
 *
 * Returns: nothing
 *******************************************************************/
void Sand::Initialize() {
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {
			grid[row][column] = 0;                   // 0 = empty cell
			colorGrid[row][column] = BLACK;          // Default to black
		}
	}
}

/******************************************************************
 * print -- Print sand grid to console (for debugging)
 *
 * Parameters: none
 * Modifies: cout - outputs grid state
 *
 * Returns: nothing
 *******************************************************************/
void Sand::print() const {
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {
			cout << grid[row][column] << " ";
		}
		cout << endl;
	}
}

/******************************************************************
 * Draw -- Render the sand particles to the screen
 *
 * Parameters: none
 * Modifies: Screen output via raylib DrawRectangle
 *
 * Returns: nothing
 *******************************************************************/
void Sand::Draw() const {
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {
			int cellValue = grid[row][column];  // Get cell type
			// Only draw non-empty cells (skip 0 = empty)
			if (cellValue != 0) {
				// Draw sand particle with its unique color
				DrawRectangle(column * cellSize, row * cellSize, cellSize, cellSize, colorGrid[row][column]);
			}
		}

	}
	ClearBackground(colors[1]);  // Set background color
}

