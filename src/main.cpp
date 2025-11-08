#include <raylib.h>
#include "config.h"
#include "grid.h"
#include "blocks.h"
#include "sandPhysics/sandgrid.h"
#include "sandPhysics/sandPhysics.h"
#include "sandPhysics/addSand.h"

int main () {

    // Initialize window with configured dimensions
    InitWindow(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT, GameConfig::WINDOW_TITLE);
    SetTargetFPS(GameConfig::TARGET_FPS);

    Grid grid = Grid();
    grid.print();

	Sand sand = Sand();
	sand.print();

	// Initialize sand physics and spawner
	SandPhysics physics(sand);
	SandSpawner spawner(sand);

    while(WindowShouldClose() == false) {
        BeginDrawing();

		// Handle user input for spawning sand
		spawner.HandleInput();

		// Update sand physics
		physics.Update();

		// Draw both grids (they now share the same coordinate system)
		grid.Draw();
		sand.Draw();

		// Display FPS in top-left corner
		DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}
