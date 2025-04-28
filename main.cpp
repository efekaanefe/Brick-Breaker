#include "raylib.h"
#include "math.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <random>

const int screenWidth = 1600;
const int screenHeight = 900;
const Color backgroundColor = BLACK;

const int playerWidth = 200;
const int playerHeight = 30;
const Color playerColor = DARKGRAY;

const int ballRadius = 10;
const int ballSpeed = 500;
const Color ballColor = WHITE;

const int startX = 50;
const int startY = 50;
const int numRows = 5; // Reduced for better gameplay
const int numCols = 8; // Reduced for better gameplay
const int blockWidth = (screenWidth - startX * 2) / numCols;
const int blockHeight = 25;

// Forward declarations - Good practice for larger projects, helps with organization
class Ball;
class Block;
class Grid;
class Player;

class Ball {
public:
    Ball();
    Vector2 pos;
    float directionAngle, speed;
    int radius;
    void Update(Player& player, Grid& grid); // Pass by reference to modify the original
    void Reset();

private:
    void CollisionDetector(Player& player, Grid& grid); // Pass by reference
    void Draw();
    void Move();
    Color color;
    // Helper to normalize angle between 0 and 360
    float NormalizeAngle(float angle) {
        // Use fmodf for floating-point modulo
        angle = fmodf(angle, 360.0f);
        if (angle < 0) {
            angle += 360.0f;
        }
        return angle;
    }
};

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
    bool isAlive() const { return lifeRemaining > 0; } // Added for easier checking
    void decreaseLife(){
        lifeRemaining--;
    }
    Rectangle GetRect() const { // added for collision
        return {position.x, position.y, blockWidth, blockHeight};
    }
};

class Grid {
public:
    Grid();
    void Update(Ball& ball); // Pass ball, so grid can tell ball how to react to collision
    Block GetBlock(int row, int col) const; // Make it const, since it doesn't modify the grid
    // int numRows, numCols; // These are constants, not variables.
    std::vector<std::vector<Block>> grid;
    int getNumRows() const { return numRows;}
    int getNumCols() const { return numCols;}

private:
    void Draw();
    void Initialize();
    void SetRandomBlock(int row, int col);
    // void SetValue(int row, int col, int value); // Not used, removed.
};

class Player {
public:
    Player();
    void Update();
    Vector2 pos;
    float width, height;

private:
    void Draw();
    void Move();
    Color color;
};

Ball::Ball()
{
    pos = { screenWidth / 2, screenHeight * 0.8f }; // Use float literals for consistency
    directionAngle = 150.0f;
    speed = ballSpeed;
    color = ballColor;
    radius = ballRadius;
}

void Ball::Update(Player& player, Grid& grid) // Pass by reference
{
    CollisionDetector(player, grid); // Pass by reference
    Move();
    Draw();
}

void Ball::Reset() {
    pos = {screenWidth / 2, screenHeight * 0.8f};
    directionAngle = 150.0f;
    speed = ballSpeed;
}

void Ball::Draw()
{
    DrawCircle(pos.x, pos.y, radius, color);
}

void Ball::Move()
{
    float deltaTime = GetFrameTime();
    Vector2 velocity = { cosf(DEG2RAD * directionAngle), sinf(DEG2RAD * directionAngle) }; // Use cosf and sinf
    velocity.x *= speed;
    velocity.y *= speed;
    pos.x += velocity.x * deltaTime;
    pos.y += velocity.y * deltaTime;
}

void Ball::CollisionDetector(Player& player, Grid& grid) // Pass by reference
{
    // --- Wall Collision ---
    bool bounced = false; // Flag to prevent multiple bounces in one frame if needed

    // Right Wall
    if (pos.x >= (screenWidth - radius)) {
        pos.x = screenWidth - radius; // Clamp position to prevent sticking
        directionAngle = 180.0f - directionAngle;
        bounced = true;
    }
    // Left Wall
    else if (pos.x <= radius) {
        pos.x = radius; // Clamp position
        directionAngle = 180.0f - directionAngle;
        bounced = true;
    }

    // Top Wall
    if (pos.y <= radius) {
        pos.y = radius; // Clamp position
        directionAngle = 360.0f - directionAngle;
        bounced = true;
    }

    // NOTE: Bottom wall collision (loss condition) is typically handled outside this function.

    // Normalize angle after potential wall bounce
    directionAngle = NormalizeAngle(directionAngle);

    // --- Player Paddle Collision ---
    // Only check player collision if no wall bounce occurred this frame (optional optimization)
    if (!bounced) {
        Rectangle playerRect = {player.pos.x, player.pos.y, player.width, player.height};
        if (CheckCollisionCircleRec(pos, radius, playerRect)) {

            // Simple vertical bounce first (often good enough)
            // directionAngle = 360.0f - directionAngle;

            // --- More Controlled Paddle Bounce ---
            // Calculate normalized horizontal distance from paddle center (-1 to 1)
            float paddleCenter = player.pos.x + player.width / 2.0f;
            float relativeIntersectX = (pos.x - paddleCenter) / (player.width / 2.0f);

            // Clamp relativeIntersectX to avoid extreme angles if hit near edges
            relativeIntersectX = fmaxf(-1.0f, fminf(1.0f, relativeIntersectX));

            // Define the maximum angle deflection (e.g., 60 degrees means ball can leave between -60 and +60 from vertical)
            const float MAX_PADDLE_BOUNCE_ANGLE_DEG = 60.0f; // Adjust as needed

            // Calculate the outgoing angle based on hit position.
            // 270 degrees is straight up. We subtract the influence.
            // Hit left (-1) -> 270 - (-1 * 60) = 330 degrees (up-left)
            // Hit center (0) -> 270 - (0 * 60) = 270 degrees (up)
            // Hit right (1) -> 270 - (1 * 60) = 210 degrees (up-right)
            directionAngle = 270.0f - relativeIntersectX * MAX_PADDLE_BOUNCE_ANGLE_DEG;

            // Ensure ball is slightly above the paddle to prevent immediate re-collision
            pos.y = player.pos.y - radius - 0.1f; // Small offset

            bounced = true; // Mark that a bounce happened
        }
    }

    // Normalize angle after potential player bounce
    directionAngle = NormalizeAngle(directionAngle);


    // --- Block Collision ---
    // Only check block collision if no wall/player bounce occurred this frame
    if (!bounced) {
        for (int row = 0; row < grid.getNumRows(); ++row) {
            for (int col = 0; col < grid.getNumCols(); ++col) {
                // Use const reference for safety if not modifying the block pointer/reference itself
                const Block& block = grid.grid[row][col];

                if (block.isAlive()) { // Only check alive blocks.
                    Rectangle blockRect = block.GetRect();
                    if (CheckCollisionCircleRec(pos, radius, blockRect)) {

                        // --- Improved Block Collision Side Detection ---
                        // Calculate vector from block center to ball center
                        float blockCenterX = blockRect.x + blockRect.width / 2.0f;
                        float blockCenterY = blockRect.y + blockRect.height / 2.0f;
                        float dx = pos.x - blockCenterX;
                        float dy = pos.y - blockCenterY;

                        // Calculate the intersection depths
                        float intersectX = (blockRect.width / 2.0f + radius) - fabsf(dx);
                        float intersectY = (blockRect.height / 2.0f + radius) - fabsf(dy);

                        // Determine primary collision axis based on smallest overlap
                        if (intersectX > 0 && intersectY > 0) { // Ensure overlap exists
                            if (intersectX < intersectY) {
                                // Side collision (horizontal reflection)
                                directionAngle = 180.0f - directionAngle;
                                // Move ball out horizontally
                                pos.x += (dx > 0 ? intersectX : -intersectX);
                            } else {
                                // Top/Bottom collision (vertical reflection)
                                directionAngle = 360.0f - directionAngle;
                                // Move ball out vertically
                                pos.y += (dy > 0 ? intersectY : -intersectY);
                            }
                        } else {
                            // Fallback (e.g., exact corner hit or calculation issue) - simple vertical bounce
                            // This case might need more refinement if corners are problematic
                             directionAngle = 360.0f - directionAngle;
                        }


                        // Normalize angle after block bounce
                        directionAngle = NormalizeAngle(directionAngle);

                        // --- Handle Block State ---
                        // Need a mutable reference/pointer if we modify the block in the grid
                        grid.grid[row][col].decreaseLife(); // Modify the block in the actual grid

                        // If block is destroyed after hit, handle it (e.g., replace)
                        if (!grid.grid[row][col].isAlive()) {
                             // Example: Replace with a default/dead block
                             // grid.grid[row][col] = Block(); // Assuming default constructor makes a dead block
                             // Or maybe set a flag: grid.grid[row][col].setDead();
                             // Add score etc. here
                        }

                        // Important: Only handle one block collision per frame!
                        return;
                    }
                }
            }
        }
    }
}


Block::Block() : lifeRemaining(0), position({ 0, 0 }), color(BLANK) {}
Block::Block(Vector2 pos, Color colorGiven, int life) : lifeRemaining(life), position(pos), color(colorGiven) {}

int Block::handleCollision(Vector2 ballPosition, float ballRadius) {
     // This function is not needed anymore
    return 0;
}

void Block::Draw() {
    if (lifeRemaining > 0) {
        DrawRectangle(position.x, position.y, blockWidth, blockHeight, color);
    }
}

Grid::Grid()
{
    Initialize();
}

void Grid::Update(Ball& ball) // Pass by reference,
{
    Draw();
}

Block Grid::GetBlock(int row, int col) const
{
    return grid[row][col];
}


void Grid::Draw()
{
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            grid[row][col].Draw();
        }
    }
}

void Grid::Initialize()
{
    grid.resize(numRows); // Resize the rows
    for (int row = 0; row < numRows; row++)
    {
        grid[row].resize(numCols); // Resize each row
        for (int col = 0; col < numCols; col++)
        {
            SetRandomBlock(row, col);
        }
    }
}

void Grid::SetRandomBlock(int row, int col)
{
    Vector2 pos = {};
    pos.x = startX + col * (blockWidth + 1);
    pos.y = startY + row * (blockHeight + 1);

    // Seed the random number generator (better approach)
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 5); // Generate numbers between 1 and 5

    Color color;
    int value = dist(gen);

    if (value == 1) { color = PURPLE; }
    else if (value == 2) { color = RED; }
    else if (value == 3) { color = BLUE; }
    else if (value == 4) { color = ORANGE; }
    else if (value == 5) { color = GREEN; }
    else  { color = GRAY; }

    int life = 1;
    grid[row][col] = Block(pos, color, life);
}



Player::Player()
{
    pos = { screenWidth / 2 - 40, screenHeight - 40 };
    width = playerWidth; height = playerHeight;
    color = playerColor;
}

void Player::Update()
{
    Move();
    Draw();
}

void Player::Draw() {
    Rectangle rect = { pos.x, pos.y, width, height };
    DrawRectangleRec(rect, color);
}

void Player::Move()
{
    Vector2 mousePos = GetMousePosition();
    pos.x = mousePos.x - width / 2;

    if (pos.x < 0) pos.x = 0;
    if (pos.x + width > screenWidth) pos.x = screenWidth - width;
}

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Breakout Game");
    SetTargetFPS(75);

    Ball ball;
    Player player;
    Grid grid;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(backgroundColor);

        ball.Update(player, grid); // Pass by reference
        player.Update();
        grid.Update(ball); // Pass ball to grid

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
