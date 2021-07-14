#include <DxLib.h>
#include "3Dmodel.h"

void Model3d_load() {
	ground_handle = MV1LoadModel("3Dmodel/ground_v1.mv1");
	tree_handle = MV1LoadModel("3Dmodel/tree_v1.mv1");
}

void Model3d_init() {
	 //画面に映る位置に３Ｄモデルを移動
	MV1SetPosition(ground_handle, VGet(320.0f, -300.0f, 600.0f));
	MV1SetPosition(tree_handle, VGet(0.0f, -300.0f, 600.0f));
}

void Model3d_draw() {
	//３Ｄモデルの描画
	MV1DrawModel(ground_handle);
	MV1DrawModel(tree_handle);
}

void Model3d_dlet() {
	//// モデルハンドルの削除
	MV1DeleteModel(ground_handle);
	MV1DeleteModel(tree_handle);
}