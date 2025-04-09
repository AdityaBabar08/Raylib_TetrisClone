#include "Game.h"
#include <random>


Game::Game()
{
	grid = Grid();
	blocks = { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
	score = 0;

	InitAudioDevice();
	music = LoadMusicStream(RESOURCES_PATH "Sounds/music.mp3");
	PlayMusicStream(music);
	rotateSound = LoadSound(RESOURCES_PATH "Sounds/rotate.mp3");
	clearSound = LoadSound(RESOURCES_PATH "Sounds/clear.mp3");
}

Game::~Game()
{
	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
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
	currentBlock.DrawBlock(10, 10);
	switch (nextBlock.id)
	{
	case 3:
		nextBlock.DrawBlock(255, 290);
		break;
	case 4:
		nextBlock.DrawBlock(255, 280);
		break;
	default:
		nextBlock.DrawBlock(270, 270);
		break;
	}
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
		UpdateScore(0, 1);
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
		else
			PlaySound(rotateSound);
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

	int rowsCleared = grid.ClearFullRows();
	if (rowsCleared > 0)
	{
		UpdateScore(rowsCleared, 0);
		PlaySound(clearSound);
	}
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
	score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
	switch (linesCleared)
	{
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;
	default:
		break;
	}

	score += moveDownPoints;
}
