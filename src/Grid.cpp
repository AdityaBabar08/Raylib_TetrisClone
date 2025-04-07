#include "Grid.h"
#include "Grid.h"
#include "Grid.h"
#include <iostream>


Grid::Grid()
{
	rows = 20;
	columns = 10;
	cellSize = 30;

	InitializeGrid();
	colors = GetCellColors();
}

void Grid::InitializeGrid()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			grid[i][j] = 0;
		}
	}
}

void Grid::PrintGrid()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

bool Grid::IsCellOutside(int row, int column)
{
	if (row >= 0 && row < rows && column >= 0 && column < columns)
	{
		return false;
	}
	return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
	if (grid[row][column] == 0)
	{
		return true;
	}
	return false;
}

std::vector<Color> Grid::GetCellColors()
{
	Color darkGrey = { 26, 31, 40, 255 };
	Color green = { 47, 230, 23, 255 };
	Color red = { 232, 18, 18, 255 };
	Color orange = { 226, 116, 17, 255 };
	Color yellow = { 237, 234, 4, 255 };
	Color purple = { 166, 0, 247, 255 };
	Color cyan = { 21, 204, 209, 255 };
	Color blue = { 13, 64, 216, 255 };

	return { darkGrey, green, red, orange, yellow, purple, cyan, blue };
}

void Grid::DrawGrid()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			int cellValue = grid[i][j];
			DrawRectangle(j * cellSize + 1, i * cellSize + 1, cellSize - 1, cellSize - 1, colors[cellValue]);
		}
	}
}

Grid::~Grid()
{


}