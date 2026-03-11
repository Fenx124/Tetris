#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"raylib.h"
#include"Tetris.h"

void SaveScore(Game* game)
{
	FILE* fp;
	if ((fp = fopen("Save\\SaveScore.txt", "wb")) == NULL)
	{
		printf("文件打开错误");
	}
	fwrite(&game->Highest_Score, sizeof(game->Highest_Score), 1, fp);
	fclose(fp);
}

void SaveSet(Set* set)
{
	FILE* fp;
	if ((fp = fopen("Save\\SaveSet.txt", "wb")) == NULL)
	{
		printf("文件打开错误");
	}
	fwrite(set, sizeof(Set), 1, fp);
	fclose(fp);
}

void ReadScore(Game* game)
{
	FILE* fp;
	if ((fp = fopen("Save\\SaveScore.txt", "rb")) == NULL)
	{
		CloseWindow();
		printf("文件打开错误");
		system("pause");
		exit(0);
	}
	if (fread(&game->Highest_Score, sizeof(game->Highest_Score), 1, fp) != 1)
	{
		printf("文件读取失败");
	}
	fclose(fp);
}

void ReadSet(Set* set)
{
	FILE* fp;
	if ((fp = fopen("Save\\SaveSet.txt", "rb")) == NULL)
	{
		printf("文件打开错误");
	}
	if (fread(set, sizeof(Set), 1, fp) != 1)
	{
		printf("设置文件读取失败");
	}
	fclose(fp);
}
