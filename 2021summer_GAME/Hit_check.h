#pragma once
//�\���̐錾
struct Sph
{
	float x, y, z;
	float radius;
	float speed;
};

bool Sph_hit_check(Sph sp[]);//�֐��v���g�^�C�v�錾 //�����͖��O���Ⴄ���̏����Ă�
void Sph_init();

////�ϐ�
//const int sph_num;
//�I�u�W�F�N�g����
extern Sph sph[2];//�I�u�W�F�N�g����