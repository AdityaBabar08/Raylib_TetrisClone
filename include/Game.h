#pragma once
#include <raylib.h>
#include "Grid.h"
#include "Blocks.cpp"

class Game
{
public:
	Game();
	~Game();
	Block GetRandomBlock();
	void Draw();
	Grid grid;
	void HandleInput();
	void MoveBlockLeft();
	void MoveBlockRight();
	void MoveBlockDown();
	bool gameOver;
	int score;
	Music music;
private:
	std::vector<Block> blocks;
	void Rotate();
	Block currentBlock;
	Block nextBlock;
	bool IsBlockOutside();
	void LockBlock();
	bool BlockFits();
	void ResetGame();
	void UpdateScore(int linesCleared, int moveDownPoints);
	Sound rotateSound;
	Sound clearSound;
};
