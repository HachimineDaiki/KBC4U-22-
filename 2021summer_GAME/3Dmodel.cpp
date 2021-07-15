#include <DxLib.h>
#include "3Dmodel.h"

float wood_interval = 1300;//�؂̊Ԋu

void Model3d_load() {
	//�؂̓ǂݍ���
	ground_handle = MV1LoadModel("3Dmodel/ground_v2.mv1");
	wall_handle = MV1LoadModel("3Dmodel/wall.mv1");
	for (int i = 0; i < TREE_NUM; i++) {
		tree_handle[i] = MV1LoadModel("3Dmodel/tree.mv1");
	}
}

void Model3d_init() {
	//��ʂɉf��ʒu�ɂR�c���f�����ړ�
	MV1SetPosition(ground_handle, VGet(ground.x, ground.y, ground.z));
	MV1SetPosition(wall_handle, VGet(wall.x, wall.y, wall.z));
	for (int i = 0; i < TREE_NUM / 4; i++) {
		MV1SetPosition(tree_handle[i], VGet(-1200.0f, ground.y, -650.0f + (wood_interval * i)));
		MV1SetPosition(tree_handle[i + TREE_NUM / 4], VGet(-550.0f, ground.y, 0.0f + (wood_interval * i)));
		MV1SetPosition(tree_handle[i + TREE_NUM / 2], VGet(-550.0f + wood_interval, ground.y, 0.0f + (wood_interval * i)));
		MV1SetPosition(tree_handle[i + TREE_NUM / 4 + TREE_NUM / 2], VGet(100.0f + wood_interval, ground.y, -650.0f + (wood_interval * i)));
	}

}

void Model3d_draw() {
	//�R�c���f���̕`��
	MV1DrawModel(ground_handle);
	MV1DrawModel(wall_handle);
	for (int i = 0; i < TREE_NUM; i++) {
		MV1DrawModel(tree_handle[i]);
	}

}

void Model3d_dlet() {
	//// ���f���n���h���̍폜
	MV1DeleteModel(ground_handle);
	MV1DeleteModel(wall_handle);
	for (int i = 0; i < TREE_NUM; i++) {
		MV1DeleteModel(tree_handle[i]);
	}

}