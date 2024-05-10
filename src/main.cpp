#include "raylib.h"
#include<string>  

const int screenWidth = 1600;
const int screenHeight = 900;
class Player{
    public: 
        // int width, height;
        Rectangle rect = { screenWidth/2 - 40, screenHeight - 40, 200, 30 };
        void Update(){
            Draw();
            Move();
        }
    protected:
        void Draw(){
            DrawRectangleRec(rect, RED);
        }
        void Move(){
            Vector2 mousePos = GetMousePosition();
            rect.x = mousePos.x - rect.width/2;

            if (rect.x < 0) rect.x = 0;
            if (rect.x + rect.width > screenWidth) rect.x = screenWidth - rect.width;
        }
};


int main() 
{
    InitWindow(screenWidth, screenHeight, "Brick Braker");
    SetTargetFPS(60);              
    Player player;
    
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