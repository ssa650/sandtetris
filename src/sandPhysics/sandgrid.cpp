#include <iostream>
#include "sandPhysics/sandgrid.h"
#include "colors.h"
using namespace std;

Sand::Sand()
	: numRows(SandConfig::SAND_ROWS),
	  numCols(SandConfig::SAND_COLS),
	  cellSize(SandConfig::SAND_CELL_SIZE),
	  colors(GetCellColors())
{
	Initialize();
}

void Sand::Initialize() {
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {
			grid[row][column] = 0;
			colorGrid[row][column] = BLACK;  // Initialize all colors to black
		}
	}
}

void Sand::print() const {
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {
			cout << grid[row][column] << " ";
		}
		cout << endl;
	}
}

void Sand::Draw(int offsetX, int offsetY) const {
	for (int row = 0; row < numRows; row++) {
		for (int column = 0; column < numCols; column++) {
			int cellValue = grid[row][column];
			// Only draw non-empty cells (skip 0 = empty)
			if (cellValue != 0) {
				const int x = offsetX + column * cellSize;
				const int y = offsetY + row * cellSize;
				DrawRectangle(x, y, cellSize, cellSize, colorGrid[row][column]);
			}
		}

	}
}

void Sand::DrawAggregated(int offsetX, int offsetY, int tileSize, int subdivisions) const {
	if (subdivisions <= 0) {
		return;
	}

	const int coarseRows = numRows / subdivisions;
	const int coarseCols = numCols / subdivisions;

	for (int row = 0; row < coarseRows; ++row) {
		for (int column = 0; column < coarseCols; ++column) {
			int occupiedCount = 0;
			int rSum = 0;
			int gSum = 0;
			int bSum = 0;

			const int startRow = row * subdivisions;
			const int startCol = column * subdivisions;

			for (int localRow = 0; localRow < subdivisions; ++localRow) {
				const int sandRow = startRow + localRow;
				for (int localCol = 0; localCol < subdivisions; ++localCol) {
					const int sandCol = startCol + localCol;
					if (grid[sandRow][sandCol] == 0) {
						continue;
					}

					const Color& cellColor = colorGrid[sandRow][sandCol];
					rSum += cellColor.r;
					gSum += cellColor.g;
					bSum += cellColor.b;
					occupiedCount++;
				}
			}

			if (occupiedCount == 0) {
				continue;
			}

			Color averagedColor;
			averagedColor.r = static_cast<unsigned char>(rSum / occupiedCount);
			averagedColor.g = static_cast<unsigned char>(gSum / occupiedCount);
			averagedColor.b = static_cast<unsigned char>(bSum / occupiedCount);
			averagedColor.a = 255;

			const int x = offsetX + column * tileSize + 1;
			const int y = offsetY + row * tileSize + 1;
			DrawRectangle(x, y, tileSize - 1, tileSize - 1, averagedColor);
		}
	}
}
