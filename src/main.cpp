#include <raylib.h>

#include <iostream>

int main() {
	const int screenWidth = 800;
	const int screenHeight = 600;

	int ball_x = 100;
	int ball_y = 100;

	int ball_speed_x = 5;
	int ball_speed_y = 5;
	int ball_radius = 15;

	InitWindow(screenWidth, screenHeight, "my first game");
	SetTargetFPS(60);

	while(WindowShouldClose() == false) {
		BeginDrawing();
		ClearBackground(BLACK);
		ball_x += ball_speed_x;
		ball_y += ball_speed_y;

        // Bounce off the edges of the window
        if(ball_x >= screenWidth - ball_radius || ball_x <= ball_radius) {
            ball_speed_x *= -1; // Reverse the horizontal direction
        }
        if(ball_y >= screenHeight - ball_radius || ball_y <= ball_radius) {
            ball_speed_y *= -1; // Reverse the vertical direction
        }

		DrawCircle(ball_x, ball_y, ball_radius, GREEN);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}