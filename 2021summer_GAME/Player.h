#pragma once
#define VECTOR_SLIDE 0.86602540378

int Input_PlayerMoveDir();

void P_input_move();
void P_move();

void Sph_Gravity();

void Move_Limits();		//プレイヤーの左右移動を制限する

enum Dir { Left, Right, Down, Up };

extern float s_dis;
//void accl(); // 加速
