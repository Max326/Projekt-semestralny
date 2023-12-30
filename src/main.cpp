#include <raylib.h>

#include <iostream>

int main() {
	const int screenWidth = 800;
	const int screenHeight = 600;

	int ball_x = 100;
	int ball_y = 100;

	int ball_speed_x = 5;
	int ball_speed_y = 0;
	int ball_radius = 15;

	float timeScale = 0.5;

	InitWindow(screenWidth, screenHeight, "my first game");
	SetTargetFPS(60);

	while(WindowShouldClose() == false) {
		float deltaTime = GetFrameTime() * timeScale;
		BeginDrawing();
		ClearBackground(BLACK);


		if(ball_x >= screenWidth - ball_radius / 2 || ball_x <= ball_radius / 2) {
			break;
		}
		if(ball_y >= screenHeight - ball_radius / 2 || ball_y <= ball_radius / 2) {
			ball_speed_y *= -1;	 // Reverse the vertical direction
			break;
		}

		if(IsKeyDown(KEY_W)) {
			ball_speed_y = -5;
			ball_speed_x = 0;
		}

		if(IsKeyDown(KEY_S)) {
			ball_speed_y = 5;
			ball_speed_x = 0;
		}
		if(IsKeyDown(KEY_D)) {
			ball_speed_x = 5;
			ball_speed_y = 0;
		}
		if(IsKeyDown(KEY_A)) {
			ball_speed_x = -5;
			ball_speed_y = 0;
		}
		if(IsKeyDown(KEY_SPACE)) {
			break;
		}
		if(IsKeyDown(KEY_F)) {
			ball_speed_x = 0;
			ball_speed_y = 0;
		}

        ball_x += ball_speed_x;
		ball_y += ball_speed_y;

		DrawRectangle(ball_x, ball_y, ball_radius, ball_radius, GREEN);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}