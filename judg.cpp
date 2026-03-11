#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"raylib.h"
#include"Tetris.h"

bool Locked(Game* game);
void ClearLine(Game* game, int Line);

bool JudgBound(Game* game,Square temp)
{
	int** Square = GetSquare(&temp);
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (Square[y][x]!=0)
			{
				int X = temp.position.x + x;
				int Y = temp.position.y + y;
				if (X < 0 || X >= Game_Width || Y >= Game_Height)
				{
					FreeSquare(Square);
					return 0;
				}
				else if (Y >= 0 && game->Grid[X][Y]!=0)
				{
					FreeSquare(Square);
					return 0;
				}
			}
		}
	}
	FreeSquare(Square);
	return 1;
}

bool JudgLocked(Game* game)
{
	int** shape = GetSquare(&game->Now);
	for (int y = 3; y >= 0; y--)
	{
		for (int x = 0; x < 4; x++)
		{
			if (shape[y][x] != 0)
			{
				int Y = game->Now.position.y + y;
				int X = game->Now.position.x + x;
				if ( Y + 1 >= Game_Height)
				{
					FreeSquare(shape);
					return Locked(game);
				}
				else if (game->Grid[X][Y + 1] != 0 && X >= 0 && X < Game_Width )
				{
					FreeSquare(shape);
					return Locked(game);
				}
			}
		}
	}
	FreeSquare(shape);
	return 0;
}

bool Locked(Game* game)
{
	int** shape = GetSquare(&game->Now);
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0;y < 4; y++)
		{
			if (shape[y][x] != 0)
			{
				int Y = game->Now.position.y + y;
				int X = game->Now.position.x + x;
				game->Grid[X][Y] = game->Now.type+1;
			}
		}
	}
	FreeSquare(shape);
	game->Now = game->Next;
	game->Next = RCreatSquare();
	return 1;
}

bool JudgEnd(Game* game,Sound Failure)
{
	static int End = 0;
	int y = 0;
	for (int x = 0; x < Game_Width; x++)
	{
		if (game->Grid[x][y] != 0)
		{
			if (!End)
			{
				if (game->set.voice == 1)
				{
					PlaySound(Failure);
				}
				SaveScore(game);
				End = 1;
			}
			return 1;
		}
	}
	return 0;
}

void JudgClearLine(Game* game, Sound CleanLine)
{
	int CheckX = 0;
	int ClearLineCount = 0;

	for (int y = 0; y < Game_Height; y++)
	{
		if (game->Grid[CheckX][y] != 0)
		{
			for (int x = 1; x < Game_Width; x++)
			{
				if (game->Grid[x][y] == 0)
				{
					break;
				}
				if (x == Game_Width - 1 && game->Grid[x][y] != 0)
				{
					ClearLine(game, y);
					if (game->set.voice == 1)
					{
						game->CleanDelayTime = 0;
						PlaySound(CleanLine);
					}
					ClearLineCount++;
					y--;
					break;
				}
			}
		}
	}
	if (ClearLineCount > 0)
	{
		Score(game, ClearLineCount);
	}
}

void ClearLine(Game* game,int Line)
{
	for (int y = Line; y > 0; y--)
	{
		for (int x = 0; x < Game_Width; x++)
		{
			game->Grid[x][y] = game->Grid[x][y - 1];
		}
	}
	for (int x = 0; x < Game_Width; x++)
	{
		game->Grid[x][0] = 0;
	}
} 

void Score(Game* game,int ClearLineCount)
{
	int score = 0;
	int ScoreArr[4] = { 100,300,500,800 };
	switch (game->difficulty)
	{
	case 0:
		score = ScoreArr[ClearLineCount-1] * 1;
		break;
	case 1:
		score = ScoreArr[ClearLineCount-1] * 2;
		break;
	case 2:
		score = ScoreArr[ClearLineCount-1] * 3;
		break;
	case 3:
		score = ScoreArr[ClearLineCount-1] * 5;
		break;
	default:
		break;
	}

	game->Score += score;

	if (game->Score >= game->Highest_Score)
	{
		game->Highest_Score = game->Score;
	}
}

void JudgGhost(Game* game)
{
	if (game->set.Ghost_Cube_Open == 0)
	{
		return;
	}
	else
	{
		game->Ghost_Cube = game->Now;
		while (JudgBound(game, game->Ghost_Cube))
		{
			game->Ghost_Cube.position.y++;
		}
		game->Ghost_Cube.position.y--;
	}
}