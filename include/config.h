#pragma once

// Game configuration constants
namespace GameConfig {
    // Grid dimensions
    constexpr int GRID_ROWS = 20;
    constexpr int GRID_COLS = 10;
    constexpr int CELL_SIZE = 30;

    // Window dimensions (calculated from grid)
    constexpr int WINDOW_WIDTH = GRID_COLS * CELL_SIZE;   // 300px
    constexpr int WINDOW_HEIGHT = GRID_ROWS * CELL_SIZE;  // 600px

    // Frame rate
    constexpr int TARGET_FPS = 60;

    // Game title
    constexpr const char* WINDOW_TITLE = "Sand Tetris";
}
