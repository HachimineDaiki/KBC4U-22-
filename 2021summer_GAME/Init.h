#pragma once
#include <DxLib.h>
//�\���̐錾
struct Sph
{
	/*float x, y, z;*/
	float radius;
	float speed;
	float v0y;
	int color;
	VECTOR pos;
	float zaccl; //Z������
	float zmove; //Z������
};

void Sph_init();
void Model_init();
void Obj_init();

//�I�u�W�F�N�g����
extern Sph sph[2];//�v���C���[
extern Sph obj;//�s�@������
extern float vx, vy, vz;