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
#include "config.h"
#include "grid.h"
#include "blocks.h"
#include "sandPhysics/sandgrid.h"
#include "sandPhysics/sandPhysics.h"
#include "sandPhysics/addSand.h"

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

    // Main game loop - runs until user closes window
    while(WindowShouldClose() == false) {
        BeginDrawing();

		// Handle user input for spawning sand
		spawner.HandleInput();

		// Update sand physics simulation
		physics.Update();

		// Draw both grids (they share the same coordinate system)
		grid.Draw();
		sand.Draw();

		// Display FPS counter in top-left corner
		DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}
