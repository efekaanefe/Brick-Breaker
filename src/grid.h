#pragma once
#include <vector>
#include "block.h"


class Grid{
    public:
        Grid();
        void Update();
        Block GetBlock(int row, int col);
        // int numRows, numCols;
        std::vector<std::vector<Block>> grid;

    private:
        void Draw();
        void Initialize();
        void SetRandomBlock(int row, int col);
        void SetValue(int row, int col, int value);
};