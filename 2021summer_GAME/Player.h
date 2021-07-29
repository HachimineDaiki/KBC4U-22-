#pragma once
#define VECTOR_SLIDE 0.86602540378

int Input_PlayerMoveDir();//プレイヤー入力方向

void P_input_move();//プレイヤーの入力受付
void P_move();//プレイヤー動き

void Sph_Gravity();//プレイヤー重力
void Accl();//加速処理

enum Dir { Left, Right, Down, Up };

extern float s_dis;
extern bool p_zmoveflg;//前進に移動するフラグ
extern VECTOR TempMoveVector;
