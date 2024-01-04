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
			head.SetPosX(head.GetPosX() - restX);
			head.GoUp();
		};
		if(IsKeyDown(KEY_S) && head.GetDirY() != -1 && head.GetDirY() != 1 && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
			head.SetPosX(head.GetPosX() - restX);
			head.GoDown();
		};

		if(IsKeyDown(KEY_D) && head.GetDirX() != -1 && head.GetDirX() != 1 && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
			head.SetPosY(head.GetPosY() - restY);
			head.GoRight();
		};
		if(IsKeyDown(KEY_A) && head.GetDirX() != 1 && head.GetDirX() != -1 && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
			head.SetPosY(head.GetPosY() - restY);
			head.GoLeft();
		};
		// TODO how to skip to the next square and not let the user stay in one?
	}

public:
	Head& head;
};