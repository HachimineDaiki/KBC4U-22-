#pragma once
#define TREE_NUM 36 //�؂̐�

struct Model {
	float x, y, z;//���f���̍��W
	int handle;
};

void Model3d_init();//�������ʒu
void Model3d_load();//3D�ǂݍ���
void Model3d_draw();//3D�`��
void Model3d_dlet();//3D���f������

//extern �̓t�@�C���̊O���ɕϐ������L���������
extern MV1_COLL_RESULT_POLY_DIM HitPolyDim[TREE_NUM];
extern Model ground;
extern Model rock;