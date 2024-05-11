#include "grid.h"
// #include <vector>
#include "constants.h"
#include "block.h"
#include <random>


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
            block.Draw();
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
    pos.x = startX + col*(blockWidth + 1);
    pos.y = startY + row*(blockHeight + 1);

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 5); // Generate numbers between 1 and 100

    Color color;
    int value = dist(gen);
    
    if (value == 0) { color = GRAY; }
    else if (value == 1){ color = PURPLE; }
    else if (value == 2){ color = RED; }
    else if (value == 3){ color = BLUE; }
    else if (value == 4){ color = ORANGE; }
    else if (value == 5){ color = GREEN; }

    int life  = 1;
    grid[row][col] = Block(pos, color, life);
}

Block Grid::GetBlock(int row, int col)
{
    return grid[row][col];
}