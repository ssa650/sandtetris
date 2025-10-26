#include <raylib.h>
#include "grid.h"
#include "blocks.cpp"

int main () {
    
    InitWindow(300, 600, "Sand Tetris");
    SetTargetFPS(60);

    Grid grid = Grid();
    grid.print();

	TBlock block = TBlock();
	

    while(WindowShouldClose() == false) {
        BeginDrawing();
        grid.Draw();
        block.Draw();
        EndDrawing();
    }

    CloseWindow();
}
