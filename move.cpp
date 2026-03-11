#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"raylib.h"
#include"Tetris.h"

void moveSquare(Game* game,int Move)
{
	if (!JudgLocked(game)) {
		if (Move == 0)
		{
			Square temp = game->Now;
			temp.position.y++;
			if (JudgBound(game, temp))
			{
				(game->Now.position.y)++;
			}

		}//ÏÂÂä
		else if (Move == 1)
		{
			Square temp = game->Now;
			temp.position.x++;
			if (JudgBound(game, temp))
			{
				(game->Now.position.x)++;
			}
		}//ÓÒÒÆ
		else if (Move == 2)
		{
			Square temp = game->Now;
			temp.position.x--;
			if (JudgBound(game, temp))
			{
				(game->Now.position.x)--;
			}
		}//×óÒÆ
	}
}


void RoatSquare(Game* game)
{	
	Square temp;
	temp = game->Now;
	temp.rotatingState = (game->Now.rotatingState+1) % 4;
	if (JudgBound(game,temp)&& temp.position.y>-1)
	{
		game->Now = temp;
	}
	else if ((!JudgBound(game, temp)) && temp.position.y > -1)
	{
		HitWall(game, temp);
	}
}

void AutoFall(Game* game)
{
	game->fallTimer++;
	if (game->fallTimer == game->fallInterval)
	{
		moveSquare(game, 0);
		game->fallTimer = 0;
	}
}

void HitWall(Game* game,Square temp)
{
	int** Square = GetSquare(&temp);
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (Square[y][x] != 0)
			{
				int X = temp.position.x + x;
				int Y = temp.position.y + y;
				if (X <= 0)
				{
					HitWallMove(game, 1, temp);
				}
				else if (X >= Game_Width)
				{
					HitWallMove(game, 2, temp);
				}
			}
		}
	}
	FreeSquare(Square);
}

void HitWallMove(Game* game,int CheckNum,Square temp)
{
	if (CheckNum == 1)
	{
		if (temp.type == type_I)
		{
			temp.position.x += 2;
			game->Now = temp;
		}
		else
		{
			game->Now = temp;
			game->Now.position.x ++ ;
		}
	}
	else
	{
		if (temp.type == type_I )
		{
			temp.position.x -= 2;
			game->Now = temp;
		}
		else 
		{
			game->Now = temp;
			game->Now.position.x--;
		}
	}
}