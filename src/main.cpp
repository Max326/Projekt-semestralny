#include <raylib.h>

#include <iostream>

#include "Head.h"
#include "KeyboardHandler.h"

int main() {
	const int screenWidth = 800;
	const int screenHeight = 600;

	// int ball_x = 100;
	// int ball_y = 100;

	// int ball_speed_x = 5;
	// int ball_speed_y = 0;

	float timeScale = 0.5;

	Head head;
	KeyboardHandler keyboardHandler(head);

	head.SetSpeed(3);

	head.SetPosX(screenWidth/2);
	head.SetPosY(screenHeight/2);

	head.SetDirX(1);
	head.SetDirY(0);

	head.bodySize = 20;

	InitWindow(screenWidth, screenHeight, "Snake");
	SetTargetFPS(144);

	while(WindowShouldClose() == false) {
		// float deltaTime = GetFrameTime() * timeScale;

		BeginDrawing();
		ClearBackground(BLACK);

		if(head.GetPosX() >= screenWidth - head.bodySize / 2 || head.GetPosX() <= head.bodySize / 2) {
			// ball_speed_x *= -1;
			std::cout << "end of field x" << std::endl;
			head.SetDirX(-head.GetDirX());
			break;
		}
		if(head.GetPosY() >= screenHeight - head.bodySize / 2 || head.GetPosY() <= head.bodySize / 2) {
			// ball_speed_y *= -1;
			head.SetDirY(-head.GetDirY());
			std::cout << "end of field y" << std::endl;
			break;
		}

		keyboardHandler.HandleKeyboard();
		if(IsKeyDown(KEY_SPACE)) {
			break;
		}
		if(IsKeyDown(KEY_F)) {
			// ball_speed_x = 0;
			// ball_speed_y = 0;

			head.SetSpeed(0);
		}
		head.Move();

		std::cout << "headposx: " << head.GetPosX() << " headposy: " << head.GetPosY() << "\n";

		// ball_x += ball_speed_x;
		// ball_y += ball_speed_y;

		DrawRectangle(head.GetPosX(), head.GetPosY(), head.bodySize, head.bodySize, GREEN);

		DrawGrid(1000, 100);

		EndDrawing();

		// WaitTime(0.5);
	}

	CloseWindow();

	return 0;
}