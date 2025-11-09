#pragma once
#include <raylib.h>
#include <vector>

using namespace std;

extern const Color grey;
extern const Color black;
extern const Color green;
extern const Color blue;
extern const Color red;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color orange;

// Test sand colors - matches tetris block colors
extern const vector<Color> testSandColors;

vector<Color> GetCellColors();


