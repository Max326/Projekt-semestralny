#pragma once

#include <raylib.h>

#include <memory>
#include <vector>

#include "Block.h"
#include "Head.h"
#include "RaylibUtils.h"

class Body : public Block
{
private:
	std::vector<std::shared_ptr<Block>> bodyBlocks;

public:
	void UpdateSnake() {
		if(bodyBlocks.size() > 1) {
			auto it1 = bodyBlocks.rbegin();

			while(std::next(it1) != bodyBlocks.rend()) {
				(*it1)->SetPosX((*std::next(it1))->GetPosX());

				(*it1)->SetPosY((*std::next(it1))->GetPosY());

				++it1;
			}
		}
	}

	bool FoodEaten(Block food) {
		for(int i = 0; i < bodyBlocks.size(); i++) {
			if(bodyBlocks[i]->GetPosX() == food.GetPosX() && bodyBlocks[i]->GetPosY() == food.GetPosY()) {
				return true;
			}
		}
		return false;
	}

	void ElongateSnake() {	// TODO check this
		if(!bodyBlocks.empty()) {
			const auto &lastBlock = bodyBlocks.back();
			bodyBlocks.push_back(std::make_shared<Block>(*lastBlock));
		}
	}

	void ElongateSnakePrecisely(float x, float y) {
		std::shared_ptr<Block> newBlock = std::make_shared<Block>(Vector2 {x, y});
		bodyBlocks.push_back(newBlock);
	}

	void UpdateHead(std::shared_ptr<Block> head) { 
		bodyBlocks.push_back(head);
	}

	void DrawSnake(const int tileSize) {
		for(auto it = bodyBlocks.begin(); it != bodyBlocks.end(); ++it) {
			DrawSquare((*it)->GetPosX(), (*it)->GetPosY(), tileSize, (*it == bodyBlocks.front()) ? GREEN : DARKGREEN);
		}
	}

	bool CollisionCheck() {
		for(int i = 1; i < bodyBlocks.size(); ++i) {
			if(bodyBlocks[0]->GetPosX() == bodyBlocks[i]->GetPosX() && bodyBlocks[0]->GetPosY() == bodyBlocks[i]->GetPosY()) {
				return true;
			}
		}
		return false;
	}

	std::shared_ptr<Block> operator()(size_t n) {
		return bodyBlocks[n];
	}
};