#pragma once
#define VECTOR_SLIDE 0.86602540378
#define DECELEARIA_NUM 100
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

int Input_PlayerMoveDir();//プレイヤー入力方向
void P_input_move();//プレイヤーの入力受付
void P_move();//プレイヤー動き

void Sph_Gravity();//プレイヤー重力
void Accl();//加速処理

struct Input {
	bool space;
};

enum Dir { Left, Right, Down, Up };

//オブジェクト生成
extern Sph sph[2];//プレイヤー
extern Sph obj;//不法投棄物
extern Sph decelearia[DECELEARIA_NUM]; //減速エリア

extern float s_dis;
extern bool p_zmoveflg;//前進に移動するフラグ
extern VECTOR TempMoveVector;
extern Input input;