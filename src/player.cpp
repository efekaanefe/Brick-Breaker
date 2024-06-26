#include "player.h"
#include "constants.h"


Player::Player()
{
    pos = {screenWidth/2 - 40, screenHeight - 40};
    width = playerWidth; height = playerHeight;
    color = playerColor;
}

void Player::Update()
{
    Draw();
    Move();
}

void Player::Draw(){
    Rectangle rect = { pos.x, pos.y, width, height };
    DrawRectangleRec(rect, color);
}

void Player::Move()
{
    Vector2 mousePos = GetMousePosition();
    pos.x = mousePos.x - width/2;

    if (pos.x < 0) pos.x = 0;
    if (pos.x + width > screenWidth) pos.x = screenWidth - width;
}