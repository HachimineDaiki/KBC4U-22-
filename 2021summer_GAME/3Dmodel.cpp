#include <DxLib.h>
#include "3Dmodel.h"

float wood_interval = 1300;//木の間隔

void Model3d_load() {
	//木の読み込み
	ground.handle = MV1LoadModel("3Dmodel/floor_game.mv1");
	rock.handle = MV1LoadModel("3Dmodel/sph.mv1");
	//for (int i = 0; i < TREE_NUM; i++) {
	//	tree_handle[i] = MV1LoadModel("3Dmodel/tree.mv1");
	//}
}

void Model3d_init() {
	//画面に映る位置に３Ｄモデルを移動
	MV1SetPosition(ground.handle, VGet(ground.x, ground.y, ground.z));//初期位置設定


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


	MV1SetupCollInfo(ground.handle, -1);


	//// ３ＤモデルのY軸の回転値を９０度にセットする
	//MV1SetRotationXYZ(ground_handle, VGet(2.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
}

void Model3d_draw() {
	//３Ｄモデルの描画
	MV1DrawModel(ground.handle);
	MV1DrawModel(rock.handle);
	//for (int i = 0; i < TREE_NUM; i++) {
	//	MV1DrawModel(tree_handle[i]);
	//}

}

void Model3d_dlet() {
	//// モデルハンドルの削除
	MV1DeleteModel(ground.handle);
	MV1DeleteModel(rock.handle);
	//for (int i = 0; i < TREE_NUM; i++) {
	//	MV1DeleteModel(tree_handle[i]);
	//}

}