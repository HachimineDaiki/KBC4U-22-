#pragma once
#include <DxLib.h>
#define DECELEARIA_NUM 100
//�\���̐錾
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

void Sph_init();
void Model_init();
void Obj_init();
void Decelearia_init();
//�I�u�W�F�N�g����
extern Sph sph[2];//�v���C���[
extern Sph obj;//�s�@������
extern Sph decelearia[DECELEARIA_NUM]; //�����G���A

extern float merikomi;

extern int gameMode;

//extern enum GAMEMODE;//�Q�[�����[�h