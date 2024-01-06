#include <raylib.h>

#include <iostream>
#include <vector>

#include "Body.h"
#include "Food.h"
#include "Head.h"
#include "KeyboardHandler.h"
#include "RaylibUtils.h"

class Game
{
public:
	void Start() {
		const int tileSize = 20;

		const int screenCols = 20;
		const int screenRows = 20;

		const int screenWidth = tileSize * screenCols;
		const int screenHeight = tileSize * screenRows;

		float timeScale = 0.5;

		Head head;
		KeyboardHandler keyboardHandler(head);
		Food food;

		head.SetSpeed(20);

		head.SetPosX(40);
		head.SetPosY(0);

		head.SetDirX(1);
		head.SetDirY(0);

		head.bodySize = 20;

		InitWindow(screenWidth, screenHeight, "Snake");
		SetTargetFPS(60);

		UpdateFood(food, tileSize, screenCols, screenRows);

		Body body;

        Block block1(Vector2(20, 0));
        Block block2(Vector2(0, 0));

		while(WindowShouldClose() == false) {
			// float deltaTime = GetFrameTime() * timeScale;

			BeginDrawing();
			ClearBackground(DARKGRAY);

			if(head.GetPosX() == food.GetPosX() && head.GetPosY() == food.GetPosY()) {
				UpdateFood(food, tileSize, screenCols, screenRows);
			}

			DrawSquare(food.GetPosX(), food.GetPosY(), tileSize, RED);
			// std::cout << "foodposx: " << food.GetPosX() << " foodposy: " << food.GetPosY() << "\n";

			if(head.GetPosX() > screenWidth - head.bodySize / 4 || head.GetPosX() < -head.bodySize / 4) {
				std::cout << "end of field x" << std::endl;
				head.SetDirX(-head.GetDirX());
				break;
			}
			if(head.GetPosY() > screenHeight - head.bodySize / 4 || head.GetPosY() < -head.bodySize / 4) {
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
				head.SetSpeed(head.GetSpeed() + 0.1f);
			}

			body.bodyBlocks = {head, block1, block2};

			if(eventTriggered(0.2)) {
				body.UpdateSnake();
				head.Move();
			}

			std::cout << "headposx: " << head.GetPosX() << " headposy: " << head.GetPosY() << "\n";

            body.DrawSnake(tileSize);
			// DrawSquare(head.GetPosX(), head.GetPosY(), tileSize, GREEN);

			for(int i = 0; i < screenCols; i++) {
				for(int j = 0; j < screenRows; j++) {
					DrawRectangleLines(i * head.bodySize, j * head.bodySize, head.bodySize, head.bodySize, GRAY);
				}
			}

			EndDrawing();
		}

		CloseWindow();
	}

	void UpdateFood(Food &food, const int tile, const int cols, const int rows) {
		food.SetPosX(GetRandomValue(0, cols - 1) * tile);
		food.SetPosY(GetRandomValue(0, rows - 1) * tile);
	}

	double lastUpdateTime;

	bool eventTriggered(double interval) {
		double currentTime = GetTime();

		if(currentTime - lastUpdateTime >= interval) {
			lastUpdateTime = currentTime;
			return true;
		}
		return false;
	}
};