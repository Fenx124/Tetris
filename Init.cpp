#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"raylib.h"
#include"Tetris.h"


void Init_Game(Game* game)
{
	for (int y = 0; y < Game_Height; y++)
	{
		for (int x = 0; x < Game_Width; x++)
		{
			game->Grid[x][y] = 0;
		}
	}//ÇåÀíÍø¸ñ

	game->Now = RCreatSquare();
	game->Next = RCreatSquare();

	game->Ghost_Cube = game->Now;

	game->Score = 0;
	game->state = Game_Initialization;
	game->Highest_Score = 0;
	ReadScore(game);

	game->fallTimer = 0;
	game->fallInterval = 30;
	game->inputCooldown = 0;
	game->CleanDelayTime = 0;

	game->difficulty = Easy;

	game->set.If_Auto_Improve_Difficult = 1;
	game->set.Difficult_UP_Time = 60;
	game->set.voice = 1;
	game->set.Ghost_Cube_Open = 1;
	game->set.sound = 1;
	ReadSet(&game->set);

	game->CheckDifficultyTime = 0;
}

