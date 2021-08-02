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
	float zaccl; //Z������
	float zmove; //Z������
	float control;
};

int Input_PlayerMoveDir();//�v���C���[���͕���
void P_input_move();//�v���C���[�̓��͎�t
void P_move();//�v���C���[����

void Sph_Gravity();//�v���C���[�d��
void Accl();//��������

struct Input {
	bool space;
};

enum Dir { Left, Right, Down, Up };

//�I�u�W�F�N�g����
extern Sph sph[2];//�v���C���[
extern Sph obj;//�s�@������
extern Sph decelearia[DECELEARIA_NUM]; //�����G���A

extern float s_dis;
extern bool p_zmoveflg;//�O�i�Ɉړ�����t���O
extern VECTOR TempMoveVector;
extern Input input;