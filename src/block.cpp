#include "Block.h"
#include "constants.h"

Block::Block(Vector2 pos, Color colorGiven, int life){
    lifeRemaining = life;
    position = pos;
    color = colorGiven;
}

int Block::handleCollision(Vector2 ballPosition, float ballRadius) {
    Rectangle blockRect = { position.x, position.y, blockWidth, blockHeight};
    Rectangle ballRect = { ballPosition.x - ballRadius, ballPosition.y - ballRadius, ballRadius * 2, ballRadius * 2 };

    float ballRight = ballPosition.x + ballRadius;
    float ballLeft = ballPosition.x - ballRadius;
    float ballTop = ballPosition.y - ballRadius;
    float ballBottom = ballPosition.y + ballRadius;

    bool collidedLeft = ballRight > blockRect.x && ballRight < blockRect.x + ballRect.width && ballTop < ballRect.y + ballRect.height && ballBottom > ballRect.y;
    bool collidedRight = ballLeft < blockRect.x + blockRect.width && ballLeft > ballRect.x && ballTop < ballRect.y + ballRect.height && ballBottom > ballRect.y;
    bool collidedTop = ballBottom > blockRect.y && ballBottom < ballRect.y + ballRect.height && ballLeft < ballRect.x + ballRect.width && ballRight > ballRect.x;
    bool collidedBottom = ballTop < blockRect.y + blockRect.height && ballTop > ballRect.y && ballLeft < ballRect.x + ballRect.width && ballRight > ballRect.x;

    if (collidedLeft || collidedRight) {
        lifeRemaining--;
        return 1; 
    }
    else if (collidedBottom || collidedTop){
        lifeRemaining--;
        return 2;
    }

    return 0; // No collision
}

void Block::draw() const {
    DrawRectangle(position.x, position.y, blockWidth, blockHeight, GRAY);
}

