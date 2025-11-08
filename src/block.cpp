#include "block.h"
#include "config.h"

using namespace std;

Block::Block()
	: cellSize(GameConfig::CELL_SIZE),
	  rotationState(0),
	  colors(GetCellColors()),
	  rowOffset(0),
	  columnOffset(0)
{
}

void Block::Draw() const
{
	vector<Position> tiles = GetCellPositions();
	for (const Position& item : tiles)
	{
		DrawRectangle(item.column * cellSize + 1, item.row * cellSize + 1, cellSize - 1, cellSize - 1, colors[id]);
	}
}

void Block::Move(int rows, int columns)
{
	rowOffset += rows;
	columnOffset += columns;
}

vector<Position> Block::GetCellPositions() const
{
	const vector<Position>& tiles = cells.at(rotationState);
	vector<Position> movedTiles;
	for (const Position& item : tiles)
	{
		Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
		movedTiles.push_back(newPos);
	}
	return movedTiles;
}