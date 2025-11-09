/******************************************************************
 * Sand Tetris Game
 * main.cpp -- Main game loop and initialization
 *
 * Description: A Tetris variant where blocks turn into sand particles
 *              that fall and interact using cellular automata physics.
 *
 * Input: User mouse input for sand spawning
 * Output: Graphical game window with falling sand simulation
 *
 * Authors: Jethro Rolfe, Carson Chen, Howard Li, Jason Mai, Shayan Sharvini
 *
 *******************************************************************/
#include <raylib.h>
#include <random>
#include "config.h"
#include "grid.h"
#include "blocks.h"
#include "sandPhysics/sandgrid.h"
#include "sandPhysics/sandPhysics.h"
#include "sandPhysics/addSand.h"

const int panelWidth = 420;
const int panelHeight = 660;
const int panelX = (GameConfig::WINDOW_WIDTH - panelWidth) / 2;
const int panelY = (GameConfig::WINDOW_HEIGHT - panelHeight) / 2;
const int playfieldOffsetX = panelX + (panelWidth - GameConfig::WINDOW_WIDTH) / 2;
const int playfieldOffsetY = panelY + (panelHeight - GameConfig::WINDOW_HEIGHT) / 2;
const int startButtonWidth = 180;
const int startButtonHeight = 60;
const Rectangle startButton = {
    (float)(panelX + (panelWidth - startButtonWidth) / 2),
    (float)(panelY + panelHeight - startButtonHeight - 24),
    (float)startButtonWidth,
    (float)startButtonHeight
};
const Color backgroundColor = { 15, 16, 32, 255 };
const Color panelColor = { 34, 40, 58, 255 };
const Color panelBorderColor = { 71, 82, 109, 255 };
const Color buttonColor = { 93, 109, 157, 255 };
const Color buttonHoverColor = { 122, 141, 194, 255 };
const Color buttonTextColor = RAYWHITE;
const Color overlayColor = { 0, 0, 0, 140 };
const float fallInterval = 0.6f;

/******************************************************************
 * CreateBlockByIndex -- Makes the specified block
 *
 * Parameters: index
 *
 * Returns: which block to create
 *******************************************************************/

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

/******************************************************************
 * CreateRandomBlock -- Makes random block
 *
 * Parameters: none
 * Modifies: index
 *
 * Returns: random block type
 *******************************************************************/

Block CreateRandomBlock() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    static std::uniform_int_distribution<int> dist(0, 6);
    int index = dist(rng);
    return CreateBlockByIndex(index);
}

/******************************************************************
 * BlockFits -- Determines whether a block fits
 *
 * Parameters: current block, block grid
 *
 * Returns: true/false
 *******************************************************************/

bool BlockFits(Block &block, Grid &grid) {
    vector<Position> tiles = block.GetCellPositions();
    for (Position item : tiles) {
        if (item.column < 0 || item.column >= GameConfig::GRID_COLS) {
            return false;
        }
        if (item.row >= GameConfig::GRID_ROWS) {
            return false;
        }
        if (item.row >= 0 && grid.grid[item.row][item.column] != 0) {
            return false;
        }
    }
    return true;
}

/******************************************************************
 * BlockInput -- Process arrow keys for moving blocks
 *
 * Parameters: none
 * Modifies: block grid
 *
 * Returns: nothing
 *******************************************************************/

void BlockInput(Block &block, Grid &grid) {
    if (IsKeyPressed(KEY_LEFT)) {
        block.Move(0, -1);
        if (!BlockFits(block, grid)) {
            block.Move(0, 1);
        }
    }
	if (IsKeyPressed(KEY_RIGHT)) {
		block.Move(0, 1);
		if (!BlockFits(block, grid)) {
			block.Move(0, -1);
		}
	}
	if (IsKeyPressed(KEY_DOWN)) {
		block.Move(1, 0);
		if (!BlockFits(block, grid)) {
			block.Move(-1, 0);
		}
	}
	if (IsKeyPressed(KEY_UP)) {
		block.Rotate();
		if (!BlockFits(block, grid)) {
			block.UndoRotation();
		}
	}
}

/******************************************************************
 * main -- Initialize game and run main game loop
 *
 * Parameters: none
 * Modifies: Creates window, initializes grids and physics systems
 *
 * Returns: 0 on successful exit
 *******************************************************************/
int main () {

    // Initialize window with configured dimensions
    InitWindow(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT, GameConfig::WINDOW_TITLE);
    SetTargetFPS(GameConfig::TARGET_FPS);

    Grid grid = Grid();           // Tetris block grid
    grid.print();                 // Debug: print grid to console

	Sand sand = Sand();           // Sand particle grid
	sand.print();                 // Debug: print sand grid to console

	// Initialize sand physics and spawner
	SandPhysics physics(sand);    // Physics engine for sand particles
	SandSpawner spawner(sand);    // Mouse-based sand spawning system

	Block block = CreateRandomBlock();
	bool gameStarted = false;
	bool gameOver = false;
	float fallTimer = 0.0f;
    // Main game loop - runs until user closes window
    while(WindowShouldClose() == false) {
		float deltaTime = GetFrameTime();
        Vector2 mousePosition = GetMousePosition();
		bool buttonHover = CheckCollisionPointRec(mousePosition, startButton);
        
		if (!gameStarted && buttonHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            gameStarted = true;
            gameOver = false;
            grid.Initialize();
            sand.Initialize();
            block = CreateRandomBlock();
            fallTimer = 0.0f;
            if (!BlockFits(block, grid)) {
                gameOver = true;
                gameStarted = false;
            }
        }

		if (gameStarted) {
            // Handle user input for spawning sand
		    spawner.HandleInput();

            BlockInput(block, grid);
            fallTimer += deltaTime;

            if (fallTimer >= fallInterval) {
                fallTimer = 0.0f;
                block.Move(1, 0);
                // Update sand physics simulation
		        physics.Update();
                if (!BlockFits(block, grid)) {
                    block.Move(-1, 0);
                    vector<Position> landedCells = block.GetCellPositions();
                    grid.LockBlock(landedCells, block.id);
                    Block nextBlock = CreateRandomBlock();
                    if (BlockFits(nextBlock, grid)) 
                        block = nextBlock;
                    else {
                        gameOver = true;
                        gameStarted = false;
                    }
                }
            }
        }
        
        BeginDrawing();

		grid.Draw(playfieldOffsetX, playfieldOffsetY);

		// Display FPS counter in top-left corner
		DrawFPS(10, 10);

		ClearBackground(backgroundColor);
        DrawRectangle(panelX, panelY, panelWidth, panelHeight, panelColor);
        Rectangle newRectangle(panelX, panelY, panelWidth, panelHeight);
        DrawRectangleLinesEx(newRectangle, 3.0f, panelBorderColor);

		if (gameStarted) {
            block.Draw(playfieldOffsetX, playfieldOffsetY);
            sand.Draw();
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
