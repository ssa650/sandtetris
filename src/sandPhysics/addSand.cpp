#include "sandPhysics/addSand.h"
#include "sandPhysics/sandConfig.h"
#include "sandPhysics/sandColor.h"

// Testing feature: Add sand particles with mouse clicks
// Right-click to spawn sand at cursor position
// Change sandColor value (1-8) to test different colors

SandSpawner::SandSpawner(Sand& sandGrid) : sand(sandGrid) {}

void SandSpawner::AddSandAtPosition(int row, int col) {
    // Add sand in a square pattern based on brushSize
    // brushSize 1 = 1x1, brushSize 2 = 2x2, brushSize 3 = 3x3, etc.

    for (int r = 0; r < brushSize; r++) {
        for (int c = 0; c < brushSize; c++) {
            int targetRow = row + r;
            int targetCol = col + c;

            // Validate bounds
            if (targetRow < 0 || targetRow >= SandConfig::SAND_ROWS ||
                targetCol < 0 || targetCol >= SandConfig::SAND_COLS) {
                continue;
            }

            // Only add sand if cell is empty
            // Sand color values: 1=black, 2=orange, 3=blue, 4=yellow, 5=cyan, 6=green, 7=purple, 8=red
            if (sand.grid[targetRow][targetCol] == 0) {
                sand.grid[targetRow][targetCol] = sandColor;
                sand.colorGrid[targetRow][targetCol] = GetSandColorVariation(sandColor);
            }
        }
    }
}

void SandSpawner::HandleInput() {
    // Check for right mouse button click
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 mousePos = GetMousePosition();

        // Convert mouse position to grid coordinates
        int col = static_cast<int>(mousePos.x / SandConfig::SAND_CELL_SIZE);
        int row = static_cast<int>(mousePos.y / SandConfig::SAND_CELL_SIZE);

        AddSandAtPosition(row, col);
    }
}