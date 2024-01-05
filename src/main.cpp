#include <raylib.h>

#include <iostream>

#include "Head.h"
#include "KeyboardHandler.h"
#include "Food.h"

#include "RaylibUtils.h"

int main() {
	const int tileSize = 20;

	const int screenCols = 20;
	const int screenRows = 20;

	const int screenWidth = tileSize * screenCols;
	const int screenHeight = tileSize * screenRows;

	float timeScale = 0.5;

	Head head;
	KeyboardHandler keyboardHandler(head);

	head.SetSpeed(2);

	head.SetPosX(0);
	head.SetPosY(0);

	head.SetDirX(1);
	head.SetDirY(0);

	head.bodySize = 20;

	int columns = screenWidth / head.bodySize;
	int rows = screenHeight / head.bodySize;

    int foodX, foodY;

	InitWindow(screenWidth, screenHeight, "Snake");
	SetTargetFPS(60);

	while(WindowShouldClose() == false) {
		// float deltaTime = GetFrameTime() * timeScale;

		BeginDrawing();
		ClearBackground(DARKGRAY);

        foodX = GetRandomValue(0, columns-1);
        foodY = GetRandomValue(0, rows-1);

        Food food(foodX, foodY);
        DrawBlock(food.GetPosX(), food.GetPosY(), tileSize, RED);

		if(head.GetPosX() > screenWidth - head.bodySize/4 || head.GetPosX() < -head.bodySize/4) {
			std::cout << "end of field x" << std::endl;
			head.SetDirX(-head.GetDirX());
			break;
		}
		if(head.GetPosY() > screenHeight - head.bodySize/4 || head.GetPosY() < -head.bodySize/4) {
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
        if(IsKeyDown(KEY_G)) {
			head.SetSpeed(head.GetSpeed()+0.1f);
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
	}

	CloseWindow();

	return 0;
}