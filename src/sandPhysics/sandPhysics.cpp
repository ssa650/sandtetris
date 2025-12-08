#include "sandPhysics/sandPhysics.h"
#include "sandPhysics/sandConfig.h"
#include <array>
#include <cstdlib>
#include <utility>
#include <vector>

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

int SandPhysics::ClearSpanningClusters() {
    std::array<std::array<bool, SandConfig::SAND_COLS>, SandConfig::SAND_ROWS> visited{};
    int cleared = 0;

    for (int row = 0; row < SandConfig::SAND_ROWS; row++) {
        for (int col = 0; col < SandConfig::SAND_COLS; col++) {
            int cellValue = sand.grid[row][col];
            if (!IsSand(cellValue) || visited[row][col]) {
                continue;
            }

            const int color = cellValue;
            std::vector<std::pair<int, int>> stack;
            std::vector<std::pair<int, int>> cells;
            stack.push_back({row, col});
            visited[row][col] = true;

            bool touchesLeft = false;
            bool touchesRight = false;

            while (!stack.empty()) {
                auto current = stack.back();
                stack.pop_back();
                int r = current.first;
                int c = current.second;
                cells.push_back(current);

                if (c == 0) touchesLeft = true;
                if (c == SandConfig::SAND_COLS - 1) touchesRight = true;

                const int dr[4] = {1, -1, 0, 0};
                const int dc[4] = {0, 0, 1, -1};

                for (int i = 0; i < 4; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr < 0 || nr >= SandConfig::SAND_ROWS || nc < 0 || nc >= SandConfig::SAND_COLS) {
                        continue;
                    }
                    if (visited[nr][nc] || sand.grid[nr][nc] != color) {
                        continue;
                    }
                    visited[nr][nc] = true;
                    stack.push_back({nr, nc});
                }
            }

            if (touchesLeft && touchesRight) {
                for (const auto& cell : cells) {
                    sand.grid[cell.first][cell.second] = 0;
                    sand.colorGrid[cell.first][cell.second] = BLACK;
                }
                cleared += static_cast<int>(cells.size());
            }
        }
    }

    return cleared;
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
