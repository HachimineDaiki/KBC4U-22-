#pragma once
#define PLYAER_COLOR 3 //�v���C���[HP�����������ς��F
struct Model {
	float x, y, z;//���f���̍��W
	int handle;//���f��handle
	int handle_num;
};

void Model3d_init();//�������ʒu
void Model3d_load();//3D�ǂݍ���
void Model3d_draw();//3D�`��
void Model3d_dlet();//3D���f������

//extern �̓t�@�C���̊O���ɕϐ������L���������
extern Model ground;//�n��
extern Model rock[3];//�v���C���[��