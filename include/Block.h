#pragma once
#include<vector>
#include<map>
#include <raylib.h>
#include "Position.h"

class Block
{
public:
	int id;
	std::map<int, std::vector<Position>> cells;
public:
	Block();
	void DrawBlock();
	void Move(int rows, int columns);
	std::vector<Position> GetCellPositions();
private:
	int cellSize;
	int rotationState;
	int rowOffset;
	int colOffset;


	std::vector<Color> colors;
	std::vector<Color> GetCellColors();
};


