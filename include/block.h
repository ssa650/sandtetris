#pragma once
#include <vector>
#include <map>

#include "colors.h"
#include "position.h"

using namespace std;

class Block
{
public:
	Block();
	void Draw(int offsetX, int offsetY);
	void Move(int rows, int columns);
	void Rotate();
	void UndoRotation();
	vector<Position> GetCellPositions();
	int id;
	map<int, vector<Position>> cells;

private:
	int cellSize;
	int rotationState;
	vector<Color> colors;
	int rowOffset;
	int columnOffset;
};
