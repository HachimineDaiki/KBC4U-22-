#pragma once
//�\���̐錾
struct Sph
{
	float x, y, z;
	float radius;
	float speed;
	float v0y;
};

void Sph_init();

//�I�u�W�F�N�g����
extern Sph sph[2];//�I�u�W�F�N�g����
extern float vx, vy, vz;