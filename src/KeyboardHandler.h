#include <raylib.h>

#include <vector>

#pragma once
#include "Head.h"

class KeyboardHandler
{
public:
	KeyboardHandler(Head& headInstance) : head(headInstance) {}

	void HandleKeyboard() {
		int restX, restY;

		restX = head.GetPosX() % head.bodySize;
		restY = head.GetPosY() % head.bodySize;

		if(IsKeyDown(KEY_W) && head.GetDirY() != 1 && head.GetDirY() != -1 && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
			std::cout << "W HIT\n";
			head.SetPosX(head.GetPosX() - restX);
			if(restX >= head.bodySize / 2) {
				head.SetPosX(head.GetPosX() + head.bodySize);
			}
			head.SetPosY(head.GetPosY() - head.bodySize / 2);
			head.GoUp();
		};
		if(IsKeyDown(KEY_S) && head.GetDirY() != -1 && head.GetDirY() != 1 && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
			std::cout << "S HIT\n";
			head.SetPosX(head.GetPosX() - restX);
			if(restX >= head.bodySize / 2) {
				head.SetPosX(head.GetPosX() + head.bodySize);
			}
			head.SetPosY(head.GetPosY() + head.bodySize / 2);
			head.GoDown();
		};

		if(IsKeyDown(KEY_D) && head.GetDirX() != -1 && head.GetDirX() != 1 && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
			std::cout << "D HIT\n";
			head.SetPosY(head.GetPosY() - restY);
			if(restY >= head.bodySize / 2) {
				head.SetPosY(head.GetPosY() + head.bodySize);
			}
			head.SetPosX(head.GetPosX() + head.bodySize / 2);
			head.GoRight();
		};
		if(IsKeyDown(KEY_A) && head.GetDirX() != 1 && head.GetDirX() != -1 && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
			std::cout << "A HIT\n";
			head.SetPosY(head.GetPosY() - restY);
			if(restY >= head.bodySize / 2) {
				head.SetPosY(head.GetPosY() + head.bodySize);
			}
			head.SetPosX(head.GetPosX() - head.bodySize / 2);
			head.GoLeft();
		};
		// TODO fix teleportation
		// TODO after fixing the head movement, add bodytiles vector, which will have their own positions in a table probably
		// TODO and then run a check for the head colliding with them
	}

public:
	Head& head;
};