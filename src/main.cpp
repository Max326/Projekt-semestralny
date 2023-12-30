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
	int ball_radius = 15;

	float timeScale = 0.5;

	Head head;
	KeyboardHandler keyboardHandler(head);

	head.SetSpeed(3);

	head.SetPosX(100);
	head.SetPosY(100);

	InitWindow(screenWidth, screenHeight, "Snake");
	SetTargetFPS(60);

	while(WindowShouldClose() == false) {
		// float deltaTime = GetFrameTime() * timeScale;
		BeginDrawing();
		ClearBackground(BLACK);

		if(head.GetPosX() >= screenWidth - ball_radius / 2 || head.GetPosX() <= ball_radius / 2) {
			// ball_speed_x *= -1;
			std::cout << "end of field x" << std::endl;
			head.SetDirX(-head.GetDirX());
			break;
		}
		if(head.GetPosY() >= screenHeight - ball_radius / 2 || head.GetPosY() <= ball_radius / 2) {
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

		// ball_x += ball_speed_x;
		// ball_y += ball_speed_y;

		DrawRectangle(head.GetPosX(), head.GetPosY(), ball_radius, ball_radius, GREEN);

		EndDrawing();

        WaitTime(0.5);
	}

	CloseWindow();

	return 0;
}