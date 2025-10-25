#include <raylib.h>
#include "grid.h"

int main () {
    Color coffeeBrown = {111, 78, 55, 1};
    InitWindow(300, 600, "Sand Tetris");
    SetTargetFPS(60);

    Grid grid = Grid();
    grid.grid[0][0] = 1;
    grid.grid[3][5] = 4;
    grid.grid[17][9] = 7;
    grid.print();

    while(WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(coffeeBrown);
        grid.Draw();
        EndDrawing();
    }

    CloseWindow();
}
