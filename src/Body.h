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
	std::vector<std::unique_ptr<Block>> bodyBlocks;

public:
	void UpdateSnake() {
		if(!bodyBlocks.empty()) {
			auto it1 = bodyBlocks.rbegin();
			auto it2 = std::next(bodyBlocks.rbegin());

			while(it2 != bodyBlocks.rend()) {
				std::cout << "bifor: it1 getposx: " << (*it1)->GetPosX() << ", it1 getposy: " << (*it1)->GetPosY() << std::endl;
				std::cout << "bifor: it2 getposx: " << (*it2)->GetPosX() << ", it2 getposy: " << (*it2)->GetPosY() << std::endl;
				*it1 = std::move(*it2);

				std::cout << "after: it1 getposx: " << (*it1)->GetPosX() << ", it1 getposy: " << (*it1)->GetPosY() << std::endl;
				std::cout << "after: it2 getposx: " << (*it2)->GetPosX() << ", it2 getposy: " << (*it2)->GetPosY() << std::endl;

				++it1;
				++it2;
			}

			std::cout << "koniec bodybloksa\n";
		}
	}

	// void UpdateSnake() {
	// 	if(!bodyBlocks.empty()) {
	// 		auto it1 = bodyBlocks.rbegin();
	// 		auto it2 = std::next(bodyBlocks.rbegin());

	// 		while(it2 != bodyBlocks.rend()) {
	// 			*it1 = std::move(*it2);
	// 			++it1;
	// 			++it2;
	// 		}
	// 	}
	// }

	void ElongateSnake() {
		if(!bodyBlocks.empty()) {
			const Block& lastBlock = *(bodyBlocks.back());

			std::unique_ptr<Block> newBlock = std::make_unique<Block>(lastBlock);

			bodyBlocks.push_back(std::move(newBlock));
		}
	}

	std::unique_ptr<Head> UpdateHead(std::unique_ptr<Head> head) {
		bodyBlocks[0] = std::move(head);

		return std::move(head);
	}

	void DrawSnake(const int tileSize) {
		for(auto it = bodyBlocks.begin(); it != bodyBlocks.end(); ++it) {
			if(it == bodyBlocks.begin()) {
				DrawSquare((*it)->GetPosX(), (*it)->GetPosY(), tileSize, GREEN);
			} else {
				DrawSquare((*it)->GetPosX(), (*it)->GetPosY(), tileSize, DARKGREEN);
			}
		}
	}
};