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
				*it1 = *it2;
				++it1;
				++it2;
			}
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