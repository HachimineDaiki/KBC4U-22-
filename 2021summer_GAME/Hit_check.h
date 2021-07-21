#pragma once
#include <DxLib.h>
#include <math.h>
#include "Init.h"

// プレイヤー関係の定義
#define PLAYER_MOVE_SPEED			30.0f		// 移動速度
#define PLAYER_ANGLE_SPEED			0.2f		// 角度変化速度
#define PLAYER_MAX_HITCOLL			2048		// 処理するコリジョンポリゴンの最大数
#define PLAYER_ENUM_DEFAULT_SIZE	800.0f		// 周囲のポリゴン検出に使用する球の初期サイズ
#define PLAYER_HIT_WIDTH			100.0f		// 当たり判定カプセルの半径
#define PLAYER_HIT_HEIGHT			700.0f		// 当たり判定カプセルの高さ
#define PLAYER_HIT_TRYNUM			16		// 壁押し出し処理の最大試行回数
#define PLAYER_HIT_SLIDE_LENGTH		5.0f		// 一度の壁押し出し処理でスライドさせる距離

// ステージ関係の定義
#define STAGECOLLOBJ_MAXNUM			256		// 追加のコリジョンオブジェクトの最大数

//プロトタイプ宣言
//bool Sph_hit_check(Sph sp[]);
//void Sph_hit();
//void Model_hit_check();
//void Model_hit();
void Ground_model_hit();
void Ground_model_hit_check(VECTOR MoveVector);
struct StageModelHit
{
	int i, j, k;						// 汎用カウンタ変数
	int MoveFlag;						// 水平方向に移動したかどうかのフラグ( ０:移動していない  １:移動した )
	int HitFlag;						// ポリゴンに当たったかどうかを記憶しておくのに使う変数( ０:当たっていない  １:当たった )
	MV1_COLL_RESULT_POLY_DIM HitDim[STAGECOLLOBJ_MAXNUM + 1];			// プレイヤーの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
	int HitDimNum;						// HitDim の有効な配列要素数
	int KabeNum;						// 壁ポリゴンと判断されたポリゴンの数
	int YukaNum;						// 床ポリゴンと判断されたポリゴンの数
	MV1_COLL_RESULT_POLY* Kabe[PLAYER_MAX_HITCOLL];	// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* Yuka[PLAYER_MAX_HITCOLL];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* Poly;				// ポリゴンの構造体にアクセスするために使用するポインタ( 使わなくても済ませられますがプログラムが長くなるので・・・ )
	HITRESULT_LINE LineRes;				// 線分とポリゴンとの当たり判定の結果を代入する構造体
	VECTOR OldPos;						// 移動前の座標	
	VECTOR NowPos;						// 移動後の座標
	//移動ベクトル
	VECTOR TargetMoveDirection;			// モデルが向くべき方向のベクトル
	VECTOR movepos;

	VECTOR upvec = VGet(0.0f, 0.0f, 1.0f);
	VECTOR downvec = VGet(0.0f, 0.0f, -1.0f);
	VECTOR rightvec = VGet(1.0f, 0.0f, 0.0f);
	VECTOR leftvec = VGet(-1.0f, 0.0f, 0.0f);

};

extern StageModelHit st_model_hit;
