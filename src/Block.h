#pragma once

class Block
{
protected:
	int posX, posY;

public:
	int GetPosX() const { return posX; };
	int GetPosY() const { return posY; };

	void SetPosX(int x) { posX = x; };
	void SetPosY(int y) { posY = y; };
};