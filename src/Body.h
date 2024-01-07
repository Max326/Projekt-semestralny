#pragma once

#include <raylib.h>

#include <memory>
#include <vector>

#include "Block.h"
#include "Head.h"
#include "RaylibUtils.h"

class Body : public Block
{
public:
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

	// void ElongateSnake() {
	// 	if(!bodyBlocks.empty()) {
	// 		const Block &lastBlock = *(bodyBlocks.back());

	// 		std::unique_ptr<Block> newBlock = std::make_unique<Block>(lastBlock);

	// 		bodyBlocks.push_back(std::move(newBlock));
	// 	}
	// }

	void ElongateSnake() { //TODO check this
		if(!bodyBlocks.empty()) {
			const auto &lastBlock = bodyBlocks.back();
			bodyBlocks.push_back(std::make_shared<Block>(*lastBlock));
		}
	}

	std::unique_ptr<Head> UpdateHead(std::unique_ptr<Head> head) { //TODO maybe try inserting the head into the vector
		if(!bodyBlocks.empty()) {
			bodyBlocks[0]->SetPosX(head->GetPosX());
			bodyBlocks[0]->SetPosY(head->GetPosY());
		}

		return std::move(head);
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
};