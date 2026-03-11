#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"raylib.h"
#include"Tetris.h"

void Input(Game* game)
{
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
	
		Rectangle StartBut = { Game_position_X + 90, Game_position_Y + 300, 120, 50 };
		Rectangle settingBut = { Game_position_X + 90, Game_position_Y + 400, 120, 50 };
		Rectangle ReturnBut = { Game_position_X , Game_position_Y + 500, 90, 40 };
		Rectangle ResetScoreBut{ Game_position_X + (Game_Width * Square_Size) + 150, Game_position_Y + 540, 30, 30 };

		Rectangle EazyBut= { Game_position_X + 90, Game_position_Y + 260, 120, 50 };
		Rectangle NormalBut = { Game_position_X + 90, Game_position_Y + 340, 120, 50 };
		Rectangle HardBut = { Game_position_X + 90, Game_position_Y + 400, 120, 50 };
		Rectangle GodBut = { Game_position_X + 90, Game_position_Y + 460, 120, 50 };

		Rectangle ExitBut = { Game_position_X + 90, Game_position_Y + 500, 120, 50 };
		Vector2 Mouse = GetMousePosition();

		Rectangle Set_DifficultyUPBut{ Game_position_X + 135 , Game_position_Y + 150, 30, 30 };
		Rectangle Set_UPTimeBut1{ Game_position_X + 30, Game_position_Y + 300, 60, 30 };
		Rectangle Set_UPTimeBut2{ Game_position_X + 120, Game_position_Y + 300, 60, 30 };
		Rectangle Set_UPTimeBut3{ Game_position_X + 210, Game_position_Y + 300, 60, 30 };
		Rectangle Set_VoiceBut{ Game_position_X + 215 , Game_position_Y + 395, 20, 20 };
		Rectangle Set_GhostBut{ Game_position_X + 215 , Game_position_Y + 425, 20, 20 };
		Rectangle Set_ResetBut{ Game_position_X + 180 , Game_position_Y + 480, 80, 40 };
		Rectangle Set_SoundBut{ Game_position_X + 215 , Game_position_Y + 365, 20, 20 };
		
		if (game->inputCooldown != 0)
		{
			game->inputCooldown--;
		}
		else if (game->state == Game_Initialization)
		{
			if (CheckCollisionPointRec(Mouse, StartBut))
			{
				game->state = Select;
				game->inputCooldown += 5;
			}
			else if (CheckCollisionPointRec(Mouse, settingBut))
			{
				game->state = Setting;
				game->inputCooldown += 5;
			}
			else if (CheckCollisionPointRec(Mouse, ExitBut))
			{
				CloseWindow();
				exit(0);
			}
			else if (CheckCollisionPointRec(Mouse, ResetScoreBut))
			{
				game->Highest_Score = 0;
				SaveScore(game);
			}
		}
		else if (game->state == Select)
		{
			if (CheckCollisionPointRec(Mouse, EazyBut))
			{
				game->difficulty = Easy;
				game->state = Game_Start;
			}
			else if (CheckCollisionPointRec(Mouse, NormalBut))
			{
				game->difficulty = Normal;
				game->state = Game_Start;
			}
			else if (CheckCollisionPointRec(Mouse, HardBut))
			{
				game->difficulty = Hard;
				game->state = Game_Start;
			}
			else if (CheckCollisionPointRec(Mouse, GodBut))
			{
				game->difficulty = God;
				game->state = Game_Start;
			}
		}
		else if (game->state == Setting)
		{
			if (CheckCollisionPointRec(Mouse, ReturnBut))
			{
				game->state = Game_Initialization;
				SaveSet(&game->set);
				game->inputCooldown += 5;
			}
			else if (CheckCollisionPointRec(Mouse, Set_DifficultyUPBut))
			{
				if (game->set.If_Auto_Improve_Difficult == 1)
				{
					game->set.If_Auto_Improve_Difficult = 0;
					game->inputCooldown += 5;
				}
				else
				{
					game->set.If_Auto_Improve_Difficult = 1;
					game->inputCooldown += 5;
				}
			}
			else if (CheckCollisionPointRec(Mouse, Set_UPTimeBut1) && game->set.If_Auto_Improve_Difficult == 1)
			{
				game->set.Difficult_UP_Time = 60;
				game->inputCooldown += 5;
			}
			else if (CheckCollisionPointRec(Mouse, Set_UPTimeBut2) && game->set.If_Auto_Improve_Difficult == 1)
			{
				game->set.Difficult_UP_Time = 180;
				game->inputCooldown += 5;
			}
			else if (CheckCollisionPointRec(Mouse, Set_UPTimeBut3) && game->set.If_Auto_Improve_Difficult == 1)
			{
				game->set.Difficult_UP_Time = 300;
				game->inputCooldown += 5;
			}
			else if (CheckCollisionPointRec(Mouse, Set_VoiceBut))
			{
				if (game->set.voice == 1)
				{
					game->set.voice = 0;
					game->inputCooldown += 5;
				}
				else
				{
					game->set.voice = 1;
					game->inputCooldown += 5;
				}
			}
			else if (CheckCollisionPointRec(Mouse, Set_GhostBut))
			{
				if (game->set.Ghost_Cube_Open == 1)
				{
					game->set.Ghost_Cube_Open = 0;
					game->inputCooldown += 5;
				}
				else
				{
					game->set.Ghost_Cube_Open = 1;
					game->inputCooldown += 5;
				}
			}
			else if (CheckCollisionPointRec(Mouse, Set_ResetBut))
			{
				game->set.If_Auto_Improve_Difficult = 1;
				game->set.Difficult_UP_Time = 60;
				game->set.voice = 1;
				game->set.Ghost_Cube_Open = 1;
				game->set.sound = 1;
			}
			else if (CheckCollisionPointRec(Mouse, Set_SoundBut))
			{
				if (game->set.sound == 1)
				{
					game->set.sound = 0;
					game->inputCooldown += 5;
				}
				else
				{
					game->set.sound = 1;
					game->inputCooldown += 5;
				}
			}
		}

	}

	if (IsKeyDown(KEY_P) && game->state == Game_Start)
	{
		game->state = Game_Pause;
	}
	else if (IsKeyDown(KEY_C) && game->state == Game_Pause)
	{
		game->state = Game_Start;
	}
	else if (IsKeyDown(KEY_R) && game->state == Game_Over)
	{
		Init_Game(game);
	}
	if (game->state == Game_Start)
	{
		if (game->inputCooldown != 0)
		{
			game->inputCooldown--;
		}
		else
		{
			if (IsKeyDown(KEY_DOWN))
			{
				moveSquare(game, 0);
				game->inputCooldown += 5;
			}
			else if (IsKeyDown(KEY_RIGHT))
			{
				moveSquare(game, 1);
				game->inputCooldown += 10;
			}
			else if (IsKeyDown(KEY_LEFT))
			{
				moveSquare(game, 2);
				game->inputCooldown += 10;
			}
			else if (IsKeyDown(KEY_UP))
			{
				RoatSquare(game);
				game->inputCooldown += 15;
			}
		}
	}

}