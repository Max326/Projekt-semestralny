#include <raylib.h>

#include <memory>
#include <vector>

#pragma once
#include "Head.h"

class KeyboardHandler
{
public:
	// std::unique_ptr<Head> HandleKeyboard(std::unique_ptr<Head> head) {
	std::shared_ptr<Head> HandleKeyboard(std::shared_ptr<Head> head) {
		int restX, restY;

		restX = head->GetPosX() % head->bodySize;
		restY = head->GetPosY() % head->bodySize;

		if(IsKeyDown(KEY_W) && head->GetDirY() != 1 && head->GetDirY() != -1 && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
			// std::cout << "W HIT\n";
			head->GoUp();
		};
		if(IsKeyDown(KEY_S) && head->GetDirY() != -1 && head->GetDirY() != 1 && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
			// std::cout << "S HIT\n";
			head->GoDown();
		};

		if(IsKeyDown(KEY_D) && head->GetDirX() != -1 && head->GetDirX() != 1 && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
			// std::cout << "D HIT\n";
			head->GoRight();
		};
		if(IsKeyDown(KEY_A) && head->GetDirX() != 1 && head->GetDirX() != -1 && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) {
			// std::cout << "A HIT\n";
			head->GoLeft();
		};

		return std::move(head);
	}
};