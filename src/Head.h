#pragma once

#include "Block.h"

class Head : public Block
{
private:
	float speed;
	int dirX, dirY;

public:
	int bodySize;
	bool turnMade;

	void SetSpeed(float newSpeed) { speed = newSpeed; }
	float GetSpeed() { return speed; };

	int GetDirX() { return dirX; };
	int GetDirY() { return dirY; };

	void SetDirX(int directionX) { dirX = directionX; }
	void SetDirY(int directionY) { dirY = directionY; }

	void ResetTurn() {
		turnMade = false;
	}

	void GoRight() {
		if(!turnMade) {
			dirX = 1;
			dirY = 0;
			turnMade = true;
		}
	}
	void GoLeft() {
		if(!turnMade) {
			dirX = -1;
			dirY = 0;
			turnMade = true;
		}
	}
	void GoDown() {
		if(!turnMade) {
			dirX = 0;
			dirY = 1;
			turnMade = true;
		}
	}
	void GoUp() {
		if(!turnMade) {
			dirX = 0;
			dirY = -1;
			turnMade = true;
		}
	}

	void Move() {
		SetPosX(GetPosX() + speed * dirX);
		SetPosY(GetPosY() + speed * dirY);
	}
};