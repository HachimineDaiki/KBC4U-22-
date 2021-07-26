#pragma once
#include <DxLib.h>
#define DECELEARIA_NUM 4
//構造体宣言
struct Sph
{
	/*float x, y, z;*/
	float radius;
	float speed;
	float v0y;
	int color;
	VECTOR pos;
	float zaccl; //Z軸加速
	float zmove; //Z軸動く
};

void Sph_init();
void Model_init();
void Obj_init();
void Decelearia_init();
//オブジェクト生成
extern Sph sph[2];//プレイヤー
extern Sph obj;//不法投棄物
extern Sph deceleAria[DECELEARIA_NUM]; //減速エリア　
extern float vx, vy, vz;