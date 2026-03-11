#pragma once
#ifndef TETRIS_H
#define TETRIS_H

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"raylib.h"


#define Game_Height 20
#define Game_Width 10
#define Square_Size 30
#define Game_area_Height (Game_Height*Square_Size)
#define Game_area_Width (Game_Width*Square_Size)
#define Game_position_X 100
#define Game_position_Y 100

typedef enum
{
	type_I,
	type_O,
	type_T,
	type_L,
	type_J,
	type_S,
	type_Z
}Square_Type;

typedef struct
{
	Square_Type type;
	int rotatingState;
	Vector2 position;
	Color color;
}Square;

typedef enum
{
	Game_Start,
	Game_Pause,
	Game_Over,
	Game_Initialization,
	Setting,
	Select
}gameState;

typedef enum
{
	Easy,
	Normal,
	Hard,
	God
}Difficulty;

typedef struct
{
	int If_Auto_Improve_Difficult;
	int Difficult_UP_Time;
	int Ghost_Cube_Open;
	int voice;
	int sound;
}Set;

typedef struct
{
	gameState state;
	int Grid[Game_Width][Game_Height];
	Square Now;
	Square Next;
	Square Ghost_Cube;
	int Score;
	int Highest_Score;
	int fallTimer;     
	int fallInterval;
	int CleanDelayTime;
	int inputCooldown;
	Difficulty difficulty;
	int CheckDifficultyTime;
	Set set;
}Game;

static const Color color[7] =
{
	SKYBLUE,
	YELLOW,
	PURPLE,
	GREEN,
	RED,
	BLUE,
	ORANGE
};


void Init_Game(Game* game);
Square CreatSquare(Square_Type type);
Square RCreatSquare();
void gameTree(Game* game);
int** GetSquare(const Square* square);
void FreeSquare(int** shape);
void DifficultyUP(Game* game);
void Score(Game* game,int ClearLineCount);

void Input(Game* game);
void moveSquare(Game* game, int Move);
void RoatSquare(Game* game);
void AutoFall(Game* game);
void HitWall(Game* game, Square temp);
void HitWallMove(Game* game, int CheckNum, Square temp);

bool JudgBound(Game* game, Square temp);
bool JudgLocked(Game* game);
bool JudgEnd(Game* game, Sound Failure);
void Check_Improve_Difficulty(Game* game);
void CheckDifficulty(Game* game);
void CheckGameStatus(Game* game, Sound CleanLine, Sound Failure);
void JudgClearLine(Game* game, Sound CleanLine);
void ClearLine(Game* game, int Line);
void JudgGhost(Game* game);

void DrawPausetext();
void DrawNext(Game* game);
void DrawGameUI(Game* game);
void DrawScore(Game* game);
void DrawLocked(const Game* game);
void DrawHint();
void Drawsetting(Game* game);
void DrawDifficulty(Game* game);
void DrawLine();
void DrawNow(Game* game);
void DrawGrid();
void DrawGhost(Game* game);

void SaveScore(Game* game);
void SaveSet(Set* set);
void ReadScore(Game* game);
void ReadSet(Set* set);

void Music_S(Game* game, Music Backmusic);

#endif


