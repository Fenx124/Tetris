#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"raylib.h"
#include"Tetris.h"


int main()
{
	const int Width=600;
	const int Height = 800;
	InitWindow(Width, Height, "Tetris");
	SetTargetFPS(60);
	Game game;
	Init_Game(&game);
	Texture2D Back = LoadTexture("Resources/1.png");
	InitAudioDevice();
	Music Backmusic = LoadMusicStream("Resources/tetris.mp3");
	Sound CleanLine = LoadSound("Resources/tetris_s.mp3");
	Sound Failure = LoadSound("Resources/tetris_f.mp3");
	PlayMusicStream(Backmusic);
	while (!WindowShouldClose())
	{
		Input(&game);
		Music_S(&game, Backmusic);
		CheckGameStatus(&game,CleanLine,Failure);
		UpdateMusicStream(Backmusic);
		BeginDrawing();
		DrawTexture(Back, 0, 0, WHITE);
		gameTree(&game);
		EndDrawing();
	}
	UnloadMusicStream(Backmusic);
	CloseAudioDevice();
	CloseWindow();

	return 0;
}