/******************************************************************
 * config.h -- Centralized game configuration constants
 *
 * Description: Contains all game configuration values including
 *              grid dimensions, window size, and performance settings.
 *              All magic numbers are defined here for easy tuning.
 *
 * Authors: Jethro Rolfe, Carson Chen, Howard Li, Jason Mai, Shayan Sharvini
 *
 *******************************************************************/
#pragma once

// Game configuration constants
namespace GameConfig {
    // Grid dimensions - standard Tetris grid
    constexpr int GRID_ROWS = 20;    // Number of rows in game grid
    constexpr int GRID_COLS = 10;    // Number of columns in game grid
    constexpr int CELL_SIZE = 30;    // Size of each cell in pixels

    // Window dimensions (calculated from grid)
    constexpr int WINDOW_WIDTH = GRID_COLS * CELL_SIZE;   // 300px total width
    constexpr int WINDOW_HEIGHT = GRID_ROWS * CELL_SIZE;  // 600px total height

    // Performance settings
    constexpr int TARGET_FPS = 60;   // Target frames per second

    // Display
    constexpr const char* WINDOW_TITLE = "Sand Tetris";  // Window title bar text
}
