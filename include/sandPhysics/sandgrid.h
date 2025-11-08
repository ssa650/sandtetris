#pragma once
#include <vector>
#include <array>
#include <raylib.h>
#include "sandConfig.h"
using namespace std;

class Sand {
public:
	Sand();
	void Initialize();
	void print() const;
	void Draw() const;

	// Getters
	int GetCell(int row, int col) const { return grid.at(row).at(col); }
	Color GetCellColor(int row, int col) const { return colorGrid.at(row).at(col); }
	int GetNumRows() const { return numRows; }
	int GetNumCols() const { return numCols; }

	// Setters (needed by SandPhysics)
	void SetCell(int row, int col, int value) { grid.at(row).at(col) = value; }
	void SetCellColor(int row, int col, Color color) { colorGrid.at(row).at(col) = color; }

	// Friend class to allow physics engine direct access
	friend class SandPhysics;
	friend class SandSpawner;

private:
	array<array<int, SandConfig::SAND_COLS>, SandConfig::SAND_ROWS> grid;
	array<array<Color, SandConfig::SAND_COLS>, SandConfig::SAND_ROWS> colorGrid;  // Individual color for each cell
	int numRows;
	int numCols;
	int cellSize;
	vector<Color> colors;
};