#pragma once
#include <raylib.h>
#include "Block.h"
class Food : public Block
{
public:
    Food(int x, int y){
        SetPosX(x);
        SetPosY(y);
    }
};