#pragma once

#include <vector>
#include <iostream>

#include "Block.h"

class Body : public Block
{
    std::vector<Block> bodyBlocks;

    // TODO: implement a list of snake elements by the bodyblocks vector of vector2s
    // TODO: make a queue of direction vectors change the positions of blocks (function for that)

    void UpdateSnake(std::vector<Block> &bodyBlocks){
        for(int i = 0; i < bodyBlocks.size(); i++){
            std::cout << "dupa\n";   
        }
    }
};