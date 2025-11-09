/******************************************************************
 * colors.cpp -- Game color palette definitions
 *
 * Description: Defines all colors used in the game for blocks,
 *              sand particles, and backgrounds. Colors match
 *              standard Tetris block colors.
 *
 * Authors: Jethro Rolfe, Carson Chen, Howard Li, Jason Mai, Shayan Sharvini
 *
 *******************************************************************/
#include "colors.h"

using namespace std;

// Color definitions (RGBA format: Red, Green, Blue, Alpha)
const Color grey = { 26, 31, 40, 255 };        // Background/empty cells
const Color black = { 0, 0, 0, 255 };          // Unused
const Color orange = { 255, 165, 0, 255 };     // L-Block color
const Color blue = { 0, 0, 255, 255 };         // J-Block color
const Color yellow = { 255, 255, 0, 255 };     // O-Block color
const Color cyan = { 0, 255, 255, 255 };       // I-Block color
const Color green = { 0, 255, 0, 255 };        // S-Block color
const Color purple = { 128, 0, 128, 255 };     // T-Block color
const Color red = { 255, 0, 0, 255 };          // Z-Block color

// Sand color palette for testing
const vector<Color> testSandColors = { cyan, yellow, purple, green, red, blue, orange };

/******************************************************************
 * GetCellColors -- Returns color palette for grid cells
 *
 * Parameters: none
 * Modifies: nothing
 *
 * Returns: vector<Color> with colors indexed by cell value
 *          Index 0 = grey (empty), 1 = black, 2-8 = block colors
 *******************************************************************/
vector<Color> GetCellColors()
{
	return { grey , black, orange, blue, yellow, cyan, green, purple, red };
}