#pragma once

#include <raylib.h>

class Block
{
protected:
	int posX, posY;

public:
    Block () = default;

	Block(Vector2 position) {
        SetPosX(position.x);
        SetPosY(position.y);
    }
    
	Block(const Block& other) = default;
	Block(Block&& other) = default;
	Block& operator=(const Block& other) = default;
	Block& operator=(Block&& other) = default;

	int GetPosX() const { return posX; };
	int GetPosY() const { return posY; };

	void SetPosX(int x) { posX = x; };
	void SetPosY(int y) { posY = y; };
};