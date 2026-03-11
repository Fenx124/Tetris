#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"raylib.h"
#include"Tetris.h"

void gameTree(Game* game)
{
	if (game->state == Game_Initialization)
	{
		DrawLine();

		DrawGrid();

		DrawGameUI(game);
	}
	else if (game->state == Game_Start)
	{
		DrawLine();

		DrawGrid();

		DrawLocked(game);

		DrawGameUI(game);

		DrawNow(game);

		if (game->set.Ghost_Cube_Open == 1)
		{
			DrawGhost(game);
		}
	}
	else if (game->state == Game_Over)
	{
		DrawLine();

		DrawGrid();

		DrawLocked(game);

		DrawGameUI(game);
	}
	else if (game->state == Game_Pause)
	{
		DrawLine();

		DrawGrid();

		DrawLocked(game);

		DrawNow(game);

		DrawGameUI(game);

		DrawPausetext();

		if (game->set.Ghost_Cube_Open == 1)
		{
			DrawGhost(game);
		}
	}
	else if (game->state == Setting)
	{
		DrawLine();

		DrawGrid();

		DrawGameUI(game);
	}
	else if (game->state == Select)
	{
		DrawLine();

		DrawGrid();

		DrawGameUI(game);
	}
}

void Music_S(Game* game,Music Backmusic)
{
	if (game->set.sound != 1 || (game->state != Game_Start && game->state != Game_Pause))
	{
		PauseMusicStream(Backmusic);
	}
	else
	{
		ResumeMusicStream(Backmusic);
	}

}
