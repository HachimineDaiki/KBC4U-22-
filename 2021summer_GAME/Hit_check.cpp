#include <Dxlib.h>
#include <math.h>
#include "Hit_check.h"
#include "3Dmodel.h"
#include "Player.h"
#include "Camera.h"
#include "Init.h"

float p_vz = 0;
struct STAGE
{
	int		ModelHandle;				// ステージのモデルハンドル
	int		CollObjBaseModelHandle;		// コリジョンモデルの派生元ハンドル
	int		CollObjModelHandle[STAGECOLLOBJ_MAXNUM];	// ステージに配置するコリジョンモデルのハンドル
	int		CollObjNum;				// ステージに配置しているコリジョンモデルの数
};

STAGE stg;

//球同士当たり判定
bool Sph_hit_check(Sph sp[], Sph ob) {
	sph[0].v.x = ob.pos.x - sp[0].pos.x;//x成分
	sph[0].v.y = ob.pos.y - sp[0].pos.y;//y成分
	sph[0].v.z = ob.pos.z - sp[0].pos.z;//z成分

	s_dis = sph[0].v.x * sph[0].v.x + sph[0].v.y * sph[0].v.y + sph[0].v.z * sph[0].v.z;//2点間の距離

	float radius_sum = (sp[0].radius + ob.radius) * (sp[0].radius + ob.radius); //半径の和
	return s_dis < radius_sum ? true : false;//2点間の距離が半径の和より小さければ当たっていると判定
}

bool Decel_aria_check(Sph sp[], Sph decele[], int i) {
	decelearia[i].v.x = decele[i].pos.x - sp[0].pos.x;
	decelearia[i].v.y = decele[i].pos.y - sp[0].pos.y;
	decelearia[i].v.z = decele[i].pos.z - sp[0].pos.z;

	decelearia[i].dis = decelearia[i].v.x * decelearia[i].v.x + decelearia[i].v.y * decelearia[i].v.y + decelearia[i].v.z * decelearia[i].v.z;
	decelearia[i].radius_sum = (decele[i].radius + sp[0].radius) * (decele[i].radius + sp[0].radius);
	return decelearia[i].dis < decelearia[i].radius_sum ? true : false;
}

void Decel_aria_effect() {
	sph[0].zmove *= 0.93f;
}

//球と球の当たり判定を検知した後の処理
void Sph_hit(float dis) {
	float len = sqrtf(dis);
	float radius_sum = sph[0].radius + obj.radius;
	float merikomi = radius_sum - len;

	if (len > 0) len = 1 / len;

	sph[0].v.x *= len;
	sph[0].v.y *= len;
	sph[0].v.z *= len;

	merikomi /= 2.0f;

	//めり込み修正
	//sph[0].pos.x -= sph[0].v.x * merikomi; 
	//sph[0].pos.y -= sph[0].v.y * merikomi;
	//sph[0].pos.z -= sph[0].v.z * merikomi;

	//obj.pos.x += sph[0].v.x * merikomi;
	//obj.pos.y += sph[0].v.y * merikomi;
	//obj.pos.z += sph[0].v.z * merikomi;
}

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
	if (st_model_hit.MoveFlag == 1)
	{
		// 移動ベクトルを正規化したものをプレイヤーが向くべき方向として保存
		st_model_hit.TargetMoveDirection = VNorm(st_model_hit.movepos);
		/*DrawFormatString(100, 200, GetColor(255, 255, 255), " %.1f , %.1f , %.1f ", st_model_hit.TargetMoveDirection.x, st_model_hit.TargetMoveDirection.y, st_model_hit.TargetMoveDirection.z);*/
		// プレイヤーが向くべき方向ベクトルをプレイヤーのスピード倍したものを移動ベクトルとする
		st_model_hit.movepos = VScale(st_model_hit.TargetMoveDirection, sph[0].speed);


		/*DrawFormatString(100, 230, GetColor(255, 0, 0), "Vscale %.1f , %.1f , %.1f ", st_model_hit.movepos.x, st_model_hit.movepos.y, st_model_hit.movepos.z);*/
	}
	if (p_zmoveflg == true) {

		st_model_hit.movepos.z = st_model_hit.movepos.z + sph[0].zmove;
		
		if (st_model_hit.gmoveflg == false) {
			// カメラの角度に合わせて移動ベクトルを回転してから加算
			sinParam = (float)sin(cameraHAngle / 180.0f * DX_PI_F);
			cosParam = (float)cos(cameraHAngle / 180.0f * DX_PI_F);
			// 各ベクトルごとに計算yは放置

			TempMoveVector.x = st_model_hit.movepos.x * cosParam - st_model_hit.movepos.z * sinParam;
			TempMoveVector.y = 0.0f;
			TempMoveVector.z = st_model_hit.movepos.x * sinParam + st_model_hit.movepos.z * cosParam;

			st_model_hit.movepos = TempMoveVector;
		}
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
	st_model_hit.HitDim[0] = MV1CollCheck_Sphere(ground.handle, -1, sph[0].pos, PLAYER_ENUM_DEFAULT_SIZE + VSize(MoveVector));
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
	}

	
	sph[0].pos = st_model_hit.NowPos;
	
	MV1SetPosition(rock.handle, sph[0].pos);
	/*DrawSphere3D(sph[0].pos, sph[0].radius, 32, sph[0].color, GetColor(255, 255, 255), TRUE);*/
	// 検出したプレイヤーの周囲のポリゴン情報を開放する
	for (int i = 0; i < st_model_hit.HitDimNum; i++)
	{
		MV1CollResultPolyDimTerminate(st_model_hit.HitDim[i]);
	}
}

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

//プレイヤーの左右移動範囲を制限する
void Move_Limits()
{
	//球自体のX座標をもとに作る
	int lhit_magnification = 2;    //Xの移動範囲外にでた場合の戻す力の倍率
	//仮
	static VECTOR player_before_pos = VGet(0.0f, 0.0f, 0.0f);

	if (sph[0].pos.z < st_model_hit.branch_point[0] && sph[0].pos.y < 5470.0f) {
		//左右のどちらかの範囲外に移動しようとしたらフラグをtrueにする
		if ((sph[0].pos.x <= st_model_hit.glimits_verification[0] ||
			sph[0].pos.x >= st_model_hit.glimits_verification[1]) && st_model_hit.gmoveflg != true) {
			st_model_hit.gmoveflg = true;
			player_before_pos = sph[0].pos;
		}

		if (st_model_hit.gmoveflg == true) {
			//範囲内に戻す処理(左)
			if (sph[0].pos.x <= player_before_pos.x + sph[0].zmove * lhit_magnification && st_model_hit.landr_move == 1) {
				sph[0].pos.x += 10;
			}
			//範囲内に戻す処理(右)
			else if (sph[0].pos.x >= player_before_pos.x - sph[0].zmove * lhit_magnification && st_model_hit.landr_move == 2) {
				sph[0].pos.x -= 10;
			}
			//フラグをもとに戻す
			else {
				//sph[0].zmove = 0.0f;
				//sph[0].zaccl = 2.0f;
				st_model_hit.gmoveflg = false;
			}

		}
	}
}