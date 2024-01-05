#pragma once
#include <raylib.h>

inline void DrawBlock(int x, int y, int squareSide, Color color) {
	DrawRectangle(x, y, squareSide, squareSide, color);
}