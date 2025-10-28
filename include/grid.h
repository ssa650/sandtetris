#pragma once 
#include <vector>
#include <raylib.h>

#include "position.h"

using namespace std;

class Grid{
    public:
        Grid();
        void Initialize();
        void LockBlock(const vector<Position> &positions, int id);
        void print();
        void Draw(int offsetX, int offsetY);
        int grid[20][10];
        
    private:
        int numRows;
        int numCols;
        int cellSize;
        vector<Color> colors;
};
