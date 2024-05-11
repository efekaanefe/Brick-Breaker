#pragma once

#include "raylib.h"

class Block {
public:
    Block(Vector2 pos, Color color, int life);
    int handleCollision(Vector2 ballPosition, float ballRadius);
    void draw() const;

private:
    int lifeRemaining, blockSize;
    Vector2 position;
    Color color;
};