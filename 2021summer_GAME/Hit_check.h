#pragma once
struct Sph_
{
	float x, y, z;
	float radius;
	float speed;
};

bool Sph_hit_check(Sph_ sp[]);
void Sph_init();

//�ϐ�
const int sph_num = 2;
//�I�u�W�F�N�g����
extern Sph_ sph[sph_num];