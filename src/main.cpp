#include <raylib.h>
#include <random>
#include <vector>

#include "config.h"
#include "grid.h"
#include "blocks.h"
#include "sandPhysics/sandgrid.h"
#include "sandPhysics/sandConfig.h"
#include "sandPhysics/sandPhysics.h"
#include "sandPhysics/addSand.h"
#include "sandPhysics/sandColor.h"

const int gridRows = GameConfig::GRID_ROWS;
const int gridColumns = GameConfig::GRID_COLS;
const int cellSize = GameConfig::CELL_SIZE;
const int gridWidth = gridColumns * cellSize;
const int gridHeight = gridRows * cellSize;

const int screenWidth = 600;
const int screenHeight = 700;
const int panelWidth = 420;
const int panelHeight = 660;
const int panelX = (screenWidth - panelWidth) / 2;
const int panelY = (screenHeight - panelHeight) / 2;
const int playfieldOffsetX = panelX + (panelWidth - gridWidth) / 2;
const int playfieldOffsetY = panelY + (panelHeight - gridHeight) / 2;

const int startButtonWidth = 180;
const int startButtonHeight = 60;
const Rectangle startButton = {
    (float)(panelX + (panelWidth - startButtonWidth) / 2),
    (float)(panelY + panelHeight - startButtonHeight - 24),
    (float)startButtonWidth,
    (float)startButtonHeight
};

const Color backgroundColor = { 15, 16, 32, 255 };
const Color panelColor = { 20, 24, 40, 255 };
const Color panelBorderColor = { 71, 82, 109, 255 };
const Color playfieldColor = { 34, 40, 58, 255 };
const Color buttonColor = { 93, 109, 157, 255 };
const Color buttonHoverColor = { 122, 141, 194, 255 };
const Color buttonTextColor = RAYWHITE;
const Color overlayColor = { 0, 0, 0, 140 };
const float fallInterval = 0.6f;

// Shared RNG for every gameplay system (blocks, sand, UI tweaks)
std::mt19937& GlobalRng() {
    static std::mt19937 rng(std::random_device{}());
    return rng;
}

// Chooses one of the 4 sand-compatible colors with equal probability
int RandomBlockColorIndex() {
    static std::uniform_int_distribution<int> colorDist(2, 5);
    return colorDist(GlobalRng());
}

Block CreateBlockByIndex(int index) {
    switch (index) {
        case 0: return IBlock();
        case 1: return JBlock();
        case 2: return LBlock();
        case 3: return OBlock();
        case 4: return SBlock();
        case 5: return TBlock();
        case 6: return ZBlock();
        default: return TBlock();
    }
}

Block CreateRandomBlock() {
    static std::uniform_int_distribution<int> blockDist(0, 6);
    Block block = CreateBlockByIndex(blockDist(GlobalRng()));
    block.SetId(RandomBlockColorIndex());
    return block;
}

// Maps a block id to a sand color index, randomizing if id falls outside palette
int GetSandColorIndexForBlock(int blockId) {
    if (blockId >= 2 && blockId <= 5) {
        return blockId;
    }
    return RandomBlockColorIndex();
}

// Checks whether any fine-grained sand lives inside the coarse grid cell
bool HasSandInCell(const Sand& sand, int gridRow, int gridCol) {
    if (gridRow < 0 || gridCol < 0) {
        return false;
    }

    const int subdivisions = SandConfig::SUBDIVISION;
    const int startRow = gridRow * subdivisions;
    const int startCol = gridCol * subdivisions;

    for (int row = 0; row < subdivisions; ++row) {
        const int sandRow = startRow + row;
        if (sandRow < 0 || sandRow >= sand.GetNumRows()) {
            continue;
        }
        for (int col = 0; col < subdivisions; ++col) {
            const int sandCol = startCol + col;
            if (sandCol < 0 || sandCol >= sand.GetNumCols()) {
                continue;
            }
            if (sand.GetCell(sandRow, sandCol) != 0) {
                return true;
            }
        }
    }

    return false;
}

// Converts the landed block cells into fully-populated sand regions
void DepositBlockAsSand(const std::vector<Position>& cells, int blockId, Sand& sand) {
    const int colorIndex = GetSandColorIndexForBlock(blockId);
    const int subdivisions = SandConfig::SUBDIVISION;

    for (const Position& cell : cells) {
        if (cell.row < 0) {
            continue;
        }

        const int startRow = cell.row * subdivisions;
        const int startCol = cell.column * subdivisions;

        for (int r = 0; r < subdivisions; ++r) {
            const int sandRow = startRow + r;
            if (sandRow < 0 || sandRow >= sand.GetNumRows()) {
                continue;
            }
            for (int c = 0; c < subdivisions; ++c) {
                const int sandCol = startCol + c;
                if (sandCol < 0 || sandCol >= sand.GetNumCols()) {
                    continue;
                }

                sand.SetCell(sandRow, sandCol, colorIndex);
                sand.SetCellColor(sandRow, sandCol, GetSandColorVariation(colorIndex));
            }
        }
    }
}

// Checks tetris block collisions against both grid cells and dynamic sand
bool BlockFits(const Block &block, const Grid &grid, const Sand& sand) {
    std::vector<Position> tiles = block.GetCellPositions();
    for (const Position& item : tiles) {
        if (item.column < 0 || item.column >= gridColumns) {
            return false;
        }
        if (item.row >= gridRows) {
            return false;
        }
        if (item.row >= 0) {
            if (grid.GetCell(item.row, item.column) != 0) {
                return false;
            }
            if (HasSandInCell(sand, item.row, item.column)) {
                return false;
            }
        }
    }
    return true;
}

// Standard Tetris controls with collision rollback
void HandleInput(Block &block, const Grid &grid, const Sand& sand) {
    if (IsKeyPressed(KEY_LEFT)) {
        block.Move(0, -1);
        if (!BlockFits(block, grid, sand)) {
            block.Move(0, 1);
        }
    }
	if (IsKeyPressed(KEY_RIGHT)) {
		block.Move(0, 1);
		if (!BlockFits(block, grid, sand)) {
			block.Move(0, -1);
		}
	}
	if (IsKeyPressed(KEY_DOWN)) {
		block.Move(1, 0);
		if (!BlockFits(block, grid, sand)) {
			block.Move(-1, 0);
		}
	}
	if (IsKeyPressed(KEY_UP)) {
		block.Rotate();
		if (!BlockFits(block, grid, sand)) {
			block.UndoRotation();
		}
	}
}

int main () {
    InitWindow(screenWidth, screenHeight, "Sand Tetris");
    SetTargetFPS(60);

    Grid grid;
	Sand sand;

	// Initialize sand physics and spawner
	SandPhysics physics(sand);
	SandSpawner spawner(sand, playfieldOffsetX, playfieldOffsetY);

	Block block = CreateRandomBlock();
	bool gameStarted = false;
	bool gameOver = false;
	float fallTimer = 0.0f;

    // Core loop: process input, simulate sand, update Tetris, draw UI
    while(WindowShouldClose() == false) {
        float deltaTime = GetFrameTime();
        Vector2 mousePosition = GetMousePosition();
        bool buttonHover = CheckCollisionPointRec(mousePosition, startButton);

		// Handle sand input and simulation each frame
		spawner.HandleInput();
		physics.Update();

        if (!gameStarted && buttonHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            gameStarted = true;
            gameOver = false;
            // Reset both grids for a fresh run
            grid.Initialize();
            sand.Initialize();
            block = CreateRandomBlock();
            fallTimer = 0.0f;
            if (!BlockFits(block, grid, sand)) {
                gameOver = true;
                gameStarted = false;
            }
        }
        if (gameStarted) {
            HandleInput(block, grid, sand);
            fallTimer += deltaTime;
            if (fallTimer >= fallInterval) {
                fallTimer = 0.0f;
                block.Move(1, 0);
                if (!BlockFits(block, grid, sand)) {
                    block.Move(-1, 0);
                    std::vector<Position> landedCells = block.GetCellPositions();
                    // Turn settled block into sand, then spawn the next piece
                    DepositBlockAsSand(landedCells, block.GetId(), sand);
                    Block nextBlock = CreateRandomBlock();
                    if (!BlockFits(nextBlock, grid, sand)) {
                        gameOver = true;
                        gameStarted = false;
                    } else {
                        block = nextBlock;
                    }
                }
            }
        }
        BeginDrawing();
        ClearBackground(backgroundColor);
        DrawRectangle(panelX, panelY, panelWidth, panelHeight, panelColor);
        DrawRectangleLinesEx((Rectangle){(float)panelX, (float)panelY, (float)panelWidth, (float)panelHeight}, 3.0f, panelBorderColor);
        // Dedicated playfield rect keeps grey visuals confined to the grid area
        DrawRectangle(playfieldOffsetX, playfieldOffsetY, gridWidth, gridHeight, playfieldColor);

		// Render sand grains first so falling piece sits on top
		sand.Draw(playfieldOffsetX, playfieldOffsetY);
        grid.Draw(playfieldOffsetX, playfieldOffsetY);
        if (gameStarted) {
            block.Draw(playfieldOffsetX, playfieldOffsetY);
        }
        if (!gameStarted) {
            DrawRectangle(panelX, panelY, panelWidth, panelHeight, overlayColor);
            DrawRectangleRounded(startButton, 0.2f, 8, buttonHover ? buttonHoverColor : buttonColor);
            int labelFontSize = 28;
            const char* labelText = "START";
            int labelWidth = MeasureText(labelText, labelFontSize);
            int labelX = (int)(startButton.x + (startButton.width - labelWidth) / 2);
            int labelY = (int)(startButton.y + (startButton.height - labelFontSize) / 2);
            DrawText(labelText, labelX, labelY, labelFontSize, buttonTextColor);

            const char* prompt = gameOver ? "Game Over! Click START to restart" : "Click START to begin";
            int promptSize = 24;
            int promptWidth = MeasureText(prompt, promptSize);
            int promptX = panelX + (panelWidth - promptWidth) / 2;
            int promptY = panelY + 150;
            DrawText(prompt, promptX, promptY, promptSize, RAYWHITE);
        }
        EndDrawing();
    }

    CloseWindow();
}
