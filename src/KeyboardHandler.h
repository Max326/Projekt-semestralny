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

		if(IsKeyDown(KEY_W) && head.GetDirY() != 1 && head.GetDirY() != -1) {
			head.SetPosX(head.GetPosX() - restX + head.bodySize / 2);
			head.GoUp();
		};
		if(IsKeyDown(KEY_S) && head.GetDirY() != -1 && head.GetDirY() != 1) {
			head.SetPosX(head.GetPosX() - restX + head.bodySize / 2);
			head.GoDown();
		};

		if(IsKeyDown(KEY_D) && head.GetDirX() != -1 && head.GetDirX() != 1) {
			head.SetPosY(head.GetPosY() - restY + head.bodySize / 2);
			head.GoRight();
		};
		if(IsKeyDown(KEY_A) && head.GetDirX() != 1 && head.GetDirX() != -1) {
			head.SetPosY(head.GetPosY() - restY + head.bodySize / 2);
			head.GoLeft();
		};
		// TODO snake stops when W and D pressed and similar
	}

public:
	Head& head;
};