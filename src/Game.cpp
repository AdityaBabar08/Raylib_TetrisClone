#include "Game.h"
#include "Game.h"
#include "Game.h"
#include "Game.h"
#include "Game.h"
#include "Game.h"
#include "Game.h"
#include "Game.h"
#include "Game.h"
#include "Game.h"
#include <random>


Game::Game()
{
	grid = Grid();
	blocks = { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
}

Block Game::GetRandomBlock()
{
	if (blocks.empty())
	{
		blocks = { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
	}

	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return block;
}

void Game::Draw()
{
	grid.DrawGrid();
	currentBlock.DrawBlock();
}

void Game::HandleInput()
{
	int KeyPressed = GetKeyPressed();
	if (gameOver && KeyPressed != 0)
	{
		gameOver = false;
		ResetGame();
	}
	switch (KeyPressed)
	{
	case KEY_LEFT:
		MoveBlockLeft();
		break;
	case KEY_RIGHT:
		MoveBlockRight();
		break;
	case KEY_DOWN:
		MoveBlockDown();
		break;
	case KEY_UP:
		Rotate();
		break;
	}
}

void Game::MoveBlockLeft()
{
	if (!gameOver)
	{
		currentBlock.Move(0, -1);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(0, 1);
		}
	}
	
}

void Game::MoveBlockRight()
{
	if (!gameOver)
	{
		currentBlock.Move(0, 1);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(0, -1);
		}
	}
}

void Game::MoveBlockDown()
{
	if (!gameOver)
	{
		currentBlock.Move(1, 0);
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(-1, 0);
			LockBlock();
		}
	}
}

void Game::Rotate()
{
	if (!gameOver)
	{
		currentBlock.RotateBlock();
		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.UndoRotateBlock();
		}
	}
}

bool Game::IsBlockOutside()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position tile:tiles)
	{
		if (grid.IsCellOutside(tile.row, tile.col))
		{
			return true;
		}
	}
	return false;
}

void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles)
	{
		grid.grid[item.row][item.col] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (BlockFits() == false)
	{
		gameOver = true;
	}

	nextBlock = GetRandomBlock();

	grid.ClearFullRows();
}

bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles)
	{
		if (grid.IsCellEmpty(item.row, item.col) == false)
		{
			return false;
		}
	}
	return true;
}

void Game::ResetGame()
{
	grid.InitializeGrid();
	blocks = { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
}
