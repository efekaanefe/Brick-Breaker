#pragma once
#include "raylib.h"
#include "constants.h"

class Player{
    public: 
        Player();
        void Update();
        Vector2 pos;
        int width; int height;

    private:
        void Draw();
        void Move();
};