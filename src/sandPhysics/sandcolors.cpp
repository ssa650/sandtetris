/******************************************************************
 * sandcolors.cpp -- Sand particle color variation generator
 *
 * Description: Generates color variations for sand particles to create
 *              visual diversity. Each sand particle gets a slightly
 *              different shade of its base color.
 *
 * Authors: Jethro Rolfe, Carson Chen, Howard Li, Jason Mai, Shayan Sharvini
 *
 *******************************************************************/
#include "sandPhysics/sandColor.h"
#include "colors.h"
#include <cstdlib>
#include <algorithm>

/******************************************************************
 * GetSandColorVariation -- Create a randomized shade of base color
 *
 * Parameters: baseColorIndex -- index of base color (2-8 for blocks)
 * Modifies: nothing
 *
 * Returns: Color with randomized RGB variation from base color
 *          Creates visual variety while maintaining color identity
 *******************************************************************/
Color GetSandColorVariation(int baseColorIndex) {
    // Get the base colors array
    // 0=grey, 1=black, 2=orange, 3=blue, 4=yellow, 5=cyan, 6=green, 7=purple, 8=red
    vector<Color> cellColors = GetCellColors();

    // Validate index
    if (baseColorIndex < 0 || baseColorIndex >= cellColors.size()) {
        return cellColors[0]; // Return grey as fallback
    }

    Color baseColor = cellColors[baseColorIndex];
    Color varied;
    varied.a = 255;

    // Apply color-specific variations
    switch (baseColorIndex) {
        case 2: { // Orange {255, 165, 0}
            int rVar = (rand() % 41) - 20;
            int gVar = (rand() % 51) - 25;
            varied.r = std::clamp(baseColor.r + rVar, 0, 255);
            varied.g = std::clamp(baseColor.g + gVar, 0, 255);
            varied.b = 0;
            break;
        }
        case 3: { // Blue {0, 0, 255}
            varied.r = 0;
            varied.g = 0;
            int bVar = (rand() % 141) - 70;  // Increased to ±70 for more visible variation
            varied.b = std::clamp(baseColor.b + bVar, 0, 255);
            break;
        }
        case 4: { // Yellow {255, 255, 0}
            // Use same variation for both R and G to keep yellow pure
            int variation = (rand() % 141) - 70;  // ±70 variation
            varied.r = std::clamp(baseColor.r + variation, 0, 255);
            varied.g = std::clamp(baseColor.g + variation, 0, 255);
            varied.b = 0;
            break;
        }
        case 5: { // Cyan {0, 255, 255}
            varied.r = 0;
            // Use same variation for both G and B to keep cyan pure
            int variation = (rand() % 141) - 70;  // ±70 variation
            varied.g = std::clamp(baseColor.g + variation, 0, 255);
            varied.b = std::clamp(baseColor.b + variation, 0, 255);
            break;
        }
        case 6: { // Green {0, 255, 0}
            varied.r = 0;
            int gVar = (rand() % 141) - 70;  // Increased to ±70 for more visible variation
            varied.g = std::clamp(baseColor.g + gVar, 0, 255);
            varied.b = 0;
            break;
        }
        case 7: { // Purple {128, 0, 128}
            int rVar = (rand() % 51) - 25;
            int bVar = (rand() % 51) - 25;
            varied.r = std::clamp(baseColor.r + rVar, 0, 255);
            varied.g = 0;
            varied.b = std::clamp(baseColor.b + bVar, 0, 255);
            break;
        }
        case 8: { // Red {255, 0, 0}
            int rVar = (rand() % 141) - 70;  // Increased to ±70 for more visible variation
            varied.r = std::clamp(baseColor.r + rVar, 0, 255);
            varied.g = 0;
            varied.b = 0;
            break;
        }
        default: { // Grey, Black, or unknown
            varied.r = baseColor.r;
            varied.g = baseColor.g;
            varied.b = baseColor.b;
            break;
        }
    }

    return varied;
}
