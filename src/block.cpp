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

void Block::Draw(int offsetX, int offsetY) const
{
	vector<Position> tiles = GetCellPositions();
	for (const Position& item : tiles)
	{
		int x = offsetX + item.column * cellSize + 1;
		int y = offsetY + item.row * cellSize + 1;
		DrawRectangle(x, y, cellSize - 1, cellSize - 1, colors[id]);
	}
}

void Block::Move(int rows, int columns)
{
	rowOffset += rows;
	columnOffset += columns;
}

void Block::Rotate()
{
	int rotationCount = static_cast<int>(cells.size());
	if (rotationCount == 0)
	{
		return;
	}
	rotationState = (rotationState + 1) % rotationCount;
}

void Block::UndoRotation()
{
	int rotationCount = static_cast<int>(cells.size());
	if (rotationCount == 0)
	{
		return;
	}
	rotationState = (rotationState - 1 + rotationCount) % rotationCount;
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
