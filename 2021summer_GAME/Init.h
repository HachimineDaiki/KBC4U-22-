#pragma once
#include <DxLib.h>
#include "Time.h"
#include <stdio.h>
#include"Goal.h"
void Sph_init();
void Model_init();
void Obj_init();
void Decelearia_init();
void Damege_Init();
void All_Init();
int Fail_Read_Init();//ファイル読み込み　初期化
void PlanetInit();
struct FileData
{
	char str[256];
	int filehandle;
};

extern FileData f_damege_aria;
extern float merikomi;
extern int CheckKey;
extern int gameMode;

//extern enum GAMEMODE;//ゲームモード