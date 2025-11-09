/******************************************************************
 * position.cpp -- 2D grid position helper class
 *
 * Description: Simple class to represent a (row, column) position
 *              on the game grid. Used for tracking block cells.
 *
 * Authors: Jethro Rolfe, Carson Chen, Howard Li, Jason Mai, Shayan Sharvini
 *
 *******************************************************************/
#include "position.h"

/******************************************************************
 * Position -- Constructor, creates a position object
 *
 * Parameters: row    -- grid row (vertical position)
 *             column -- grid column (horizontal position)
 * Modifies: Initializes row and column member variables
 *
 * Returns: Position object
 *******************************************************************/
Position::Position(int row, int column)
	: row(row), column(column)
{
}