#include <DxLib.h>
#include "3Dmodel.h"

float wood_interval = 1300;//木の間隔

void Model3d_load() {
	//Stage15
	//Stage_Short.mv1
	//Stage_Short_1.1
	ground.handle = MV1LoadModel("3Dmodel/Stage_Short_2.0");
	rock[0].handle = MV1LoadModel("3Dmodel/Rock.mv1");
	rock[1].handle = MV1LoadModel("3Dmodel/Rock_1.mv1");
	rock[2].handle = MV1LoadModel("3Dmodel/Rock_red.mv1");

	//ぬかるみ床
	for (int i = 0; i < DECELE_ARIA_MAX; i++) {
		gensoku[i].handle = MV1LoadModel("3Dmodel/MudColor_11cm.mv1");
	}
	//障害物岩
	for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
		if (damege_aria[i].name == L) {
			e_rock[i].handle = MV1LoadModel("3Dmodel/Rock_L.mv1");
		}
		else if(damege_aria[i].name == M){
			e_rock[i].handle = MV1LoadModel("3Dmodel/Rock_M.mv1");
		}else if (damege_aria[i].name == S) {
			e_rock[i].handle = MV1LoadModel("3Dmodel/Rock_S.mv1");
		}
	}
}

void Model3d_init() {
	//画面に映る位置に３Ｄモデルを移動
	MV1SetPosition(ground.handle, VGet(ground.x, ground.y, ground.z));//初期位置設定
	
	//壁の初期位置
	//for (int i = 0; i < WALL_MAX;i++) {
	//	MV1SetPosition(wall[i].handle, VGet(wall[i].x,wall[i].y,wall[i].z));//初期位置設定
	//	rock[0].handle_num = 0;//岩モデル　初期色　handle
	//}

	for (int i = 0; i < DECELE_ARIA_MAX; i++) {
		MV1SetPosition(gensoku[i].handle, VGet(decele_aria[i].pos.x, decele_aria[i].pos.y-120, decele_aria[i].pos.z));//初期位置設定
	}

	for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
		MV1SetPosition(e_rock[i].handle, VGet(damege_aria[i].pos.x, damege_aria[i].pos.y - 60, damege_aria[i].pos.z));//初期位置設定
	}

	
	//壁モデル回転 (度数 * DX_PI_F / 180.0f) で度数に変換
	MV1SetRotationXYZ(wall[0].handle, VGet(10.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
	MV1SetRotationXYZ(wall[1].handle, VGet(10.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
	MV1SetRotationXYZ(ground.handle, VGet(5.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));


	MV1SetupCollInfo(ground.handle, -1);
}

void Model3d_draw() {
	//３Ｄモデルの描画
	MV1DrawModel(ground.handle);
	MV1DrawModel(rock[rock[0].handle_num].handle);
	
	for (int i = 0; i < DECELE_ARIA_MAX; i++) {
		MV1DrawModel(gensoku[i].handle);
		MV1SetRotationXYZ(gensoku[i].handle, VGet(10.0f * DX_PI_F / 180.0f, 0.0f, 0.0f));
	}
}

void Model3d_dlet() {
	//// モデルハンドルの削除
	MV1DeleteModel(ground.handle);

	for (int i = 0; i < PLYAER_COLOR; i++) { //プレイヤー色
		MV1DeleteModel(rock[i].handle);
	}
	for (int i = 0; i < DECELE_ARIA_MAX; i++) { //プレイヤー色
		MV1DeleteModel(gensoku[i].handle);
	}

	for (int i = 0; i < DAMEGE_ARIA_MAX; i++) { //プレイヤー色
		MV1DeleteModel(e_rock[i].handle);
	}
}