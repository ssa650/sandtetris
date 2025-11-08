#pragma once
#include "sandgrid.h"
#include <raylib.h>

class SandSpawner {
public:
    SandSpawner(Sand& sandGrid, int offsetX, int offsetY);
    void HandleInput();
    int sandColor = 2;  // Default to cyan, change to test colors (1-8)
    int brushSize = 5;  // 1=1x1, 2=2x2, 3=3x3, etc.

private:
    Sand& sand;
    int playfieldOffsetX;
    int playfieldOffsetY;
    void AddSandAtPosition(int row, int col);
};
