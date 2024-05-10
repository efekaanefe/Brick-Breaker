#include "grid.h"
// #include <vector>
#include "constants.h"
#include <random>

Grid::Grid()
{
    grid.resize(numRows, std::vector<int>(numCols, 0)); 
    Initialize();
}

void Grid::Update()
{
    Draw();
}


void Grid::Draw()
{
    Color color;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            int value = GetValue(row, col);
            int posX = startX + col * (blockWidth + 1);
            int posY = startY + row * (blockHeight + 1);

            if (value == 0) { color = GRAY; }
            else if (value == 1){ color = PURPLE; }
            else if (value == 2){ color = RED; }
            else if (value == 3){ color = BLUE; }
            else if (value == 4){ color = ORANGE; }
            else if (value == 5){ color = GREEN; }

            DrawRectangle(posX, posY, blockWidth, blockHeight, color);
        }
    }
}


void Grid::Initialize()
{    
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 5); // Generate numbers between 1 and 100

    for (int row = 0; row < numRows; row++)
        { 
            for (int column = 0; column < numCols; column++)
            { 
                SetValue(row, column, dist(gen)); 
            }
        }
}

int Grid::GetValue(int row, int col)
{
    if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
        return grid[row][col];
    }
    return -1;
}

void Grid::SetValue(int row, int col, int value) 
{
    if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
        grid[row][col] = value;
    }    
}