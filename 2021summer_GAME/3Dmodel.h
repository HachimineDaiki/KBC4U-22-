#pragma once
#define TREE_NUM 36 //�؂̐�
void Model3d_init();//�������ʒu
void Model3d_load();//3D�ǂݍ���
void Model3d_draw();//3D�`��
void Model3d_dlet();//3D���f������

//extern �̓t�@�C���̊O���ɕϐ������L���������

extern int ground_handle;//�n�ʃ��f�������ϐ�
extern int tree_handle[TREE_NUM];//�؂̃��f�������ϐ�
