#include <raylib.h>

#include <iostream>

#include "Head.h"
#include "KeyboardHandler.h"

int main() {
	const int screenWidth = 800;
	const int screenHeight = 600;

	float timeScale = 0.5;

	Head head;
	KeyboardHandler keyboardHandler(head);

	head.SetSpeed(2);

	head.SetPosX(screenWidth / 2);
	head.SetPosY(screenHeight / 2);

	head.SetDirX(1);
	head.SetDirY(0);

	head.bodySize = 20;

	int columns = screenWidth / head.bodySize;
	int rows = screenHeight / head.bodySize;

	InitWindow(screenWidth, screenHeight, "Snake");
	SetTargetFPS(60);

	while(WindowShouldClose() == false) {
		// float deltaTime = GetFrameTime() * timeScale;

		BeginDrawing();
		ClearBackground(DARKGRAY);

		if(head.GetPosX() > screenWidth - head.bodySize || head.GetPosX() < 0) {
			std::cout << "end of field x" << std::endl;
			head.SetDirX(-head.GetDirX());
			break;
		}
		if(head.GetPosY() > screenHeight - head.bodySize || head.GetPosY() < 0) {
			head.SetDirY(-head.GetDirY());
			std::cout << "end of field y" << std::endl;
			break;
		}

		keyboardHandler.HandleKeyboard();
		if(IsKeyDown(KEY_SPACE)) {
			break;
		}
		if(IsKeyDown(KEY_F)) {
			head.SetSpeed(0);
		}
		head.Move();

		std::cout << "headposx: " << head.GetPosX() << " headposy: " << head.GetPosY() << "\n";

		DrawRectangle(head.GetPosX(), head.GetPosY(), head.bodySize, head.bodySize, GREEN);

		for(int i = 0; i < columns; i++) {
			for(int j = 0; j < rows; j++) {
				DrawRectangleLines(i * head.bodySize, j * head.bodySize, head.bodySize, head.bodySize, GRAY);
			}
		}

		EndDrawing();

		// WaitTime(0.5);
	}

	CloseWindow();

	return 0;
}