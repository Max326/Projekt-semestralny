#pragma once

#include <raylib.h>

#include <iostream>
#include <memory>
#include <vector>

#include "Block.h"
#include "Head.h"
#include "RaylibUtils.h"

class Body : public Block
{
public:
	// std::vector<Block> bodyBlocks;
	// std::vector<std::unique_ptr<Block>> bodyBlocks;
	std::vector<std::shared_ptr<Block>> bodyBlocks;

public:
	// Body(Head& headInstance) : head(headInstance) {};

	// void UpdateSnake() {
	// 	if(bodyBlocks.size() > 1) {
	// 		std::cout << "poczatek bodybloksa\n";

	// 		auto it1 = bodyBlocks.rbegin();
	// 		auto it2 = std::next(bodyBlocks.rbegin());

	// 		while(it2 != bodyBlocks.rend() - 1) {
	// 			// std::cout << "bifor: it1 getposx: " << (*it1)->GetPosX() << ", it1 getposy: " << (*it1)->GetPosY() << std::endl;
	// 			// std::cout << "bifor: it2 getposx: " << (*it2)->GetPosX() << ", it2 getposy: " << (*it2)->GetPosY() << std::endl;
	// 			*it1 = std::move(*it2);

	// 			// std::cout << "after: it1 getposx: " << (*it1)->GetPosX() << ", it1 getposy: " << (*it1)->GetPosY() << std::endl;
	// 			// std::cout << "after: it2 getposx: " << (*it2)->GetPosX() << ", it2 getposy: " << (*it2)->GetPosY() << std::endl;

	// 			++it1;
	// 			++it2;
	// 		}
	// 		for(const auto &block: bodyBlocks) {
	// 			if(!block) {
	// 				std::cerr << "Found a null block in bodyBlocks after UpdateSnake\n";
	// 				break;
	// 			}
	// 		}
	// 		std::cout << "koniec bodybloksa\n";
	// 	}
	// }

	void UpdateSnake() {
		if(bodyBlocks.size() > 1) {
			for(size_t i = bodyBlocks.size() - 1; i > 0; --i) { // TODO change to an iterator for additional rizz
				bodyBlocks[i]->SetPosX(bodyBlocks[i - 1]->GetPosX());
				bodyBlocks[i]->SetPosY(bodyBlocks[i - 1]->GetPosY());
			}
		}
	}

	// void ElongateSnake() {
	// 	if(!bodyBlocks.empty()) {
	// 		const Block &lastBlock = *(bodyBlocks.back());

	// 		std::unique_ptr<Block> newBlock = std::make_unique<Block>(lastBlock);

	// 		bodyBlocks.push_back(std::move(newBlock));
	// 	}
	// }

    void ElongateSnake() {
        if (!bodyBlocks.empty()) {
            const auto& lastBlock = bodyBlocks.back();
            bodyBlocks.push_back(std::make_shared<Block>(*lastBlock));
        }
    }

	std::unique_ptr<Head> UpdateHead(std::unique_ptr<Head> head) {
		if(!bodyBlocks.empty()) {
			bodyBlocks[0]->SetPosX(head->GetPosX());
			bodyBlocks[0]->SetPosY(head->GetPosY());
		}

		return std::move(head);	 // Return the updated head
	}

	// void DrawSnake(const int tileSize) {
	// 	for(auto it = bodyBlocks.begin(); it != bodyBlocks.end(); ++it) {
	// 		if(it == bodyBlocks.begin()) {
	// 			DrawSquare((*it)->GetPosX(), (*it)->GetPosY(), tileSize, GREEN);
	// 		} else {
	// 			DrawSquare((*it)->GetPosX(), (*it)->GetPosY(), tileSize, DARKGREEN);
	// 		}
	// 	}
	// }

	void DrawSnake(const int tileSize) {
		for(const auto &block: bodyBlocks) {
			if(block) {
				DrawSquare(block->GetPosX(), block->GetPosY(), tileSize, (block == bodyBlocks.front()) ? GREEN : DARKGREEN);
			}
		}
	}

    bool CollisionCheck(){
        for(int i = 1; i < bodyBlocks.size(); ++i) {
            if (bodyBlocks[0]->GetPosX() == bodyBlocks[i]->GetPosX() && bodyBlocks[0]->GetPosY() == bodyBlocks[i]->GetPosY()){
                return true;
            }
        }
        return false;
    }
};