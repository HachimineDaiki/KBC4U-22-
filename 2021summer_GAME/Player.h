#pragma once
#define VECTOR_SLIDE 0.86602540378

int Input_PlayerMoveDir();

void P_input_move();
void P_move();

void Sph_Gravity();

void Move_Limits();		//�v���C���[�̍��E�ړ��𐧌�����

enum Dir { Left, Right, Down, Up };

extern float s_dis;
//void accl(); // ����
