#pragma once
#include "Grid.h"
#include "Blocks.cpp"

class Game
{
public:
	Game();
	Block GetRandomBlock();
	void Draw();
	Grid grid;
	void HandleInput();
	void MoveBlockLeft();
	void MoveBlockRight();
	void MoveBlockDown();
private:
	std::vector<Block> blocks;
	void Rotate();
	Block currentBlock;
	Block nextBlock;
	bool IsBlockOutside();
	void LockBlock();
};
