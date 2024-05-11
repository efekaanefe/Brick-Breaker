#pragma once
#include <vector>
#include "block.h"


class Grid{
    public:
        Grid();
        void Update();
        // int numRows, numCols;
        std::vector<std::vector<Block>> grid;

    private:
        void Draw();
        void Initialize();
        void SetBlock(int row, int col, int lifeRemaining, Color color);
        Block GetBlock(int row, int col);
        int GetValue(int row, int col);
        void SetValue(int row, int col, int value);
};