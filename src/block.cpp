/******************************************************************
 * block.cpp -- Tetris block base class implementation
 *
 * Description: Base class for all Tetris pieces (L, J, I, O, S, T, Z).
 *              Handles drawing, movement, and rotation states.
 *
 * Authors: Jethro Rolfe, Carson Chen, Howard Li, Jason Mai, Shayan Sharvini
 *
 *******************************************************************/
#include "block.h"
#include "position.h"
#include "config.h"

using namespace std;

/******************************************************************
 * Block -- Constructor, initializes block properties
 *
 * Parameters: none
 * Modifies: Initializes cell size, rotation, colors, position
 *
 * Returns: Block object
 *******************************************************************/
Block::Block()
	: cellSize(GameConfig::CELL_SIZE),   // 30 pixels per cell
	  rotationState(0),                  // Start at rotation 0
	  colors(GetCellColors()),           // Load color palette
	  rowOffset(0),                      // Start at top
	  columnOffset(0)                    // Start at left
{
}

/******************************************************************
 * Draw -- Render the block to the screen
 *
 * Parameters: none
 * Modifies: Screen output via raylib DrawRectangle
 *
 * Returns: nothing
 *******************************************************************/
void Block::Draw(int offsetX, int offsetY) const
{
	vector<Position> tiles = GetCellPositions();  // Get current positions
	for (const Position& item : tiles)
	{
		// Draw each cell of the block with 1px padding
		int x = offsetX + item.column * cellSize + 1;
		int y = offsetY + item.row * cellSize + 1;
		DrawRectangle(x, y, cellSize - 1, cellSize - 1, colors[id]);
	}
}

/******************************************************************
 * Move -- Move the block by specified rows and columns
 *
 * Parameters: rows    -- number of rows to move (+ down, - up)
 *             columns -- number of columns to move (+ right, - left)
 * Modifies: rowOffset, columnOffset
 *
 * Returns: nothing
 *******************************************************************/
void Block::Move(int rows, int columns)
{
	rowOffset += rows;       // Update vertical position
	columnOffset += columns;  // Update horizontal position
}

/******************************************************************
 * GetCellPositions -- Get current positions of all block cells
 *
 * Parameters: none
 * Modifies: nothing
 *
 * Returns: vector<Position> containing absolute positions of cells
 *******************************************************************/
vector<Position> Block::GetCellPositions() const
{
	const vector<Position>& tiles = cells.at(rotationState);  // Get current rotation
	vector<Position> movedTiles;                               // Store result
	for (const Position& item : tiles)
	{
		// Apply offsets to each cell position
		Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
		movedTiles.push_back(newPos);
	}
	return movedTiles;
}

/******************************************************************
 * Rotate -- Rotate blocks cohesively
 *
 * Parameters: none
 * Modifies: rotationState of current block
 *
 * Returns: nothing
 *******************************************************************/

void Block::Rotate(){
	int rotationCount = static_cast<int>(cells.size());
	if (rotationCount == 0){
		return;
	}
	rotationState = (rotationState + 1) % rotationCount;
}

/******************************************************************
 * UndoRotation -- undo rotate on blocks
 *
 * Parameters: none
 * Modifies: rotationState of current block
 *
 * Returns: nothing
 *******************************************************************/

void Block::UndoRotation(){
	int rotationCount = static_cast<int>(cells.size());
	if (rotationCount == 0)	{
		return;
	}
	rotationState = (rotationState - 1 + rotationCount) % rotationCount;
}

