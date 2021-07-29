#pragma once
#include <DxLib.h>
#define DECELEARIA_NUM 100
//構造体宣言
struct Sph
{
	float radius;
	float speed;
	float v0y;
	int color;
	VECTOR pos;
	VECTOR v;
	float dis;
	float radius_sum;
	float zaccl; //Z軸加速
	float zmove; //Z軸動く
	float control;
};

void Sph_init();
void Model_init();
void Obj_init();
void Decelearia_init();
//オブジェクト生成
extern Sph sph[2];//プレイヤー
extern Sph obj;//不法投棄物
extern Sph decelearia[DECELEARIA_NUM]; //減速エリア

extern float merikomi;

extern int gameMode;

//extern enum GAMEMODE;//ゲームモード