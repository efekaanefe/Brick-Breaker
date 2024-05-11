#include "ball.h"
#include "block.h"
#include "constants.h"
#include "math.h"
#include <cstdio>


Ball::Ball()
{
    pos = {screenWidth/2, screenHeight*0.8};
    directionAngle = 150.f;
    speed = ballSpeed;
    color = ballColor;
    radius = ballRadius;
}


void Ball::Update(Player player, Grid grid)
{
    CollisionDetector(player, grid);
    Draw();
    Move();
}

void Ball::Draw()
{
    DrawCircle(pos.x, pos.y, radius, color);
}

void Ball::Move()
{   
    float deltaTime = GetFrameTime();
    Vector2 velocity =  {cos(DEG2RAD* directionAngle), sin(DEG2RAD * directionAngle)};
    velocity.x *= speed;
    velocity.y *= speed;
    pos.x += velocity.x * deltaTime;
    pos.y += velocity.y * deltaTime;
}

void Ball::CollisionDetector(Player player, Grid grid) // and updater
{
    // walls
    if ((pos.x >= (screenWidth - radius)) || (pos.x <= radius)) {
        directionAngle = 180 - directionAngle;
    }
    if ((pos.y >= (screenHeight - radius)) || (pos.y <= radius)) {
        directionAngle = 360 - directionAngle;
    }

    if (pos.y >= (player.pos.y-radius)){
        directionAngle = 360 - directionAngle; // TODO: make this more fun
    }

    // TODO: add collision with blocks
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {

            Block block = grid.GetBlock(row, col);
            int collisionType = block.handleCollision(pos, radius);

            if (collisionType == 1){
                directionAngle = 360 - directionAngle;
                printf("%d", collisionType);
                return;
            }
            else if (collisionType == 2){
                directionAngle = 180 - directionAngle;
                printf("%d", collisionType);
                return;
            }
        }
    }
}