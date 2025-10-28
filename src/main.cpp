#include <raylib.h>
#include <random>
#include "grid.h"
#include "blocks.cpp"

const int gridRows = 20;
const int gridColumns = 10;
const int cellSize = 30;
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
const Color panelColor = { 34, 40, 58, 255 };
const Color panelBorderColor = { 71, 82, 109, 255 };
const Color buttonColor = { 93, 109, 157, 255 };
const Color buttonHoverColor = { 122, 141, 194, 255 };
const Color buttonTextColor = RAYWHITE;
const Color overlayColor = { 0, 0, 0, 140 };
const float fallInterval = 0.6f;

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
    static std::random_device rd;
    static std::mt19937 rng(rd());
    static std::uniform_int_distribution<int> dist(0, 6);
    int index = dist(rng);
    return CreateBlockByIndex(index);
}

bool BlockFits(Block &block, Grid &grid) {
    vector<Position> tiles = block.GetCellPositions();
    for (Position item : tiles) {
        if (item.column < 0 || item.column >= gridColumns) {
            return false;
        }
        if (item.row >= gridRows) {
            return false;
        }
        if (item.row >= 0 && grid.grid[item.row][item.column] != 0) {
            return false;
        }
    }
    return true;
}

void HandleInput(Block &block, Grid &grid) {
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

int main () {
    
    InitWindow(screenWidth, screenHeight, "Sand Tetris");
    SetTargetFPS(60);

    Grid grid = Grid();
    grid.print();

	Block block = CreateRandomBlock();
	bool gameStarted = false;
	bool gameOver = false;
	float fallTimer = 0.0f;

    while(WindowShouldClose() == false) {
        float deltaTime = GetFrameTime();
        Vector2 mousePosition = GetMousePosition();
        bool buttonHover = CheckCollisionPointRec(mousePosition, startButton);
        if (!gameStarted && buttonHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            gameStarted = true;
            gameOver = false;
            grid.Initialize();
            block = CreateRandomBlock();
            fallTimer = 0.0f;
            if (!BlockFits(block, grid)) {
                gameOver = true;
                gameStarted = false;
            }
        }
        if (gameStarted) {
            HandleInput(block, grid);
            fallTimer += deltaTime;
            if (fallTimer >= fallInterval) {
                fallTimer = 0.0f;
                block.Move(1, 0);
                if (!BlockFits(block, grid)) {
                    block.Move(-1, 0);
                    vector<Position> landedCells = block.GetCellPositions();
                    grid.LockBlock(landedCells, block.id);
                    Block nextBlock = CreateRandomBlock();
                    if (!BlockFits(nextBlock, grid)) {
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
