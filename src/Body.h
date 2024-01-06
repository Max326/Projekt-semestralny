#pragma once

#include <raylib.h>

#include <iostream>
#include <vector>

#include "Block.h"
#include "RaylibUtils.h"

class Body : public Block
{
public:
	std::vector<Block> bodyBlocks;

public:
	void UpdateSnake() {
		if(!bodyBlocks.empty()) {
			auto it1 = bodyBlocks.rbegin();
			auto it2 = std::next(bodyBlocks.rbegin());

			while(it2 != bodyBlocks.rend()) {
				std::cout << "bifor: it1 getposx: " << it1->GetPosX() << ", it1 getposy: " << it1->GetPosY() << std::endl;
				std::cout << "bifor: it2 getposx: " << it2->GetPosX() << ", it2 getposy: " << it2->GetPosY() << std::endl;
				*it1 = *it2;

				std::cout << "after: it1 getposx: " << it1->GetPosX() << ", it1 getposy: " << it1->GetPosY() << std::endl;
				std::cout << "after: it2 getposx: " << it2->GetPosX() << ", it2 getposy: " << it2->GetPosY() << std::endl;

				++it1;
				++it2;
			}

			std::cout << "koniec bodybloksa\n";
		}
	}

	void DrawSnake(const int tileSize) {
		for(auto it = bodyBlocks.begin(); it != bodyBlocks.end(); ++it) {
			if(it == bodyBlocks.begin()) {
				DrawSquare(it->GetPosX(), it->GetPosY(), tileSize, GREEN);
			} else {
				DrawSquare(it->GetPosX(), it->GetPosY(), tileSize, DARKGREEN);
			}
		}
	}
};