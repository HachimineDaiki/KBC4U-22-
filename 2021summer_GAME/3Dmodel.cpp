#include <DxLib.h>
#include "3Dmodel.h"

float wood_interval = 1300;//木の間隔

void Model3d_load() {
	//木の読み込み
	ground_handle = MV1LoadModel("3Dmodel/ground_v1.mv1");
	for (int i = 0; i < TREE_NUM; i++) {
		tree_handle[i] = MV1LoadModel("3Dmodel/tree_v1.mv1");
	}
}

void Model3d_init() {
	//画面に映る位置に３Ｄモデルを移動
	MV1SetPosition(ground_handle, VGet(320.0f, -300.0f, 600.0f));
	for (int i = 0; i < TREE_NUM / 4; i++) {
		MV1SetPosition(tree_handle[i], VGet(-1200.0f, -300.0f, -650.0f + (wood_interval * i)));
		MV1SetPosition(tree_handle[i + TREE_NUM / 4], VGet(-550.0f, -300.0f, 0.0f + (wood_interval * i)));
		MV1SetPosition(tree_handle[i + TREE_NUM / 2], VGet(-550.0f + wood_interval, -300.0f, 0.0f + (wood_interval * i)));
		MV1SetPosition(tree_handle[i + TREE_NUM / 4 + TREE_NUM / 2], VGet(100.0f + wood_interval, -300.0f, -650.0f + (wood_interval * i)));
	}

}

void Model3d_draw() {
	//３Ｄモデルの描画
	MV1DrawModel(ground_handle);
	for (int i = 0; i < TREE_NUM; i++) {
		MV1DrawModel(tree_handle[i]);
	}

}

void Model3d_dlet() {
	//// モデルハンドルの削除
	MV1DeleteModel(ground_handle);
	for (int i = 0; i < TREE_NUM; i++) {
		MV1DeleteModel(tree_handle[i]);
	}

}