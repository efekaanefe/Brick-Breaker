#include "raylib.h"
#include "player.h"
#include "ball.h"

#include<string>  


int main() 
{
    InitWindow(screenWidth, screenHeight, "Brick Braker");
    SetTargetFPS(75);              
    Player player = Player();
    Ball ball = Ball();
    
    // Main game loop
    while (!WindowShouldClose())  
    {
        BeginDrawing();
            ClearBackground(backgroundColor);
            DrawText("This is a raylib example", screenWidth/2-150, 20, 20, LIGHTGRAY);
            DrawFPS(10, 10);
            
            player.Update();
            ball.Update();
                        
        EndDrawing();
    }

    CloseWindow();        

    return 0;
}