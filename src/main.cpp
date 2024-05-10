#include "raylib.h"
#include "player.h"
#include<string>  


int main() 
{
    InitWindow(screenWidth, screenHeight, "Brick Braker");
    SetTargetFPS(60);              
    Player player = Player();
    
    // Main game loop
    while (!WindowShouldClose())  
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("This is a raylib example", screenWidth/2-150, 20, 20, DARKGRAY);
            DrawFPS(10, 10);
            
            player.Update();
                        
        EndDrawing();
    }

    CloseWindow();        

    return 0;
}