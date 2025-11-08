#pragma once
#include <vector>
#include <map>
#include <raylib.h>

#include "colors.h"
#include "position.h"

using namespace std;

class Block
{
public:
	Block();
	void Draw() const;
	void Move(int rows, int columns);
	vector<Position> GetCellPositions() const;

	// Getters
	int GetId() const { return id; }
	const map<int, vector<Position>>& GetCells() const { return cells; }
	int GetRotationState() const { return rotationState; }

	// Setters
	void SetId(int newId) { id = newId; }

protected:
	int id;
	map<int, vector<Position>> cells;

private:
	int cellSize;
	int rotationState;
	vector<Color> colors;
	int rowOffset;
	int columnOffset;
};
