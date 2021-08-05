#pragma once
//#define TREE_NUM 36 //木の数

struct Model {
	float x, y, z;//モデルの座標
	int handle;//モデルhandle
};

void Model3d_init();//初期化位置
void Model3d_load();//3D読み込み
void Model3d_draw();//3D描画
void Model3d_dlet();//3Dモデル消す

//extern はファイルの外部に変数を共有させるもの
extern Model ground;//地面
extern Model rock;//プレイヤー岩