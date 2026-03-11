#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"raylib.h"
#include"Tetris.h"

Square RCreatSquare();
Square CreatSquare(Square_Type type);

static const int SquareType[7][4][4] = {
	{
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0},
		{0,0,0,0}
	},//I形
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	},//O形
	{
		{0,0,0,0},
		{0,1,1,1},
		{0,0,1,0},
		{0,0,0,0}
	},//T形
	{
		{0,0,0,0},
		{0,1,1,1},
		{0,1,0,0},
		{0,0,0,0}
	},//L形
	{
		{0,0,0,0},
		{0,1,1,1},
		{0,0,0,1},
		{0,0,0,0}
	},//J形
	{
		{0,0,0,0},
		{0,0,1,1},
		{0,1,1,0},
		{0,0,0,0}
	},//S形
	{
		{0,0,0,0},
		{0,1,1,0},
		{0,0,1,1},
		{0,0,0,0}
	}//Z形
};

Square RCreatSquare()
{
	static bool initialized = false;
	if (!initialized)
	{
		srand((unsigned)time(NULL));
		initialized = true;
	}
	int num = rand() % 7;
	return CreatSquare((Square_Type)num);
}

Square CreatSquare(Square_Type type)
{ 
	Square square;
	square.color = color[type];
	square.rotatingState = 0;
	square.position = Vector2{ Game_Width / 2 - 2, -1 };
	square.type = type;
	return square;
}

int** GetSquare(const Square* square)
{
	int** shape = (int**)malloc(4 * sizeof(int*));
	for (int i = 0; i < 4; i++)
	{
		shape[i] = (int*)malloc(4 * sizeof(int));
	}
	switch (square->rotatingState)
	{
	case 0:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				shape[i][j] = SquareType[square->type][i][j];
			}
		}
		break;
	case 1:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				shape[i][j] = SquareType[square->type][3 - j][i];
			}
		}
		break;
	case 2:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				shape[i][j] = SquareType[square->type][3 - i][3 - j];
			}
		}
		break;
	case 3:
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				shape[i][j] = SquareType[square->type][j][3 - i];
			}
		}
		break;
	default:
		break;
	}
	return shape;
}

void FreeSquare(int** shape)
{
	for (int i = 0; i < 4; i++)
	{
		free(shape[i]);
	}
	free(shape);
}
