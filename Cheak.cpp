#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"raylib.h"
#include"Tetris.h"

void CheckGameStatus(Game* game,Sound CleanLine,Sound Failure)
{
	if (game->state == Game_Start)
	{
		if (game->CleanDelayTime != 30)
		{
			game->CleanDelayTime++;
		}
		else
		{
			JudgClearLine(game, CleanLine);
			Check_Improve_Difficulty(game);
			CheckDifficulty(game);
			JudgGhost(game);
			AutoFall(game);
		}
	}


	if (JudgEnd(game,Failure))
	{
		game->state = Game_Over;
	}
}

void CheckDifficulty(Game* game)
{
	if (game->difficulty == Easy)
	{
		game->fallInterval = 30;
	}
	else if (game->difficulty == Normal)
	{
		game->fallInterval = 25;
	}
	else if (game->difficulty == Hard)
	{
		game->fallInterval = 20;
	}
	else if (game->difficulty == God)
	{
		game->fallInterval = 10;
	}
}

void Check_Improve_Difficulty(Game* game)
{
	if (game->set.If_Auto_Improve_Difficult == 1 && game->difficulty != Hard)
	{
		game->CheckDifficultyTime++;
		if (game->CheckDifficultyTime == game->set.Difficult_UP_Time * 60)
		{
			DifficultyUP(game);
			game->fallTimer = 0;
			game->CheckDifficultyTime = 0;
		}
	}
}

void DifficultyUP(Game* game)
{
	if (game->difficulty == Easy)
	{
		game->difficulty = Normal;
	}
	else if(game->difficulty == Normal)
	{
		game->difficulty = Hard;
	}
}