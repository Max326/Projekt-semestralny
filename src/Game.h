#include <raylib.h>

#include <algorithm>
#include <iostream>
#include <memory>
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
		const int tileSize = 20;  // TODO fix this not being scalable

		const int screenCols = 20;
		const int screenRows = 20;

		const int screenWidth = tileSize * screenCols;
		const int screenHeight = tileSize * screenRows;

		double frameTime = 0.1;

		std::unique_ptr<Head> head = std::make_unique<Head>();

		KeyboardHandler keyboardHandler;
		Food food;

		Body body;

		head->bodySize = tileSize;

		head->SetPosX(2 * tileSize);
		head->SetPosY(0);

		body.bodyBlocks.push_back(std::make_unique<Block>(Vector2(0, 0)));	// TODO this maybe can be changed
		head = body.UpdateHead(std::move(head));
		body.bodyBlocks.push_back(std::make_unique<Block>(Vector2(tileSize, 0)));
		body.bodyBlocks.push_back(std::make_unique<Block>(Vector2(0, 0)));

		head->SetSpeed(tileSize);

		head->SetDirX(1);
		head->SetDirY(0);

		InitWindow(screenWidth, screenHeight, "Snake");
		SetTargetFPS(60);

		UpdateFood(food, tileSize, screenCols, screenRows);

		while(WindowShouldClose() == false) {
			BeginDrawing();
			ClearBackground(LIME);

			if(head->GetPosX() == food.GetPosX() && head->GetPosY() == food.GetPosY()) {
				UpdateFood(food, tileSize, screenCols, screenRows);
				body.ElongateSnake();
			}

			DrawSquare(food.GetPosX(), food.GetPosY(), tileSize, RED);
			// std::cout << "foodposx: " << food.GetPosX() << " foodposy: " << food.GetPosY() << "\n";

			if(head->GetPosX() > screenWidth - tileSize / 4 || head->GetPosX() < -tileSize / 4) {
				std::cout << "end of field x" << std::endl;
				head->SetDirX(-head->GetDirX());
				break;
			}
			if(head->GetPosY() > screenHeight - tileSize / 4 || head->GetPosY() < -tileSize / 4) {
				head->SetDirY(-head->GetDirY());
				std::cout << "end of field y" << std::endl;
				break;
			}

			head = keyboardHandler.HandleKeyboard(std::move(head));

			if(IsKeyDown(KEY_SPACE)) {
				break;
			}
			if(IsKeyDown(KEY_F)) {
				head->SetSpeed(0);
			}
			if(IsKeyDown(KEY_G)) {
				head->SetSpeed(head->GetSpeed() + 0.1f);
			}

			if(eventTriggered(frameTime)) {
				head->ResetTurn();
				body.UpdateSnake();

				head->Move();

				head = body.UpdateHead(std::move(head));
			}

			std::cout << "headposx: " << head->GetPosX() << " headposy: " << head->GetPosY() << "\n";

			if(body.CollisionCheck()) {
				std::cout << "Collision detected.\n";
				break;
			}

			body.DrawSnake(tileSize);

			// for(int i = 0; i < screenCols; i++) {
			// 	for(int j = 0; j < screenRows; j++) {
			// 		DrawRectangleLines(i * tileSize, j * tileSize, tileSize, tileSize, GRAY);
			// 	}
			// }

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