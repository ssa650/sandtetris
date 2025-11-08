#pragma once
#include <vector>
#include <array>
#include <raylib.h>
#include "config.h"
using namespace std;

class Grid{
    public:
        Grid();
        void Initialize();
        void print() const;
        void Draw() const;

        // Getters
        int GetCell(int row, int col) const { return grid.at(row).at(col); }
        int GetNumRows() const { return numRows; }
        int GetNumCols() const { return numCols; }

        // Setters
        void SetCell(int row, int col, int value) { grid.at(row).at(col) = value; }

    private:
        array<array<int, GameConfig::GRID_COLS>, GameConfig::GRID_ROWS> grid;
        int numRows;
        int numCols;
        int cellSize;
        vector<Color> colors;
};