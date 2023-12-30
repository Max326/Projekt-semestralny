#pragma once

class Head
{
private:
	int posX, posY;
	float speed;
	float dirX, dirY;

public:
    void SetSpeed(float newSpeed){speed = newSpeed;}

	int GetPosX() { return posX; };
	int GetPosY() { return posY; };

	void SetPosX(int x) { posX = x; };
	void SetPosY(int y) { posY = y; };

    int GetDirX() { return dirX; };
    int GetDirY() { return dirY; };

	void SetDirX(int directionX) { dirX = directionX; }
	void SetDirY(int directionY) { dirY = directionY; }

	void GoRight() {
		dirX = 1;
        dirY = 0;
	}
	void GoLeft() {
		dirX = -1;
        dirY = 0;
	}
	void GoDown() {
		dirY = -1;
        dirX = 0;
	}
	void GoUp() {
		dirY = 1;
        dirX = 0;
	}

	void Move() {
        SetPosX(GetPosX() + speed * dirX);
        SetPosY(GetPosY() + speed * dirY);
	}
};