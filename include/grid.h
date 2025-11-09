#pragma once
#include <vector>
#include <array>
#include <raylib.h>
#include "position.h"
#include "config.h"
using namespace std;

class Grid{
    public:
        Grid();
        void Initialize();
        void LockBlock(const vector<Position> &positions, int id);
        void print() const;
        void Draw(int offsetX, int offsetY) const;

        // Getters
        int GetCell(int row, int col) const { return grid.at(row).at(col); }
        int GetNumRows() const { return numRows; }
        int GetNumCols() const { return numCols; }

        // Setters
        void SetCell(int row, int col, int value) { grid.at(row).at(col) = value; }

        array<array<int, GameConfig::GRID_COLS>, GameConfig::GRID_ROWS> grid;
    private:
        int numRows;
        int numCols;
        int cellSize;
        vector<Color> colors;
};