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
	void DrawBlock(int offsetX, int offsetY);
	void Move(int rows, int columns);
	std::vector<Position> GetCellPositions();
	void RotateBlock();
	void UndoRotateBlock();
private:
	int cellSize;
	int rotationState;
	int rowOffset;
	int colOffset;


	std::vector<Color> colors;
	std::vector<Color> GetCellColors();
};


