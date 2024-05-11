#include "grid.h"
// #include <vector>
#include "constants.h"
#include <random>
#include "block.h"

Grid::Grid()
{
    Initialize();
}

void Grid::Update()
{
    Draw();
}


void Grid::Draw()
{
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            Block block = GetBlock(row, col);
            block.draw();
        }
    }
}


void Grid::Initialize()
{    
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 5); // Generate numbers between 1 and 100

    grid.resize(numRows); // Resize the rows
    for (int row = 0; row < numRows; row++)
        { 
            grid[row].resize(numCols); // Resize each row
            for (int col = 0; col < numCols; col++)
            { 
                Color color;
                int value = GetValue(row, col);
                
                if (value == 0) { color = GRAY; }
                else if (value == 1){ color = PURPLE; }
                else if (value == 2){ color = RED; }
                else if (value == 3){ color = BLUE; }
                else if (value == 4){ color = ORANGE; }
                else if (value == 5){ color = GREEN; }

                SetBlock(row, col, 1, color); 

            }
        }
}

void Grid::SetBlock(int row, int col, int life, Color color)
{   
    Vector2 pos = {};
    grid[row][col] = Block(pos, color, life);
}

Block Grid::GetBlock(int row, int col)
{
    return grid[row][col];
}