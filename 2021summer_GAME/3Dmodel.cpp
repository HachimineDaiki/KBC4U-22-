#include <DxLib.h>
#include "3Dmodel.h"

float wood_interval = 1300;//–Ø‚ÌŠÔŠu

void Model3d_load() {
	//–Ø‚Ì“Ç‚İ‚İ
	ground_handle = MV1LoadModel("3Dmodel/floor.mv1");
	/*wall_handle = MV1LoadModel("3Dmodel/wall.mv1");*/
	//for (int i = 0; i < TREE_NUM; i++) {
	//	tree_handle[i] = MV1LoadModel("3Dmodel/tree.mv1");
	//}
}

void Model3d_init() {
	//‰æ–Ê‚É‰f‚éˆÊ’u‚É‚R‚cƒ‚ƒfƒ‹‚ğˆÚ“®
	MV1SetPosition(ground_handle, VGet(ground.x, ground.y, ground.z));//‰ŠúˆÊ’uİ’è
	MV1SetRotationXYZ(ground_handle, VGet(3.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));//‰ŠúŠp“xİ’è


	//MV1SetPosition(wall_handle, VGet(wall.x, wall.y, wall.z));
	//MV1SetRotationXYZ(wall_handle, VGet(3.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));

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


	MV1SetupCollInfo(ground_handle, -1);


	//// ‚R‚cƒ‚ƒfƒ‹‚ÌY²‚Ì‰ñ“]’l‚ğ‚X‚O“x‚ÉƒZƒbƒg‚·‚é
	//MV1SetRotationXYZ(ground_handle, VGet(2.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
}

void Model3d_draw() {
	//‚R‚cƒ‚ƒfƒ‹‚Ì•`‰æ
	MV1DrawModel(ground_handle);
	/*MV1DrawModel(wall_handle);*/
	//for (int i = 0; i < TREE_NUM; i++) {
	//	MV1DrawModel(tree_handle[i]);
	//}

}

void Model3d_dlet() {
	//// ƒ‚ƒfƒ‹ƒnƒ“ƒhƒ‹‚Ìíœ
	MV1DeleteModel(ground_handle);
	MV1DeleteModel(wall_handle);
	for (int i = 0; i < TREE_NUM; i++) {
		MV1DeleteModel(tree_handle[i]);
	}

}