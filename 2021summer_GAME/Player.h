#pragma once
#define VECTOR_SLIDE 0.86602540378

int Input_PlayerMoveDir();//�v���C���[���͕���

void P_input_move();//�v���C���[�̓��͎�t
void P_move();//�v���C���[����

void Sph_Gravity();//�v���C���[�d��
void Accl();//��������

enum Dir { Left, Right, Down, Up };

extern float s_dis;
extern bool p_zmoveflg;//�O�i�Ɉړ�����t���O
extern VECTOR TempMoveVector;
