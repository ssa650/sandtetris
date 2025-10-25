#include "grid.h"
#include <iostream>
using namespace std;

Grid::Grid() {
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize() {
    for(int row = 0; row < numRows; row++){
        for (int column = 0; column < numCols; column++){
            grid[row][column] = 0;
        }
    }
}

void Grid::print(){
    for(int row = 0; row < numRows; row++){
        for(int column = 0; column < numCols; column++){
            cout << grid[row][column] << " ";
        }
        cout << endl;
    }
}

vector<Color> Grid::GetCellColors() {
    Color green = {47, 230, 23, 255};
    Color blue = {23, 64, 216, 255};
    Color red = {232, 18, 18, 255};
    Color yellow = {237, 234, 4, 255};
    Color purple = {166, 0, 247, 255};

    return {green, blue, red, yellow, purple};
}

void Grid::Draw() {
    for(int row = 0; row < numRows; row++){
        for(int column =0; column < numCols; column++){
            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize+1, row * cellSize+1, cellSize-1, cellSize-1, colors[cellValue]);
        }
    }
}