/******************************************************************
 * sandPhysics.cpp -- Cellular automata sand physics simulation
 *
 * Description: Implements falling sand physics using cellular automata.
 *              Sand particles fall downward, or diagonally if blocked,
 *              creating realistic pile-up behavior.
 *
 * Physics Rules:
 *   - Sand falls straight down if space is empty
 *   - If blocked, tries to move diagonally (down-left or down-right)
 *   - Direction chosen randomly to prevent bias
 *   - Processes bottom-up to avoid double-processing cells
 *
 * Authors: Jethro Rolfe, Carson Chen, Howard Li, Jason Mai, Shayan Sharvini
 *
 *******************************************************************/
#include "sandPhysics/sandPhysics.h"
#include "sandPhysics/sandConfig.h"
#include <cstdlib>

/******************************************************************
 * SandPhysics -- Constructor, initializes physics engine
 *
 * Parameters: sandGrid -- reference to the sand grid to simulate
 * Modifies: Stores reference to sand grid
 *
 * Returns: SandPhysics object
 *******************************************************************/
SandPhysics::SandPhysics(Sand& sandGrid) : sand(sandGrid) {}

/******************************************************************
 * IsSand -- Check if a cell contains sand
 *
 * Parameters: cellValue -- the value of the cell to check
 * Modifies: nothing
 *
 * Returns: true if cell contains sand (1-8), false otherwise
 *******************************************************************/
bool SandPhysics::IsSand(int cellValue) {
    // Sand can be any value from 1-8 (different colors)
    // 0 = empty, 1-8 = colored sand
    return cellValue >= 1 && cellValue <= 8;
}

/******************************************************************
 * CanMoveTo -- Check if sand can move to a specific position
 *
 * Parameters: row -- target row position
 *             col -- target column position
 * Modifies: nothing
 *
 * Precondition: none
 *
 * Returns: true if position is in bounds and empty
 *******************************************************************/
bool SandPhysics::CanMoveTo(int row, int col) {
    // Check bounds
    if (row < 0 || row >= SandConfig::SAND_ROWS || col < 0 || col >= SandConfig::SAND_COLS) {
        return false;
    }
    // Can move if cell is empty (0)
    return sand.grid[row][col] == 0;
}

/******************************************************************
 * ProcessCell -- Apply physics rules to a single sand particle
 *
 * Parameters: row -- row position of cell to process
 *             col -- column position of cell to process
 * Modifies: sand.grid, sand.colorGrid -- moves sand particle if possible
 *
 * Physics behavior:
 *   1. Try to fall straight down
 *   2. If blocked, try diagonal movement (randomized direction)
 *   3. If all blocked, particle stays in place
 *
 * Returns: nothing
 *******************************************************************/
void SandPhysics::ProcessCell(int row, int col) {
    int cellValue = sand.grid[row][col];       // Current cell type

    // Only process sand cells (any color from 1-8)
    if (!IsSand(cellValue)) {
        return;
    }

    // Try to move down first
    if (CanMoveTo(row + 1, col)) {
        sand.grid[row + 1][col] = cellValue;             // Move sand value
        sand.colorGrid[row + 1][col] = sand.colorGrid[row][col];  // Move color
        sand.grid[row][col] = 0;                         // Clear old position
        return;
    }

    // Try diagonal movement (randomly choose left or right first)
    bool tryLeftFirst = (rand() % 2) == 0;   // 50/50 chance

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

/******************************************************************
 * Update -- Process all sand particles for one physics step
 *
 * Parameters: none
 * Modifies: sand.grid, sand.colorGrid -- updates all sand positions
 *           frameCounter -- tracks frames for timing
 *
 * Performance optimization:
 *   - Runs at half speed (every other frame)
 *   - Alternates column processing direction to prevent bias
 *   - Processes bottom-up to avoid moving same particle twice
 *
 * Returns: nothing
 *******************************************************************/
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