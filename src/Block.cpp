#include "Block.h"
#include <raylib.h>


Block::Block()
{
	cellSize = 30;
	rotationState = 0;
	colors = GetCellColors();
	rowOffset = 0;
	colOffset = 0;
}

void Block::DrawBlock()
{
	std::vector<Position> tiles = GetCellPositions();
	for (Position tile : tiles)
	{
		DrawRectangle(tile.col * cellSize, tile.row * cellSize, cellSize - 1, cellSize - 1, colors[id]);
	}
}

void Block::Move(int rows, int columns)
{
	rowOffset += rows;
	colOffset += columns;
}

std::vector<Position> Block::GetCellPositions()
{
	std::vector<Position> tiles = cells[rotationState];
	std::vector<Position> movedTiles;
	for (Position item : tiles)
	{
		Position newPos = Position(item.row + rowOffset, item.col + colOffset);
		movedTiles.push_back(newPos);
	}
	return movedTiles;
}

std::vector<Color> Block::GetCellColors()
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