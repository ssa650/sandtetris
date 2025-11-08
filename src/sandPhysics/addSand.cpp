/******************************************************************
 * addSand.cpp -- Mouse-based sand particle spawning system
 *
 * Description: Allows users to spawn sand particles by clicking
 *              with the mouse. Used for testing the sand physics
 *              and creating custom sand patterns.
 *
 * Controls: Right-click to spawn sand at cursor position
 *
 * Authors: Jethro Rolfe, Carson Chen, Howard Li, Jason Mai, Shayan Sharvini
 *
 *******************************************************************/
#include "sandPhysics/addSand.h"
#include "sandPhysics/sandConfig.h"
#include "sandPhysics/sandColor.h"

/******************************************************************
 * SandSpawner -- Constructor, initializes sand spawner
 *
 * Parameters: sandGrid -- reference to the sand grid to modify
 * Modifies: Stores reference to sand grid
 *
 * Returns: SandSpawner object
 *******************************************************************/
SandSpawner::SandSpawner(Sand& sandGrid) : sand(sandGrid) {}

/******************************************************************
 * AddSandAtPosition -- Spawn sand particles at a grid position
 *
 * Parameters: row -- grid row position
 *             col -- grid column position
 * Modifies: sand.grid, sand.colorGrid -- adds sand particles
 *
 * Behavior: Creates a square brush of sand particles based on
 *           brushSize (e.g., 5x5 for brushSize=5)
 *
 * Returns: nothing
 *******************************************************************/
void SandSpawner::AddSandAtPosition(int row, int col) {
    // Add sand in a square pattern based on brushSize
    // brushSize 1 = 1x1, brushSize 2 = 2x2, brushSize 3 = 3x3, etc.

    for (int r = 0; r < brushSize; r++) {
        for (int c = 0; c < brushSize; c++) {
            int targetRow = row + r;       // Calculate target row
            int targetCol = col + c;       // Calculate target column

            // Validate bounds
            if (targetRow < 0 || targetRow >= SandConfig::SAND_ROWS ||
                targetCol < 0 || targetCol >= SandConfig::SAND_COLS) {
                continue;
            }

            // Only add sand if cell is empty
            // Sand color values: 1=black, 2=orange, 3=blue, 4=yellow, 5=cyan, 6=green, 7=purple, 8=red
            if (sand.grid[targetRow][targetCol] == 0) {
                sand.grid[targetRow][targetCol] = sandColor;    // Set sand type
                sand.colorGrid[targetRow][targetCol] = GetSandColorVariation(sandColor);  // Set unique color
            }
        }
    }
}

/******************************************************************
 * HandleInput -- Process mouse input for sand spawning
 *
 * Parameters: none
 * Modifies: sand grid if right mouse button is pressed
 *
 * Controls: Right-click and hold to continuously spawn sand
 *
 * Returns: nothing
 *******************************************************************/
void SandSpawner::HandleInput() {
    // Check for right mouse button click
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 mousePos = GetMousePosition();   // Get mouse cursor position

        // Convert mouse position to grid coordinates
        int col = static_cast<int>(mousePos.x / SandConfig::SAND_CELL_SIZE);
        int row = static_cast<int>(mousePos.y / SandConfig::SAND_CELL_SIZE);

        AddSandAtPosition(row, col);   // Spawn sand at cursor
    }
}