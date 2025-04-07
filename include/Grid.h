#pragma once
#include <vector>
#include <raylib.h>


class Grid
{
public:
	Grid();
	~Grid();
	void DrawGrid();

	void InitializeGrid();
	void PrintGrid();
	int grid[20][10];
	bool IsCellOutside(int row, int column);
	bool IsCellEmpty(int row, int column);

private:
	std::vector<Color> GetCellColors();
	int rows = 0;
	int columns = 0;
	int cellSize = 0;
	std::vector<Color> colors;
};
