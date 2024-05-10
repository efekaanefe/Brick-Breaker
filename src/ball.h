#pragma once
#include "raylib.h"
#include "constants.h"


class Ball
{
    public:
        Ball();
        Vector2 pos;
        float directionAngle, speed;
        int radius;
        void Update();

    private:
        void Draw();
        void Move();
        void CollisionDetector();
        Color color;
};