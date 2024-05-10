#pragma once
#include "raylib.h"
#include "constants.h"
#include "player.h"
#include "grid.h"


class Ball
{
    public:
        Ball();
        Vector2 pos;
        float directionAngle, speed;
        int radius;
        void Update(Player player, Grid grid);

    private:
        void CollisionDetector(Player player, Grid grid);
        void Draw();
        void Move();
        Color color;
};