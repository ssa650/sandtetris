#pragma once

// Sand grid configuration
// subdivision of Tetris grid (20 rows × 10 cols × 30px cells)
// Valid SAND_CELL_SIZE values: 15 (2x), 10 (3x), 6 (5x), 5 (6x)
namespace SandConfig {
    constexpr int SUBDIVISION = 6;  // Change this to adjust resolution
    constexpr int SAND_ROWS = 20 * SUBDIVISION;
    constexpr int SAND_COLS = 10 * SUBDIVISION;
    constexpr int SAND_CELL_SIZE = 30 / SUBDIVISION;
}
