#include <DxLib.h>
#include "3Dmodel.h"

float wood_interval = 1300;//–Ø‚ÌŠÔŠu

void Model3d_load() {
	//–Ø‚Ì“Ç‚İ‚İ
	ground_handle = MV1LoadModel("3Dmodel/ground_v1.mv1");
	for (int i = 0; i < TREE_NUM; i++) {
		tree_handle[i] = MV1LoadModel("3Dmodel/tree_v1.mv1");
	}
}

void Model3d_init() {
	//‰æ–Ê‚É‰f‚éˆÊ’u‚É‚R‚cƒ‚ƒfƒ‹‚ğˆÚ“®
	MV1SetPosition(ground_handle, VGet(320.0f, -300.0f, 600.0f));
	for (int i = 0; i < TREE_NUM / 4; i++) {
		MV1SetPosition(tree_handle[i], VGet(-1200.0f, -300.0f, -650.0f + (wood_interval * i)));
		MV1SetPosition(tree_handle[i + TREE_NUM / 4], VGet(-550.0f, -300.0f, 0.0f + (wood_interval * i)));
		MV1SetPosition(tree_handle[i + TREE_NUM / 2], VGet(-550.0f + wood_interval, -300.0f, 0.0f + (wood_interval * i)));
		MV1SetPosition(tree_handle[i + TREE_NUM / 4 + TREE_NUM / 2], VGet(100.0f + wood_interval, -300.0f, -650.0f + (wood_interval * i)));
	}

}

void Model3d_draw() {
	//‚R‚cƒ‚ƒfƒ‹‚Ì•`‰æ
	MV1DrawModel(ground_handle);
	for (int i = 0; i < TREE_NUM; i++) {
		MV1DrawModel(tree_handle[i]);
	}

}

void Model3d_dlet() {
	//// ƒ‚ƒfƒ‹ƒnƒ“ƒhƒ‹‚Ìíœ
	MV1DeleteModel(ground_handle);
	for (int i = 0; i < TREE_NUM; i++) {
		MV1DeleteModel(tree_handle[i]);
	}

}