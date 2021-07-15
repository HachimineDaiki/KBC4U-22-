#include <Dxlib.h>
#include <math.h>
#include "Hit_check.h"
#include "3Dmodel.h"

bool Sph_hit_check(Sph sp[]) {
	vx = sp[1].x - sp[0].x;//x成分
	vy = sp[1].y - sp[0].y;//y成分
	vz = sp[1].z - sp[0].z;//z成分
	float distance = vx * vx + vy * vy + vz * vz;//2点間の距離
	float radius_sum = (sp[0].radius + sp[1].radius) * (sp[0].radius + sp[1].radius); //半径の和
	return distance < radius_sum ? true : false;//2点間の距離が半径の和より小さければ当たっていると判定
}

//球と球の当たり判定を検知した後の処理
void Sph_hit() {
}

//モデルと球の当たり判定チェック
void Model_hit_check() {
	//球のベクトル型 Posに代入
	sph[0].pos = VGet(sph[0].x, sph[0].y, sph[0].z);

	//モデルと球の当たり判定を取得
	for (int i = 0; i < TREE_NUM; i++) {
		HitPolyDim[i] = MV1CollCheck_Sphere(tree_handle[i], -1, sph[0].pos, sph[0].radius);
	}
}

void Model_hit() {
	//当たり判定を検知した後の処理
	for (int j = 0; j < TREE_NUM; j++) {
		if (HitPolyDim[j].HitNum >= 1)
		{
			SetFontSize(50);
			DrawFormatString(600, 250, GetColor(255, 0, 0), "[木のモデル HIT]");
			SetFontSize(20);
		}
		//DrawFormatString(100, 300 + ((j + 1) * 20), GetColor(255, 255, 255), "%d", HitPolyDim[j].HitNum);//当たったモデルのpolygon数表示
	}

	//モデル判定のメモリ解放
	for (int i = 0; i < TREE_NUM; i++) {
		MV1CollResultPolyDimTerminate(HitPolyDim[i]);
	}
}