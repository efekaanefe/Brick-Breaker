#pragma once
#include <vector>


class Grid{
    public:
        Grid();
        void Update();
        // int numRows, numCols;
        std::vector<std::vector<int>> grid;

    private:
        void Draw();
        void Initialize();
        int GetValue(int row, int col);
        void SetValue(int row, int col, int value);
};