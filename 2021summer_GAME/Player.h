#pragma once
#define VECTOR_SLIDE 0.86602540378

int Input_PlayerMoveDir();

void P_input_move();
void P_move();

void Sph_Gravity();
void Accl();//加速処理

enum Dir { Left, Right, Down, Up };

extern float s_dis;
extern bool p_zmoveflg;//前進に移動するフラグ
//void accl(); // 加速
