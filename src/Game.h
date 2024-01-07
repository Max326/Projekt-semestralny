#include <raylib.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "Body.h"
#include "Head.h"
#include "KeyboardHandler.h"
#include "RaylibUtils.h"

class Game
{
public:
	// settings
	const int tileSize = 30;

	const int screenCols = 15;
	const int screenRows = 15;

	int offsetTiles = 4;
	int offset = offsetTiles * tileSize;  // for scalability

	const int screenWidth = tileSize * screenCols;
	const int screenHeight = tileSize * screenRows;

	double frameTime = 0.1;
	double lastUpdateTime;

	int score = 0;

public:
	void Start() {	// TODO std::visit
		std::unique_ptr<Head> head = std::make_unique<Head>();

		KeyboardHandler keyboardHandler;
		Block food;
		Body body;

		head->bodySize = tileSize;

		head->SetPosX(offset + 2 * tileSize);
		head->SetPosY(offset);

		body.bodyBlocks.push_back(std::make_unique<Block>());
		head = body.UpdateHead(std::move(head));
		body.bodyBlocks.push_back(std::make_unique<Block>(Vector2(offset + tileSize, offset)));
		body.bodyBlocks.push_back(std::make_unique<Block>(Vector2(offset, offset)));

		head->SetSpeed(tileSize);

		head->SetDirX(1);
		head->SetDirY(0);

		InitWindow(2 * offset + screenWidth, 2 * offset + screenHeight, "Snake");
		SetTargetFPS(60);

		UpdateFood(food);

		while(WindowShouldClose() == false) {
			BeginDrawing();
			ClearBackground(LIME);

			DrawRectangle(0, 0, 2 * offset + screenWidth, offset, DARKBLUE);
			DrawRectangle(0, offset + screenHeight, 2 * offset + screenWidth, offset, DARKBLUE);
			DrawRectangle(0, 0, offset, 2 * offset + screenHeight, DARKBLUE);
			DrawRectangle(offset + screenWidth, 0, offset, 2 * offset + screenHeight, DARKBLUE);

			DrawRectangleLinesEx(Rectangle {float(offset - 5), float(offset - 5), float(screenWidth + 10), float(screenHeight + 10)}, 5, DARKGREEN);  // frame
			DrawText("Snake game", offset + 2*tileSize, tileSize, tileSize * 2, SKYBLUE);
			DrawText(TextFormat("%i", score), offset + (screenCols/2)*tileSize, offset + screenHeight + tileSize, tileSize * 2, SKYBLUE);

			if(body.FoodEaten(food)) {
				UpdateFood(food);
				body.ElongateSnake();
				++score;
			}

			DrawSquare(food.GetPosX(), food.GetPosY(), tileSize, RED);
			// std::cout << "foodposx: " << food.GetPosX() << " foodposy: " << food.GetPosY() << "\n";

			if(head->GetPosX() > offset + screenWidth - tileSize || head->GetPosX() < offset - tileSize / 4) {
				std::cout << "end of field x" << std::endl;
				break;
			}
			if(head->GetPosY() > offset + screenHeight - tileSize || head->GetPosY() < offset - tileSize / 4) {
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

			// std::cout << "headposx: " << head->GetPosX() << " headposy: " << head->GetPosY() << "\n";

			if(body.CollisionCheck()) {
				std::cout << "Collision detected.\n";
				break;
			}

			body.DrawSnake(tileSize);

			// grid
			// for(int i = 0; i < screenCols; i++) {
			// 	for(int j = 0; j < screenRows; j++) {
			// 		DrawRectangleLines(i * tileSize, j * tileSize, tileSize, tileSize, GRAY);
			// 	}
			// }
			EndDrawing();
		}

		CloseWindow();
	}

	void UpdateFood(Block &food) {
		food.SetPosX(GetRandomValue(offsetTiles, offsetTiles + screenCols - 1) * tileSize);
		food.SetPosY(GetRandomValue(offsetTiles, offsetTiles + screenRows - 1) * tileSize);
	}

	bool eventTriggered(double interval) {
		double currentTime = GetTime();

		if(currentTime - lastUpdateTime >= interval) {
			lastUpdateTime = currentTime;
			return true;
		}
		return false;
	}
};