#pragma once
struct Sph_
{
	float x, y, z;
	float radius;
	float speed;
};

bool Sph_hit_check(Sph_ sp[]);
void Sph_init();

//変数
const int sph_num = 2;
//オブジェクト生成
extern Sph_ sph[sph_num];