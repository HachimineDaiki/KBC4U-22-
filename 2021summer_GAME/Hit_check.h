#pragma once
//構造体宣言
struct Sph
{
	float x, y, z;
	float radius;
	float speed;
};

bool Sph_hit_check(Sph sp[]);//関数プロトタイプ宣言 //引数は名前が違うもの書いてる
void Sph_init();

////変数
//const int sph_num;
//オブジェクト生成
extern Sph sph[2];//オブジェクト生成