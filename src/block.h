#pragma once
#include "raylib.h"


class Block {

    private:
        int lifeRemaining;
        Vector2 position;
        Color color;

    public:
        Block();
        Block(Vector2 pos, Color colorGiven, int life);
        
        int handleCollision(Vector2 ballPosition, float ballRadius);
        void Draw();
};