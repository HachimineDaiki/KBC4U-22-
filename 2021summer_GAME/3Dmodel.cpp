#include <DxLib.h>
#include "3Dmodel.h"

float wood_interval = 1300;//�؂̊Ԋu

void Model3d_load() {
	ground.handle = MV1LoadModel("3Dmodel/Stage_short1.mv1");
	rock[0].handle = MV1LoadModel("3Dmodel/Rock.mv1");
	rock[1].handle = MV1LoadModel("3Dmodel/Rock_1.mv1");
	rock[2].handle = MV1LoadModel("3Dmodel/Rock_red.mv1");
}

void Model3d_init() {
	//��ʂɉf��ʒu�ɂR�c���f�����ړ�
	MV1SetPosition(ground.handle, VGet(ground.x, ground.y, ground.z));//�����ʒu�ݒ�
	//for (int i = 0; i < TREE_NUM / 4; i++) {
	//	MV1SetPosition(tree_handle[i], VGet(-1200.0f, ground.y, -650.0f + (wood_interval * i)));
	//	//MV1SetRotationXYZ(tree_handle[i], VGet(10.0f, 0.0f, 0.0f));

	//	/*MV1SetPosition(tree_handle[i + TREE_NUM / 4], VGet(-550.0f, ground.y, 0.0f + (wood_interval * i)));
	//	MV1SetRotationXYZ(tree_handle[i + TREE_NUM / 4], VGet(45.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));

	//	MV1SetPosition(tree_handle[i + TREE_NUM / 2], VGet(-550.0f + wood_interval, ground.y, 0.0f + (wood_interval * i)));
	//	MV1SetRotationXYZ(tree_handle[i + TREE_NUM / 2], VGet(45.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));

	//	MV1SetPosition(tree_handle[i + TREE_NUM / 4 + TREE_NUM / 2], VGet(100.0f + wood_interval, ground.y, -650.0f + (wood_interval * i)));
	//	MV1SetRotationXYZ(tree_handle[i + TREE_NUM / 4 + TREE_NUM / 2], VGet(45.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));*/
	//}

	MV1SetupCollInfo(ground.handle, -1);
}

void Model3d_draw() {
	//�R�c���f���̕`��
	MV1DrawModel(ground.handle);
	MV1DrawModel(rock[rock[0].handle_num].handle);
}

void Model3d_dlet() {
	//// ���f���n���h���̍폜
	MV1DeleteModel(ground.handle);
	
	for (int i = 0; i < PLYAER_COLOR; i++) { //�v���C���[�F
		MV1DeleteModel(rock[i].handle);
	}
}