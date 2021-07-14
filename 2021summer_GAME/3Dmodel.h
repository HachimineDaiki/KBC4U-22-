#pragma once
#define TREE_NUM 10 //木の数
void Model3d_init();//初期化位置
void Model3d_load();//3D読み込み
void Model3d_draw();//3D描画
void Model3d_dlet();//3Dモデル消す

//extern はファイルの外部に変数を共有させるもの

extern int ground_handle;//地面モデル入れる変数
extern int tree_handle[TREE_NUM];//木のモデル入れる変数