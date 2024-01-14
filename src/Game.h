#include <raylib.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "Body.h"
#include "Head.h"
#include "KeyboardHandler.h"
#include "RaylibUtils.h"

class Game // TODO AI
{
public:
	// settings
	const int tileSize = 10;  // this defines the size of the window (it scales with this)

	const int screenCols = 100;
	const int screenRows = 4;

	int offsetTiles = 4;
	int offset = offsetTiles * tileSize;  // for scalability

	const int screenWidth = tileSize * screenCols;
	const int screenHeight = tileSize * screenRows;

	double frameTime = 0.06;
	double lastUpdateTime;

	int score = 0;

public:
	void Start() {
		// first approach for the head object
		// std::unique_ptr<Head> head = std::make_unique<Head>();

		// second approach
		std::shared_ptr<Head> head = std::make_shared<Head>();

		KeyboardHandler keyboardHandler;
		Block food;
		Body body;

		head->bodySize = tileSize;

		head->SetPosX(offset + 2 * tileSize);
		head->SetPosY(offset);

		// this was the first approach
		// body.bodyBlocks.push_back(std::make_unique<Block>());
		// head = body.UpdateHead(std::move(head));

		body.UpdateHead(head);	// or body(0) = head;

		body.ElongateSnakePrecisely(offset + tileSize, offset);
		body.ElongateSnakePrecisely(offset, offset);

		head->SetSpeed(tileSize);

		head->SetDirX(1);
		head->SetDirY(0);

		InitWindow(2 * offset + screenWidth, 2 * offset + screenHeight, "Snake");
		SetTargetFPS(60);

		UpdateFood(food);

		while(WindowShouldClose() == false && InsideBoundaries(head)) {
			if(IsKeyDown(KEY_SPACE)) {
				break;
			}
			BeginDrawing();

			DrawGUI();

			if(body.FoodEaten(food)) {
				UpdateFood(food);
				body.ElongateSnake();
				++score;
			}

			DrawFood(food);

			head = keyboardHandler.HandleKeyboard(head);

			if(eventTriggered(frameTime)) {
				head->ResetTurn();
				body.UpdateSnake();

				head->Move();

				// head = body.UpdateHead(std::move(head));
				body(0) = head;
			}

			if(body.CollisionCheck()) {
				std::cout << "Collision detected.\n";
				break;
			}

			body.DrawSnake(tileSize);

			// DrawGrid(); // TODO to pokazac

			EndDrawing();
		}

		CloseWindow();
	}

	bool InsideBoundaries(std::shared_ptr<Head> head) {
		if(head->GetPosX() > offset + screenWidth - tileSize || head->GetPosX() < offset - tileSize / 4) {
			std::cout << "end of field x" << std::endl;
			return false;
		}
		if(head->GetPosY() > offset + screenHeight - tileSize || head->GetPosY() < offset - tileSize / 4) {
			std::cout << "end of field y" << std::endl;
			return false;
		}
		return true;
	}

	void DrawGrid() {
		for(int i = 0; i < screenCols; i++) {
			for(int j = 0; j < screenRows; j++) {
				DrawRectangleLines(offset + i * tileSize, offset + j * tileSize, tileSize, tileSize, BROWN);
			}
		}
	}

	void DrawGUI() {
		ClearBackground(LIME);
		DrawRectangle(0, 0, 2 * offset + screenWidth, offset, DARKBLUE);
		DrawRectangle(0, offset + screenHeight, 2 * offset + screenWidth, offset, DARKBLUE);
		DrawRectangle(0, 0, offset, 2 * offset + screenHeight, DARKBLUE);
		DrawRectangle(offset + screenWidth, 0, offset, 2 * offset + screenHeight, DARKBLUE);
		DrawRectangleLinesEx(Rectangle {float(offset - 5), float(offset - 5), float(screenWidth + 10), float(screenHeight + 10)}, 5, DARKGREEN);  // frame
		DrawText("Snake game", offset + 2 * tileSize, tileSize, tileSize * 2, SKYBLUE);
		DrawText(TextFormat("%i", score), offset + (screenCols / 2) * tileSize, offset + screenHeight + tileSize, tileSize * 2, SKYBLUE);
	}

	void UpdateFood(Block &food) {
		food.SetPosX(GetRandomValue(offsetTiles, offsetTiles + screenCols - 1) * tileSize);
		food.SetPosY(GetRandomValue(offsetTiles, offsetTiles + screenRows - 1) * tileSize);
	}

	void DrawFood(const Block &food) {
		DrawSquare(food.GetPosX(), food.GetPosY(), tileSize, RED);
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