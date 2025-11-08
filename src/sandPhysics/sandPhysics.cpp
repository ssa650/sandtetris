#include "sandPhysics/sandPhysics.h"
#include "sandPhysics/sandConfig.h"
#include <cstdlib>

// Cellular automata sand physics implementation
// Cell values: 0 = empty, 1-8 = sand colors (matches tetris block colors)
// Sand falls down if space below is empty
// If blocked, sand tries to move diagonally down-left or down-right

SandPhysics::SandPhysics(Sand& sandGrid) : sand(sandGrid) {}

bool SandPhysics::IsSand(int cellValue) {
    // Sand can be any value from 1-8 (different colors)
    // 0 = empty, 1-8 = colored sand
    return cellValue >= 1 && cellValue <= 8;
}

bool SandPhysics::CanMoveTo(int row, int col) {
    // Check bounds
    if (row < 0 || row >= SandConfig::SAND_ROWS || col < 0 || col >= SandConfig::SAND_COLS) {
        return false;
    }
    // Can move if cell is empty (0)
    return sand.grid[row][col] == 0;
}

void SandPhysics::ProcessCell(int row, int col) {
    int cellValue = sand.grid[row][col];

    // Only process sand cells (any color from 1-8)
    if (!IsSand(cellValue)) {
        return;
    }

    // Try to move down first
    if (CanMoveTo(row + 1, col)) {
        sand.grid[row + 1][col] = cellValue;
        sand.colorGrid[row + 1][col] = sand.colorGrid[row][col];
        sand.grid[row][col] = 0;
        return;
    }

    // Try diagonal movement (randomly choose left or right first)
    bool tryLeftFirst = (rand() % 2) == 0;

    if (tryLeftFirst) {
        // Try down-left, then down-right
        if (CanMoveTo(row + 1, col - 1)) {
            sand.grid[row + 1][col - 1] = cellValue;
            sand.colorGrid[row + 1][col - 1] = sand.colorGrid[row][col];
            sand.grid[row][col] = 0;
            return;
        }
        if (CanMoveTo(row + 1, col + 1)) {
            sand.grid[row + 1][col + 1] = cellValue;
            sand.colorGrid[row + 1][col + 1] = sand.colorGrid[row][col];
            sand.grid[row][col] = 0;
            return;
        }
    } else {
        // Try down-right, then down-left
        if (CanMoveTo(row + 1, col + 1)) {
            sand.grid[row + 1][col + 1] = cellValue;
            sand.colorGrid[row + 1][col + 1] = sand.colorGrid[row][col];
            sand.grid[row][col] = 0;
            return;
        }
        if (CanMoveTo(row + 1, col - 1)) {
            sand.grid[row + 1][col - 1] = cellValue;
            sand.colorGrid[row + 1][col - 1] = sand.colorGrid[row][col];
            sand.grid[row][col] = 0;
            return;
        }
    }

    // If we reach here, sand particle can't move (it's settled)
}

void SandPhysics::Update() {
    // Only update physics every other frame (half speed)
    frameCounter++;
    if (frameCounter % 2 != 0) {
        return;
    }

    // Alternate column processing direction each frame to prevent bias
    bool processLeftToRight = (frameCounter % 4) == 0;

    // Process from bottom to top to avoid double-processing cells
    for (int row = SandConfig::SAND_ROWS - 1; row >= 0; row--) {
        if (processLeftToRight) {
            // Process left to right
            for (int col = 0; col < SandConfig::SAND_COLS; col++) {
                ProcessCell(row, col);
            }
        } else {
            // Process right to left
            for (int col = SandConfig::SAND_COLS - 1; col >= 0; col--) {
                ProcessCell(row, col);
            }
        }
    }
}