#include <raylib.h>

#include <vector>

#pragma once
#include "Head.h"

class KeyboardHandler
{
public:
	KeyboardHandler(Head& headInstance) : head(headInstance) {}

	std::vector<int> lastDir = {0, 0};

	void HandleKeyboard() {
		if(IsKeyDown(KEY_W)) {
			head.GoRight();
		};
		if(IsKeyDown(KEY_S)) {
            head.GoDown();
		};
		if(IsKeyDown(KEY_D)) {
            head.GoRight();
		};
		if(IsKeyDown(KEY_A)) {
            head.GoLeft();
		};
	}

public:
	Head& head;
};