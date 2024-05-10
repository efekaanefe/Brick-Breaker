#include "ball.h"
#include "constants.h"
#include "math.h"

Ball::Ball()
{
    pos = {100, 100};
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



}