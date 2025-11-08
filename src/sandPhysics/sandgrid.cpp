#include <iostream>
#include "sandPhysics/sandgrid.h"
#include "colors.h"
using namespace std;

Sand::Sand()
	: numRows(SandConfig::SAND_ROWS),
	  numCols(SandConfig::SAND_COLS),
	  cellSize(SandConfig::SAND_CELL_SIZE),
	  colors(GetCellColors())
{
	Initialize();
}

void Sand::Initialize() {
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {
			grid[row][column] = 0;
			colorGrid[row][column] = BLACK;  // Initialize all colors to black
		}
	}
}

void Sand::print() const {
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {
			cout << grid[row][column] << " ";
		}
		cout << endl;
	}
}

void Sand::Draw() const {
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {
			int cellValue = grid[row][column];
			// Only draw non-empty cells (skip 0 = empty)
			if (cellValue != 0) {
				DrawRectangle(column * cellSize, row * cellSize, cellSize, cellSize, colorGrid[row][column]);
			}
		}

	}
	ClearBackground(colors[1]);
}

