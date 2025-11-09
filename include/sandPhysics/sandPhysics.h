#pragma once
#include "sandgrid.h"

class SandPhysics {
public:
    SandPhysics(Sand& sandGrid);
    void Update();

private:
    Sand& sand;
    bool IsSand(int cellValue);
    bool CanMoveTo(int row, int col);
    void ProcessCell(int row, int col);
    int frameCounter = 0;
};
