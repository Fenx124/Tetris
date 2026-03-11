#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"raylib.h"
#include"Tetris.h"

void DrawGrid()
{
	DrawRectangle(Game_position_X, Game_position_Y,Game_Width * Square_Size, Game_Height * Square_Size,Color {242, 236, 204, 255});
	for (int x = 0; x <= Game_Width; x++)
	{
		int lineX = Game_position_X + x * Square_Size;
		DrawLine(lineX, Game_position_Y, lineX, Game_position_Y + Game_Height * Square_Size, Color{ 200, 200, 200, 255 });
	}
	for (int y = 0; y <= Game_Height; y++)
	{
		int lineY = Game_position_Y + y * Square_Size;
		DrawLine(Game_position_X, lineY, Game_position_X + Game_Width * Square_Size, lineY, Color{ 200, 200, 200, 255 });
	}
}

void DrawGhost(Game* game)
{
	int** shape = GetSquare(&game->Ghost_Cube);
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (shape[y][x] != 0)
			{
				int ScreenX = Game_position_X + (game->Ghost_Cube.position.x + x) * Square_Size;
				int ScreenY = Game_position_Y + (game->Ghost_Cube.position.y + y) * Square_Size;
				Color ghostColor = game->Ghost_Cube.color;
				ghostColor.a = 100; 
				DrawRectangle(ScreenX, ScreenY, Square_Size, Square_Size, ghostColor);
				Color borderColor = WHITE;
				borderColor.a = 150;
				DrawRectangleLines(ScreenX, ScreenY, Square_Size, Square_Size, borderColor);
			}
		}
	}
	FreeSquare(shape);
}

void DrawNow(Game* game)
{
	int** shape = GetSquare(&game->Now);
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (shape[y][x] != 0)
			{
				int ScreenX = Game_position_X + (game->Now.position.x + x) * Square_Size;
				int ScreenY = Game_position_Y + (game->Now.position.y + y) * Square_Size;
				DrawRectangle(ScreenX, ScreenY, Square_Size, Square_Size, game->Now.color);
				DrawRectangleLines(ScreenX, ScreenY, Square_Size, Square_Size, WHITE);
				DrawLine(ScreenX + 15, ScreenY + 25, ScreenX + 25, ScreenY + 25, Color{ 227,227,227,255 });
				DrawLine(ScreenX + 25, ScreenY + 15, ScreenX + 25, ScreenY + 25, Color{ 227,227,227,255 });
			}
		}
	}
	FreeSquare(shape);
}

void DrawNext(Game* game)
{
	int** shape = GetSquare(&game->Next);
	DrawRectangle(Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 60, 4 * Square_Size, 4 * Square_Size, Color{ 242, 236, 204, 255 });
	for (int x = 0; x <= 4; x++)
	{
		int lineX = Game_position_X + x * Square_Size + (Game_Width * Square_Size) + 30;
		DrawLine(lineX, Game_position_Y + 60, lineX, Game_position_Y + 180, Color{ 200, 200, 200, 255 });
	}
	for (int y = 0; y <= 4; y++)
	{
		int lineY = Game_position_Y + y * Square_Size + 60;
		DrawLine(Game_position_X + (Game_Width * Square_Size) + 30, lineY, Game_position_X + (Game_Width * Square_Size) + 150, lineY, Color{ 200, 200, 200, 255 });
	}
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (shape[y][x] != 0)
			{
				int ScreenX = Game_position_X + Game_Width * Square_Size + x * Square_Size + 30;
				int ScreenY = Game_position_Y  +y * Square_Size + 60;
				DrawRectangle(ScreenX, ScreenY, Square_Size, Square_Size, game->Next.color);
				DrawRectangleLines(ScreenX, ScreenY, Square_Size, Square_Size, WHITE);
				DrawLine(ScreenX + 15, ScreenY + 25, ScreenX + 25, ScreenY + 25, Color{ 227,227,227,255 });
				DrawLine(ScreenX + 25, ScreenY + 15, ScreenX + 25, ScreenY + 25, Color{ 227,227,227,255 });
			}
		}
	}
	FreeSquare(shape);
}

void DrawLocked(const Game* game)
{
	for (int x = 0; x < Game_Width; x++)
	{
		for (int y = 0; y < Game_Height; y++)
		{
			if (game->Grid[x][y] != 0)
			{
				int ScreenX = Game_position_X + x * Square_Size;
				int ScreenY = Game_position_Y + y * Square_Size;
				DrawRectangle(ScreenX, ScreenY, Square_Size, Square_Size,color[game->Grid[x][y]-1]);
				DrawRectangleLines(ScreenX, ScreenY, Square_Size, Square_Size, WHITE);
				DrawLine(ScreenX + 15, ScreenY + 25, ScreenX + 25, ScreenY + 25, Color{ 227,227,227,255 });
				DrawLine(ScreenX + 25, ScreenY + 15, ScreenX + 25, ScreenY + 25, Color{ 227,227,227,255 });
			}
		}
	}
}

void DrawLine()
{
	DrawRectangle(Game_position_X - 5, Game_position_Y - 5,Game_Width * Square_Size + 10, Game_Height * Square_Size + 10,Color{255, 255, 255, 255});
}

void DrawPausetext()
{
	int X = Game_position_X;
	int Y = Game_position_Y + (Game_Height * Square_Size) / 2-50;
	DrawText("Game Pause", X, Y, 50, BLUE);
	DrawText("Press 'c' to Continue", X+20, Y + 50, 25 ,BLUE);
}

void DrawGameUI(Game* game)
{
	if (game->state == Game_Start || game->state == Game_Pause)
	{
		DrawText("Tetris", 165, 30, 50, Color{ 240,135 ,132 ,255 });
		DrawText("Next:",Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 30,30, ORANGE);
		DrawNext(game);
		DrawScore(game);
		DrawHint();
		DrawDifficulty(game);
		if (game->state == Game_Pause)
		{
			DrawRectangle(Game_position_X, Game_position_Y + 240, Game_Width * Square_Size, 120, Color{ 175 ,230 ,252 ,255 });
		}
	}
	else if (game->state == Game_Initialization)
	{
		DrawText("Tetris", Game_position_X + 65, Game_position_Y + 100, 50, BLUE);

		DrawRectangle(Game_position_X + 90, Game_position_Y + 300, 120, 50, Color{ 175 ,230 ,252 ,255 });
		DrawRectangleLinesEx(Rectangle{ Game_position_X + 90, Game_position_Y + 300, 120, 50 }, 5, Color{ 72 ,193 ,252 ,255 });
		DrawText("Start", Game_position_X + 110, Game_position_Y + 310, 30, BLUE);

		DrawRectangle(Game_position_X + 90, Game_position_Y + 400, 120, 50, Color{ 175 ,230 ,252 ,255 });
		DrawRectangleLinesEx(Rectangle{ Game_position_X + 90, Game_position_Y + 400, 120, 50 }, 5, Color{ 72 ,193 ,252 ,255 });
		DrawText("Setting", Game_position_X + 108, Game_position_Y + 410, 25, BLUE);

		DrawRectangle(Game_position_X + 90, Game_position_Y + 500, 120, 50, Color{ 175 ,230 ,252 ,255 });
		DrawRectangleLinesEx(Rectangle{ Game_position_X + 90, Game_position_Y + 500, 120, 50 }, 5, Color{ 72 ,193 ,252 ,255 });
		DrawText("Exit", Game_position_X + 120, Game_position_Y + 510, 30, BLUE);

		DrawScore(game);
		DrawHint();
	}
	else if (game->state == Setting)
	{
		DrawRectangle(Game_position_X , Game_position_Y + 500, 90, 40, Color{ 175 ,230 ,252 ,255 });
		DrawRectangleLinesEx(Rectangle{ Game_position_X , Game_position_Y + 500, 90, 40 }, 5, Color{ 72 ,193 ,252 ,255 });
		DrawText("Return", Game_position_X + 10, Game_position_Y + 510, 20, BLUE);

		DrawRectangle(Game_position_X+180, Game_position_Y + 480, 80, 40, Color{ 175 ,230 ,252 ,255 });
		DrawRectangleLinesEx(Rectangle{ Game_position_X+180 , Game_position_Y + 480, 80, 40 }, 5, Color{ 72 ,193 ,252 ,255 });
		DrawText("Reset", Game_position_X + 190, Game_position_Y + 490, 20, BLUE);
		Drawsetting(game);
	}
	else if (game->state == Game_Over)
	{
		int X = Game_position_X+27;
		int Y = Game_position_Y + (Game_Height * Square_Size) / 2 - 50;
		DrawRectangle(Game_position_X , Game_position_Y + 240, Game_Width*Square_Size, 150, Color{ 175 ,230 ,252 ,255 });
		DrawText("Tetris", 165, 30, 50, Color{ 240,135 ,132 ,255 });
		DrawText("Next:", Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 30, 30, ORANGE);
		DrawNext(game);
		DrawScore(game);
		DrawHint();
		DrawText("Game Over", X, Y, 50, RED);
		DrawText(TextFormat("Your Score: %d",game->Score), X+15, Y + 60, 25, RED);
		DrawText("Press 'r' to Return", X + 12, Y + 100, 25, RED);
		DrawDifficulty(game);
	}
	else if (game->state == Select)
	{
		DrawText("Tetris", Game_position_X + 65, Game_position_Y + 100, 50, BLUE);

		DrawRectangle(Game_position_X + 90, Game_position_Y + 260, 120, 50, Color{ 175 ,230 ,252 ,255 });
		DrawRectangleLinesEx(Rectangle{ Game_position_X + 90, Game_position_Y + 260, 120, 50 }, 5, Color{ 72 ,193 ,252 ,255 });
		DrawText("Easy", Game_position_X + 115, Game_position_Y + 270, 30, GREEN);

		DrawRectangle(Game_position_X + 90, Game_position_Y + 330, 120, 50, Color{ 175 ,230 ,252 ,255 });
		DrawRectangleLinesEx(Rectangle{ Game_position_X + 90, Game_position_Y + 330, 120, 50 }, 5, Color{ 72 ,193 ,252 ,255 });
		DrawText("Normal", Game_position_X + 110, Game_position_Y + 340, 25, ORANGE);

		DrawRectangle(Game_position_X + 90, Game_position_Y + 400, 120, 50, Color{ 175 ,230 ,252 ,255 });
		DrawRectangleLinesEx(Rectangle{ Game_position_X + 90, Game_position_Y + 400, 120, 50 }, 5, Color{ 72 ,193 ,252 ,255 });
		DrawText("Hard", Game_position_X + 115, Game_position_Y + 410, 30, RED);

		DrawRectangle(Game_position_X + 90, Game_position_Y + 470, 120, 50, Color{ 175 ,230 ,252 ,255 });
		DrawRectangleLinesEx(Rectangle{ Game_position_X + 90, Game_position_Y + 470, 120, 50 }, 5, Color{ 72 ,193 ,252 ,255 });
		DrawText("God", Game_position_X + 123, Game_position_Y + 480, 30, PURPLE);

		DrawScore(game);
		DrawHint();
	}
}

void DrawScore(Game* game)
{
	DrawText("Now Score", Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 450, 25, ORANGE);
	DrawRectangle(Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 480, 120, 30, WHITE);
	DrawRectangleLinesEx(Rectangle{ Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 480, 120, 30 }, 3, Color{ 180,180,180,255 });
	DrawText(TextFormat("%d", game->Score), Game_position_X + (Game_Width * Square_Size) + 70, Game_position_Y + 482, 30, BLUE);

	DrawText("Highest Score", Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 520, 20, ORANGE);
	DrawRectangle(Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 540, 120, 30, WHITE);
	DrawRectangleLinesEx(Rectangle{ Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 540, 120, 30 }, 3, Color{ 180,180,180,255 });
	DrawText(TextFormat("%d", game->Highest_Score), Game_position_X + (Game_Width * Square_Size) + 70, Game_position_Y + 542, 30, BLUE);

	DrawRectangle(Game_position_X + (Game_Width * Square_Size) + 150, Game_position_Y + 540, 30, 30, Color{ 175 ,230 ,252 ,255 });
	DrawRectangleLinesEx(Rectangle{ Game_position_X + (Game_Width * Square_Size) + 150, Game_position_Y + 540, 30, 30 }, 3, Color{ 72 ,193 ,252 ,255 });
	DrawText(TextFormat("R"), Game_position_X + (Game_Width * Square_Size) + 155, Game_position_Y + 542, 30, BLUE);
}

void DrawHint()
{
	DrawText(TextFormat("UP:Rotate"), Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 210, 25, ORANGE);
	DrawText(TextFormat("Down:Fall"), Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 240, 25, ORANGE);
	DrawText(TextFormat("Lift/Right:Move"), Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 270, 20, ORANGE);
	DrawText(TextFormat("P:Pause"), Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 300, 25, ORANGE);
}

void Drawsetting(Game* game)
{
	DrawRectangle(Game_position_X, Game_position_Y + 60, 300, 60, Color{ 175 ,230 ,252 ,255 });
	DrawText("Difficulty increased", Game_position_X, Game_position_Y + 75, 30, BLUE);
	if (game->set.If_Auto_Improve_Difficult == 1)
	{
		DrawRectangle(Game_position_X + 135, Game_position_Y + 150, 30, 30, Color{ 50 ,130 ,246 ,255 });
	}
	else
	{
		DrawRectangle(Game_position_X + 135, Game_position_Y + 150, 30, 30, WHITE);
	}
	DrawRectangleLinesEx(Rectangle{ Game_position_X + 135 , Game_position_Y + 150, 30, 30 }, 5, BLACK);


	if (game->set.If_Auto_Improve_Difficult == 0)
	{
		DrawRectangle(Game_position_X, Game_position_Y + 210, 300, 60, Color{ 24 ,63 ,120 ,255 });
		DrawRectangle(Game_position_X + 30, Game_position_Y + 300, 60, 30, Color{ 24 ,63 ,120 ,255 });
		DrawRectangle(Game_position_X + 120, Game_position_Y + 300, 60, 30, Color{ 24 ,63 ,120 ,255 });
		DrawRectangle(Game_position_X + 210, Game_position_Y + 300, 60, 30, Color{ 24 ,63 ,120 ,255 });
		DrawText("Time Interval", Game_position_X + 45, Game_position_Y + 225, 30, BLUE);
		DrawText("1 min", Game_position_X + 37, Game_position_Y + 305, 25, BLUE);
		DrawText("3 min", Game_position_X + 125, Game_position_Y + 305, 23, BLUE);
		DrawText("5 min", Game_position_X + 215, Game_position_Y + 305, 23, BLUE);
	}
	else
	{
		DrawRectangle(Game_position_X, Game_position_Y + 210, 300, 60, Color{ 175 ,230 ,252 ,255 });
		DrawRectangle(Game_position_X + 30, Game_position_Y + 300, 60, 30, Color{ 175 ,230 ,252 ,255 });
		DrawRectangle(Game_position_X + 120, Game_position_Y + 300, 60, 30, Color{ 175 ,230 ,252 ,255 });
		DrawRectangle(Game_position_X + 210, Game_position_Y + 300, 60, 30, Color{ 175 ,230 ,252 ,255 });
		DrawText("Time Interval", Game_position_X + 45, Game_position_Y + 225, 30, BLUE);
		DrawText("1 min", Game_position_X + 37, Game_position_Y + 305, 23, BLUE);
		DrawText("3 min", Game_position_X + 125, Game_position_Y + 305, 23, BLUE);
		DrawText("5 min", Game_position_X + 215, Game_position_Y + 305, 23, BLUE);
	}
	

	if (game->set.Difficult_UP_Time == 60 && game->set.If_Auto_Improve_Difficult == 1)
	{
		DrawRectangleLinesEx(Rectangle{ Game_position_X + 30, Game_position_Y + 300, 60, 30 }, 5, Color{ 65,217,207,255 });
	}
	else if (game->set.Difficult_UP_Time == 180 && game->set.If_Auto_Improve_Difficult == 1)
	{
		DrawRectangleLinesEx(Rectangle{ Game_position_X + 120, Game_position_Y + 300, 60, 30 }, 5, Color{ 65,217,207,255 });
	}
	else if (game->set.Difficult_UP_Time == 300 && game->set.If_Auto_Improve_Difficult == 1)
	{
		DrawRectangleLinesEx(Rectangle{ Game_position_X + 210, Game_position_Y + 300, 60, 30 }, 5, Color{ 65,217,207,255 });
	}
	
	DrawText("Voice", Game_position_X + 45, Game_position_Y + 395, 30, BLUE);
	if (game->set.voice == 1)
	{
		DrawRectangle(Game_position_X + 215, Game_position_Y + 395, 20, 20, Color{ 50 ,130 ,246 ,255 });
	}
	else
	{
		DrawRectangle(Game_position_X + 215, Game_position_Y + 395, 20, 20, WHITE);
	}
	DrawRectangleLinesEx(Rectangle{ Game_position_X + 215 , Game_position_Y + 395, 20, 20 }, 5, BLACK);

	DrawText("Ghost", Game_position_X + 45, Game_position_Y + 425, 30, BLUE);
	if (game->set.Ghost_Cube_Open == 1)
	{
		DrawRectangle(Game_position_X + 215, Game_position_Y + 425, 20, 20, Color{ 50 ,130 ,246 ,255 });
	}
	else
	{
		DrawRectangle(Game_position_X + 215, Game_position_Y + 425, 20, 20, WHITE);
	}
	DrawRectangleLinesEx(Rectangle{ Game_position_X + 215 , Game_position_Y + 425, 20, 20 }, 5, BLACK);

	DrawText("Sound", Game_position_X + 45, Game_position_Y + 365, 30, BLUE);
	if (game->set.sound == 1)
	{
		DrawRectangle(Game_position_X + 215, Game_position_Y + 365, 20, 20, Color{ 50 ,130 ,246 ,255 });
	}
	else
	{
		DrawRectangle(Game_position_X + 215, Game_position_Y + 365, 20, 20, WHITE);
	}
	DrawRectangleLinesEx(Rectangle{ Game_position_X + 215 , Game_position_Y + 365, 20, 20 }, 5, BLACK);
}

void DrawDifficulty(Game* game)
{
	DrawText("Now Difficulty", Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 360, 20, ORANGE);
	DrawRectangle(Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 390, 120, 30, WHITE);
	DrawRectangleLinesEx(Rectangle{ Game_position_X + (Game_Width * Square_Size) + 30, Game_position_Y + 390, 120, 30 }, 3, Color{ 180,180,180,255 });
	if (game->difficulty == Easy)
	{
		DrawText(TextFormat("Eazy"), Game_position_X + (Game_Width * Square_Size) + 60, Game_position_Y + 392, 25, GREEN);
	}
	else if (game->difficulty == Normal)
	{
		DrawText(TextFormat("Normal"), Game_position_X + (Game_Width * Square_Size) + 50, Game_position_Y + 392, 25, ORANGE);
	}
	else if (game->difficulty == Hard)
	{
		DrawText(TextFormat("Hard"), Game_position_X + (Game_Width * Square_Size) + 60, Game_position_Y + 392, 25, RED);
	}
	else if (game->difficulty == God)
	{
		DrawText(TextFormat("God"), Game_position_X + (Game_Width * Square_Size) + 70, Game_position_Y + 392, 25, PURPLE);
	}
}
