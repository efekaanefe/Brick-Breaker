#include "ball.h"
#include "constants.h"
#include "math.h"

Ball::Ball()
{
    pos = {100, 100};
    directionAngle = 85.f;
    speed = ballSpeed;
    color = ballColor;
    radius = ballRadius;
}


void Ball::Update()
{
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