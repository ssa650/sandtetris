#include "sandPhysics/addSand.h"
#include "sandPhysics/sandConfig.h"
#include "sandPhysics/sandColor.h"

// Testing feature: Add sand particles with mouse clicks
// Right-click to spawn sand at cursor position
// Change sandColor value (1-8) to test different colors

SandSpawner::SandSpawner(Sand& sandGrid, int offsetX, int offsetY)
    : sand(sandGrid),
      playfieldOffsetX(offsetX),
      playfieldOffsetY(offsetY) {}

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
            // Sand color values: 1=black, 2=orange, 3=blue, 4=yellow, 5=cyan
            if (sand.grid[targetRow][targetCol] == 0) {
                sand.grid[targetRow][targetCol] = sandColor;
                sand.colorGrid[targetRow][targetCol] = GetSandColorVariation(sandColor);
            }
        }
    }
}

void SandSpawner::HandleInput() {
    // Check for right mouse button click
    if (!IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        return;
    }

    const Vector2 mousePos = GetMousePosition();
    const float localX = mousePos.x - static_cast<float>(playfieldOffsetX);
    const float localY = mousePos.y - static_cast<float>(playfieldOffsetY);

    // Ignore clicks outside the playfield bounds
    if (localX < 0 || localY < 0) {
        return;
    }

    const int sandPixelWidth = SandConfig::SAND_COLS * SandConfig::SAND_CELL_SIZE;
    const int sandPixelHeight = SandConfig::SAND_ROWS * SandConfig::SAND_CELL_SIZE;
    if (localX >= sandPixelWidth || localY >= sandPixelHeight) {
        return;
    }

    // Convert mouse position to grid coordinates
    const int col = static_cast<int>(localX / SandConfig::SAND_CELL_SIZE);
    const int row = static_cast<int>(localY / SandConfig::SAND_CELL_SIZE);

    AddSandAtPosition(row, col);
}
