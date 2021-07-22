#include <Dxlib.h>
#include <math.h>
#include "Hit_check.h"
#include "3Dmodel.h"
#include "Player.h"

float p_vz = 0;
struct STAGE
{
	int		ModelHandle;				// ステージのモデルハンドル
	int		CollObjBaseModelHandle;		// コリジョンモデルの派生元ハンドル
	int		CollObjModelHandle[STAGECOLLOBJ_MAXNUM];	// ステージに配置するコリジョンモデルのハンドル
	int		CollObjNum;				// ステージに配置しているコリジョンモデルの数
};

STAGE stg;


//bool Sph_hit_check(Sph sp[]) {
//	vx = sp[1].x - sp[0].x;//x成分
//	vy = sp[1].y - sp[0].y;//y成分
//	vz = sp[1].z - sp[0].z;//z成分
//	float distance = vx * vx + vy * vy + vz * vz;//2点間の距離
//	float radius_sum = (sp[0].radius + sp[1].radius) * (sp[0].radius + sp[1].radius); //半径の和
//	return distance < radius_sum ? true : false;//2点間の距離が半径の和より小さければ当たっていると判定
//}

void Ground_model_hit() {
	
	st_model_hit.movepos = VGet(0.0f, 0.0f,0.0f);//移動ベクトル
	st_model_hit.MoveFlag = 0;// 移動したかどうかのフラグを初期状態では「移動していない」を表す０にする

	P_input_move();//プレイヤー入力
	P_move();
	//地面についていなかったら重力発生
	if (!st_model_hit.groundflg) {
		Sph_Gravity();//重力
	}
	Sph_Gravity();//重力
	/*DrawFormatString(100, 220, GetColor(255, 0, 0), " %d", st_model_hit.groundflg);*/
	// 移動ボタンが押されたかどうかで処理を分岐
	if (st_model_hit.MoveFlag)
	{
		// 移動ベクトルを正規化したものをプレイヤーが向くべき方向として保存
		st_model_hit.TargetMoveDirection = VNorm(st_model_hit.movepos);
		/*DrawFormatString(100, 200, GetColor(255, 255, 255), " %.1f , %.1f , %.1f ", st_model_hit.TargetMoveDirection.x, st_model_hit.TargetMoveDirection.y, st_model_hit.TargetMoveDirection.z);*/
		// プレイヤーが向くべき方向ベクトルをプレイヤーのスピード倍したものを移動ベクトルとする
		st_model_hit.movepos = VScale(st_model_hit.TargetMoveDirection, sph[0].speed);
		/*DrawFormatString(100, 230, GetColor(255, 0, 0), "Vscale %.1f , %.1f , %.1f ", st_model_hit.movepos.x, st_model_hit.movepos.y, st_model_hit.movepos.z);*/
	}
	
	Ground_model_hit_check(st_model_hit.movepos);
}
void Ground_model_hit_check(VECTOR MoveVector) {
	// 移動前の座標を保存
	st_model_hit.OldPos = sph[0].pos;
	// 移動後の座標を算出
	st_model_hit.NowPos = VAdd(sph[0].pos, MoveVector);
	 //プレイヤーの周囲にあるステージポリゴンを取得する
	 //( 検出する範囲は移動距離も考慮する )
	st_model_hit.HitDim[0] = MV1CollCheck_Sphere(ground_handle, -1, sph[0].pos, PLAYER_ENUM_DEFAULT_SIZE + VSize(MoveVector));
	// プレイヤーの周囲にあるコリジョンオブジェクトのポリゴンも取得する
	for (int i = 0; i < stg.CollObjNum; i++)
	{

		st_model_hit.HitDim[i + 1] = MV1CollCheck_Sphere(stg.CollObjModelHandle[i], -1, sph[0].pos, PLAYER_ENUM_DEFAULT_SIZE + VSize(MoveVector));
	}

	// HitDim の有効な数はコリジョンオブジェクトの数とステージ自体のコリジョン
	st_model_hit.HitDimNum = stg.CollObjNum + 1;
	// x軸かy軸方向に 0.01f 以上移動した場合は「移動した」フラグを１にする
	if (fabs(MoveVector.x) > 0.01f || fabs(MoveVector.z) > 0.01f)
	{
		st_model_hit.MoveFlag = 1;
	}
	else
	{
		st_model_hit.MoveFlag = 0;
	}

	// 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断する
	{
		// 壁ポリゴンと床ポリゴンの数を初期化する
		st_model_hit.KabeNum = 0;
		st_model_hit.YukaNum = 0;


		// 検出されたポリゴンの数だけ繰り返し
		for (int j = 0; j < st_model_hit.HitDimNum; j++)
		{
			for (int i = 0; i < st_model_hit.HitDim[j].HitNum; i++)
			{
				// ＸＺ平面に垂直かどうかはポリゴンの法線のＹ成分が０に限りなく近いかどうかで判断する
				if (st_model_hit.HitDim[j].Dim[i].Normal.y < 0.000001f && st_model_hit.HitDim[j].Dim[i].Normal.y > -0.000001f)
				{
					// 壁ポリゴンと判断された場合でも、プレイヤーのＹ座標＋１．０ｆより高いポリゴンのみ当たり判定を行う
					if (st_model_hit.HitDim[j].Dim[i].Position[0].y > sph[0].pos.y + 1.0f ||
						st_model_hit.HitDim[j].Dim[i].Position[1].y > sph[0].pos.y + 1.0f ||
						st_model_hit.HitDim[j].Dim[i].Position[2].y > sph[0].pos.y + 1.0f)
					{
						// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
						if (st_model_hit.KabeNum < PLAYER_MAX_HITCOLL)
						{
							// ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
							st_model_hit.Kabe[st_model_hit.KabeNum] = &st_model_hit.HitDim[j].Dim[i];

							// 壁ポリゴンの数を加算する
							st_model_hit.KabeNum++;
						}
					}
				}
				else
				{
					// ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
					if (st_model_hit.YukaNum < PLAYER_MAX_HITCOLL)
					{
						// ポリゴンの構造体のアドレスを床ポリゴンポインタ配列に保存する
						st_model_hit.Yuka[st_model_hit.YukaNum] = &st_model_hit.HitDim[j].Dim[i];

						// 床ポリゴンの数を加算する
						st_model_hit.YukaNum++;
					}
				}
			}
		}
	}

	//// 壁ポリゴンとの当たり判定処理
	//if (st_model_hit.KabeNum != 0)
	//{
	//	// 壁に当たったかどうかのフラグは初期状態では「当たっていない」にしておく
	//	st_model_hit.HitFlag = 0;

	//	// 移動したかどうかで処理を分岐
	//	if (st_model_hit.MoveFlag == 1)
	//	{
	//		// 壁ポリゴンの数だけ繰り返し
	//		for (int i = 0; i < st_model_hit.KabeNum; i++)
	//		{
	//			// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
	//			st_model_hit.Poly = st_model_hit.Kabe[i];

	//			// ポリゴンとプレイヤーが当たっていなかったら次のカウントへ
	//			if (HitCheck_Capsule_Triangle(st_model_hit.NowPos, VAdd(st_model_hit.NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, st_model_hit.Poly->Position[0], st_model_hit.Poly->Position[1], st_model_hit.Poly->Position[2]) == FALSE) continue;

	//			// ここにきたらポリゴンとプレイヤーが当たっているということなので、ポリゴンに当たったフラグを立てる
	//			st_model_hit.HitFlag = 1;

	//			//壁に当たったら壁に遮られない移動成分分だけ移動する
	//			{
	//				VECTOR SlideVec;	// プレイヤーをスライドさせるベクトル

	//				// 進行方向ベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出
	//				SlideVec = VCross(MoveVector, st_model_hit.Poly->Normal);

	//				// 算出したベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出、これが
	//				// 元の移動成分から壁方向の移動成分を抜いたベクトル
	//				SlideVec = VCross(st_model_hit.Poly->Normal, SlideVec);

	//				// それを移動前の座標に足したものを新たな座標とする
	//				st_model_hit.NowPos = VAdd(st_model_hit.OldPos, SlideVec);
	//			}

	//			int j;
	//			// 新たな移動座標で壁ポリゴンと当たっていないかどうかを判定する
	//			for (j = 0; j < st_model_hit.KabeNum; j++)
	//			{
	//				// j番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
	//				st_model_hit.Poly = st_model_hit.Kabe[j];

	//				// 当たっていたらループから抜ける
	//				if (HitCheck_Capsule_Triangle(st_model_hit.NowPos, VAdd(st_model_hit.NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, st_model_hit.Poly->Position[0], st_model_hit.Poly->Position[1], st_model_hit.Poly->Position[2]) == TRUE) break;
	//			}

	//			// j が KabeNum だった場合はどのポリゴンとも当たらなかったということなので
	//			// 壁に当たったフラグを倒した上でループから抜ける
	//			if (j == st_model_hit.KabeNum)
	//			{
	//				st_model_hit.HitFlag = 0;
	//				break;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		// 移動していない場合の処理

	//		// 壁ポリゴンの数だけ繰り返し
	//		for (int i = 0; i < st_model_hit.KabeNum; i++)
	//		{
	//			// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
	//			st_model_hit.Poly = st_model_hit.Kabe[i];

	//			// ポリゴンに当たっていたら当たったフラグを立てた上でループから抜ける
	//			if (HitCheck_Capsule_Triangle(st_model_hit.NowPos, VAdd(st_model_hit.NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, st_model_hit.Poly->Position[0], st_model_hit.Poly->Position[1], st_model_hit.Poly->Position[2]) == TRUE)
	//			{
	//				st_model_hit.HitFlag = 1;
	//				break;
	//			}
	//		}
	//	}
	//}


	// 床ポリゴンとの当たり判定
	if (st_model_hit.YukaNum != 0)
	{


		float MaxY;

		// 下降中かジャンプ中ではない場合の処理

		// 床ポリゴンに当たったかどうかのフラグを倒しておく
		st_model_hit.HitFlag = 0;

		// 一番高い床ポリゴンにぶつける為の判定用変数を初期化
		MaxY = 0.0f;

		// 床ポリゴンの数だけ繰り返し
		for (int i = 0; i < st_model_hit.YukaNum; i++)
		{
			// i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
			st_model_hit.Poly = st_model_hit.Yuka[i];


			// 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
			/*st_model_hit.LineRes = HitCheck_Line_Triangle(VAdd(st_model_hit.NowPos, VGet(0.0f, 0.0f, 0.0f)), VAdd(st_model_hit.NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), st_model_hit.Poly->Position[0], st_model_hit.Poly->Position[1], st_model_hit.Poly->Position[2]);*/
			st_model_hit.LineRes = HitCheck_Line_Triangle(st_model_hit.NowPos, VAdd(st_model_hit.NowPos, VGet(0.0f, -200, 0.0f)), st_model_hit.Poly->Position[0], st_model_hit.Poly->Position[1], st_model_hit.Poly->Position[2]);
			
			//DrawFormatString(100, 220, GetColor(255, 0, 0), "[0] %.0f  %.0f  %.0f", st_model_hit.Poly->Position[0].x, st_model_hit.Poly->Position[0].y, st_model_hit.Poly->Position[0].z);
			//// 当たっていなかったら何もしない
			//DrawFormatString(100, 240, GetColor(255, 0, 0), "[1] %.0f  %.0f  %.0f", st_model_hit.Poly->Position[1].x, st_model_hit.Poly->Position[1].y, st_model_hit.Poly->Position[1].z);
			//DrawFormatString(100, 260, GetColor(255, 0, 0), "[2] %.0f  %.0f  %.0f", st_model_hit.Poly->Position[2].x, st_model_hit.Poly->Position[2].y, st_model_hit.Poly->Position[2].z);
			if (st_model_hit.LineRes.HitFlag == FALSE) { 
				
				continue; 
			}
			//ここまでやった
			
			// 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
			if (st_model_hit.HitFlag == 1 && MaxY > st_model_hit.LineRes.Position.y) continue;

			// ポリゴンに当たったフラグを立てる
			st_model_hit.HitFlag = 1;
			// 接触したＹ座標を保存する
			MaxY = st_model_hit.LineRes.Position.y + sph[0].radius;
			/*DrawFormatString(100, 240, GetColor(255, 0, 0), " Line.Y %d", st_model_hit.LineRes.Position.y);*/
			st_model_hit.groundflg = true; //地面についたフラグを立てる
		}
		DrawLine3D(st_model_hit.NowPos, VAdd(st_model_hit.NowPos,VGet(0.0f,-200.f,0.0f)), GetColor(255, 0, 0));
		// 床ポリゴンに当たったかどうかで処理を分岐
		if (st_model_hit.HitFlag == 1)
		{
			// 当たった場合

			// 接触したポリゴンで一番高いＹ座標をプレイヤーのＹ座標にする
			st_model_hit.NowPos.y = MaxY;
		}

		DrawFormatString(100, 270, GetColor(255, 255, 255), "MaxY %.1f", MaxY);
	}

	
	sph[0].pos = st_model_hit.NowPos;
	
	DrawSphere3D(sph[0].pos, sph[0].radius, 32, sph[0].color, GetColor(255, 255, 255), TRUE);
	DrawFormatString(100, 100, GetColor(255, 255, 255), "[sphx %.0f] [sphy %.0f] [sphz %.0f]", sph[0].pos.x, sph[0].pos.y, sph[0].pos.z);
	// 検出したプレイヤーの周囲のポリゴン情報を開放する
	for (int i = 0; i < st_model_hit.HitDimNum; i++)
	{
		MV1CollResultPolyDimTerminate(st_model_hit.HitDim[i]);
	}
}
//球と球の当たり判定を検知した後の処理
//void Sph_hit() {
//}

////モデルと球の当たり判定チェック
//void Model_hit_check() {
//	//球のベクトル型 Posに代入
//	sph[0].pos = VGet(sph[0].x, sph[0].y, sph[0].z);
//
//	//モデルと球の当たり判定を取得
//	for (int i = 0; i < TREE_NUM; i++) {
//		HitPolyDim[i] = MV1CollCheck_Sphere(tree_handle[i], -1, sph[0].pos, sph[0].radius);
//	}
//}

//void Model_hit() {
//	//当たり判定を検知した後の処理
//	for (int j = 0; j < TREE_NUM; j++) {
//		if (HitPolyDim[j].HitNum >= 1)
//		{
//			SetFontSize(50);
//			DrawFormatString(600, 250, GetColor(255, 0, 0), "[木のモデル HIT]");
//			SetFontSize(20);
//		}
//		//DrawFormatString(100, 300 + ((j + 1) * 20), GetColor(255, 255, 255), "%d", HitPolyDim[j].HitNum);//当たったモデルのpolygon数表示
//	}
//
//	//モデル判定のメモリ解放
//	for (int i = 0; i < TREE_NUM; i++) {
//		MV1CollResultPolyDimTerminate(HitPolyDim[i]);
//	}
//}