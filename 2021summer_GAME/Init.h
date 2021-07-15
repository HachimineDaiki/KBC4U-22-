#pragma once
#include <DxLib.h>
//構造体宣言
struct Sph
{
	float x, y, z;
	float radius;
	float speed;
	float v0y;
	int color;
	VECTOR pos;
};

void Sph_init();
void Model_init();

//オブジェクト生成
extern Sph sph[2];//オブジェクト生成
extern float vx, vy, vz;