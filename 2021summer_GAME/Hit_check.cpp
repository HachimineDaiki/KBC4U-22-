#include <Dxlib.h>
#include <math.h>
#include "Hit_check.h"
#include "3Dmodel.h"
#include "Player.h"
#include "Camera.h"
#include "Init.h"

float p_vz = 0;
VECTOR frontpos = VGet(0.0,0.0,0.0);
VECTOR rightpos = VGet(0.0, 0.0, 0.0);
VECTOR leftpos = VGet(0.0, 0.0, 0.0);
struct STAGE
{
	int		ModelHandle;				// ステージのモデルハンドル
	int		CollObjBaseModelHandle;		// コリジョンモデルの派生元ハンドル
	int		CollObjModelHandle[STAGECOLLOBJ_MAXNUM];	// ステージに配置するコリジョンモデルのハンドル
	int		CollObjNum;				// ステージに配置しているコリジョンモデルの数
};

STAGE stg;

//当たった時プレイヤーに影響するHP
int Hit_player_speed(Sph player[], int obs_info) {
	int hp = 0;
	
	if (obs_info == L) {//大きい障害物
		//if (player[0].zmove >= 0 && player[0].zmove <= 60) {
		//	hp = obs_damege._30;
		//}
		//else if (player[0].zmove >= 61 && player[0].zmove <= 100) {
		//	hp = obs_damege._50;
		//}
		//else if (player[0].zmove >= 101) {
		//	hp = obs_damege._100;
		//}
		//else {
		//	hp = obs_damege._0;
		//}
		if (fabsf(player[0].zmove) >= 0 && fabsf(player[0].zmove) <= 30) {
			hp = obs_damege._0;
		}
		else if (fabsf(player[0].zmove) >= 31 && fabsf(player[0].zmove) <= 50) {
			hp = obs_damege._15;
		}
		else if (fabsf(player[0].zmove) >= 51 && fabsf(player[0].zmove) <= 70) {
			hp = obs_damege._30;
		}
		else if (fabsf(player[0].zmove) >= 71 && fabsf(player[0].zmove) <= 100) {
			hp = obs_damege._50;
		}
		else if (fabsf(player[0].zmove) >= 101 && fabsf(player[0].zmove) <= 120) {
			hp = obs_damege._75;
		}
		else if (fabsf(player[0].zmove) >= 121) {
			hp = obs_damege._100;
		}


	}
	else if(obs_info == M){//中障害物
		if (player[0].zmove >= 0 && player[0].zmove <= 60) {
			hp = obs_damege._15;
		}
		else if (player[0].zmove >= 61 && player[0].zmove <= 100) {
			hp = obs_damege._25;
		}
		else if (player[0].zmove >= 101) {
			hp = obs_damege._50;
		}
		else {
			hp = obs_damege._0;
		}
	}
	else {//小さい障害物
		hp = obs_damege._0;
	}

	return hp;
}
void Hit_badobject_helth(Sph player[], int obs_info, int i) {

	if (obs_info == L) {
		if (player[0].zmove >= 100) {
			DrawFormatString(0, 0, GetColor(0, 255, 255), "HIT_L");
			damege_aria[i].obj_flag = false;
			damege_aria[i].radius = 0;
			damege_aria[i].pos = VGet(1.0f, 1.0f, 1.0f);
		}
	}
	else if (obs_info == M) {
		if (player[0].zmove >= 50) {
			DrawFormatString(0, 0, GetColor(0, 255, 255), "HIT_M");
			damege_aria[i].obj_flag = false;
			damege_aria[i].radius = 0;
			damege_aria[i].pos = VGet(1.0f, 1.0f, 1.0f);
		}
	}
	else {
		if (player[0].zmove >= 10) {
			DrawFormatString(0, 0, GetColor(0, 255, 255), "HIT_S");
			damege_aria[i].obj_flag = false;
			damege_aria[i].radius = 0;
			damege_aria[i].pos = VGet(1.0f, 1.0f, 1.0f);
		}
	}
}
//どの障害物にあたったのか
int IsObs_check(Sph obs[], int i) {
	int obs_size = 0;//障害物のサイズを返す変数

	switch (obs[i].hit_name)//当たった障害物の名前を探す
	{
	case L:obs_size = L;//大きいサイズ
		break;
	case M:obs_size = M;//中サイズ
		break;
	case S:obs_size = S;//小さいサイズ
		break;
	}

	return obs_size;//障害物のサイズを返す
}

//球同士当たり判定
bool Sph_hit_check(Sph sp[], Sph ob) {
	sph[0].v.x = ob.pos.x - sp[0].pos.x;//x成分
	sph[0].v.y = ob.pos.y - sp[0].pos.y;//y成分
	sph[0].v.z = ob.pos.z - sp[0].pos.z;//z成分

	s_dis = sph[0].v.x * sph[0].v.x + sph[0].v.y * sph[0].v.y + sph[0].v.z * sph[0].v.z;//2点間の距離

	float radius_sum = (sp[0].radius + ob.radius) * (sp[0].radius + ob.radius); //半径の和
	return s_dis < radius_sum ? true : false;//2点間の距離が半径の和より小さければ当たっていると判定
}

//ダメージエリア
bool Sph_ehit_chech(Sph sp[], Sph _damege_aria[], int i) {
	damege_aria[i].v.x = _damege_aria[i].pos.x - sp[0].pos.x;//x成分
	damege_aria[i].v.y = _damege_aria[i].pos.y - sp[0].pos.y;//y成分
	damege_aria[i].v.z = _damege_aria[i].pos.z - sp[0].pos.z;//z成分

	damege_aria[i].dis = damege_aria[i].v.x * damege_aria[i].v.x + damege_aria[i].v.y * damege_aria[i].v.y + damege_aria[i].v.z * damege_aria[i].v.z;//2点間の距離
	damege_aria[i].radius_sum = (sp[0].radius + damege_aria[i].radius) * (sp[0].radius + damege_aria[i].radius); //半径の和
	
	bool hit;//当たったのか返す用

	//ダメージエリアに入っているかチェック
	if (damege_aria[i].dis < damege_aria[i].radius_sum) {
		hit = true;//当たった。
		damege_aria[i].hit_name = damege_aria[i].name;//当たったダメージエリアの名前を入れる。
		damege_aria[i].hit_speed = sph[0].zmove;//当たった時のプレイヤーの速度を入れる。
		P_hp(IsObs_check(damege_aria, i));//当たったダメージエリアのサイズでHP減少。
		Hit_badobject_helth(sph, IsObs_check(damege_aria, i), i);
	}
	else
	{
		hit = false;//当たっていない。
	}

	return hit;//当たっているか情報を返す。
}
//減速エリアのチェック判定処理
bool Decel_aria_check(Sph sp[], Sph decele[], int i) {
	decele_aria[i].v.x = decele[i].pos.x - sp[0].pos.x;
	decele_aria[i].v.y = decele[i].pos.y - sp[0].pos.y;
	decele_aria[i].v.z = decele[i].pos.z - sp[0].pos.z;

	decele_aria[i].dis = decele_aria[i].v.x * decele_aria[i].v.x + decele_aria[i].v.y * decele_aria[i].v.y + decele_aria[i].v.z * decele_aria[i].v.z;
	decele_aria[i].radius_sum = (decele[i].radius + sp[0].radius) * (decele[i].radius + sp[0].radius);
	return decele_aria[i].dis < decele_aria[i].radius_sum ? true : false;
}


//減速速度処理
void Decel_aria_effect(){

	//if (sph[0].zmove > 10) {
	//	sph[0].zmove *= 0.93f;
	//}else if (-10 > sph[0].zmove) {
	//	sph[0].zmove *= 0.93f;
	//}

	sph[0].zmove *= 0.97f;
	//if (g_frontflg == 0) {
	//	if (sph[0].zmove < 10) {
	//		sph[0].zmove = 10;
	//	}
	//}
	//if (g_frontflg == 1) {
	//	if (sph[0].zmove > -10) {
	//		sph[0].zmove = -10;
	//	}
	//}


	//if (g_frontmoveflg == 1) {
	//	if ((sph[0].zmove >= -15) && (sph[0].zmove <= 0)) {
	//		sph[0].zmove = -15;
	//	}
	//}
	//if (g_frontmoveflg == 0) {
	//	if ((sph[0].zmove <= 15) && (sph[0].zmove >= 0)) {
	//		sph[0].zmove = 15;
	//	}
	//}

}

//ダメージエリア　減速処理
void Damege_aria_Decele() {
	sph[0].zmove *= 0.7f;
}

//球と球の当たり判定を検知した後の処理
//void Sph_hit(float dis) {
//	float len = sqrtf(dis);
//	float radius_sum = sph[0].radius + obj.radius;
//	float merikomi = radius_sum - len;
//
//	if (len > 0) len = 1 / len;
//
//	sph[0].v.x *= len;
//	sph[0].v.y *= len;
//	sph[0].v.z *= len;
//
//	merikomi /= 2.0f;
//
//	//めり込み修正
//	sph[0].pos.x -= sph[0].v.x * merikomi; 
//	sph[0].pos.y -= sph[0].v.y * merikomi;
//	sph[0].pos.z -= sph[0].v.z * merikomi;
//
//	//obj.pos.x += sph[0].v.x * merikomi;
//	//obj.pos.y += sph[0].v.y * merikomi;
//	//obj.pos.z += sph[0].v.z * merikomi;
//}

void Sph_ehit(float dis , int i) {
	float len = sqrtf(dis);
	float radius_sum = sph[0].radius + obj.radius;
	float merikomi = radius_sum - len;

	if (len > 0) len = 1 / len;

	sph[0].v.x *= len;
	sph[0].v.y *= len;
	sph[0].v.z *= len;

	merikomi /= 2.0f;

	//めり込み修正
	sph[0].pos.x -= sph[0].v.x * merikomi;
	sph[0].pos.y -= sph[0].v.y * merikomi;
	sph[0].pos.z -= sph[0].v.z * merikomi;
//	float len = sqrtf(dis);
//	float radius_sum = sph[0].radius + damege_aria[i].radius;
//	float merikomi = radius_sum - len;
//
//	if (len > 0) len = 1 / len;
//
//	sph[0].v.x *= len;
//	sph[0].v.y *= len;
//	sph[0].v.z *= len;
//
//	merikomi /= 2.0f;
//
//	//sph[0].pos.x -= sph[i].v.x * merikomi;
//	//sph[0].pos.y -= sph[i].v.y * merikomi/* - 800*/;
//	//sph[0].pos.z -= sph[i].v.z * merikomi/* + 1600*/;
//
//	//sph[0].v.x += damege_aria[i].v.x * merikomi;
//	//sph[0].v.y += damege_aria[i].v.y * merikomi;
//	//sph[0].v.z += damege_aria[i].v.z * merikomi;
//
//	/*_damege_aria.pos.x += sph[0].v.x * merikomi;
//	_damege_aria.pos.y += sph[0].v.y * merikomi;
//	_damege_aria.pos.z += sph[0].v.z * merikomi;*/
}

void Ground_model_hit() {
	st_model_hit.movepos = VGet(0.0f, 0.0f,0.0f);//移動ベクトル
	st_model_hit.moveflag = 0;// 移動したかどうかのフラグを初期状態では「移動していない」を表す０にする

	P_input_move();//プレイヤー入力
	P_move();
	//地面についていなかったら重力発生
	//if (!st_model_hit.groundflg) {
	//	Sph_Gravity();//重力
	//}
	Sph_Gravity();//重力
	// 移動ボタンが押されたかどうかで処理を分岐
	if (st_model_hit.moveflag == 1)
	{
		// 移動ベクトルを正規化したものをプレイヤーが向くべき方向として保存
		st_model_hit.targetmovedirection = VNorm(st_model_hit.movepos);
		/*DrawFormatString(100, 200, GetColor(255, 255, 255), " %.1f , %.1f , %.1f ", st_model_hit.TargetMoveDirection.x, st_model_hit.TargetMoveDirection.y, st_model_hit.TargetMoveDirection.z);*/
		// プレイヤーが向くべき方向ベクトルをプレイヤーのスピード倍したものを移動ベクトルとする
		st_model_hit.movepos = VScale(st_model_hit.targetmovedirection, sph[0].speed);
	}
	//if (p_zmoveflg == true) {

		st_model_hit.movepos.z = st_model_hit.movepos.z + sph[0].zmove;

		// カメラの角度に合わせて移動ベクトルを回転してから加算
		g_sinParam = (float)sin(g_p_direct / 180.0f * DX_PI_F);
		g_cosParam = (float)cos(g_p_direct / 180.0f * DX_PI_F);
		//岩の向いている方向の計算(目の前が坂かどうかを判断するのに使う)
		TempMoveVector.x = st_model_hit.movepos.x * g_cosParam - sph[0].front * g_sinParam;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = st_model_hit.movepos.x * g_sinParam + sph[0].front * g_cosParam;

		g_frontVector = TempMoveVector;

		TempMoveVector.x = (st_model_hit.movepos.x + sph[0].right) * g_cosParam - st_model_hit.movepos.z * g_sinParam;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = (st_model_hit.movepos.x + sph[0].right) * g_sinParam + st_model_hit.movepos.z * g_cosParam;

		g_rightVector =  TempMoveVector;

		TempMoveVector.x = (st_model_hit.movepos.x + sph[0].left) * g_cosParam - st_model_hit.movepos.z * g_sinParam;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = (st_model_hit.movepos.x + sph[0].left) * g_sinParam + st_model_hit.movepos.z * g_cosParam;

		g_leftVector = TempMoveVector;
		// 各ベクトルごとに計算yは放置

		TempMoveVector.x = st_model_hit.movepos.x * g_cosParam - st_model_hit.movepos.z * g_sinParam;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = st_model_hit.movepos.x * g_sinParam + st_model_hit.movepos.z * g_cosParam;

		st_model_hit.movepos = TempMoveVector;
	//}

	Ground_model_hit_check(st_model_hit.movepos);
}
void Ground_model_hit_check(VECTOR MoveVector) {
	// 移動前の座標を保存
	st_model_hit.oldpos = sph[0].pos;
	// 移動後の座標を算出
	st_model_hit.nowpos = VAdd(sph[0].pos, MoveVector);
	frontpos = VAdd(sph[0].pos, g_frontVector);
	rightpos = VAdd(sph[0].pos, g_rightVector);
	leftpos = VAdd(sph[0].pos, g_leftVector);
	HITRESULT_LINE rightposhit;
	HITRESULT_LINE leftposhit;
	stg.CollObjNum = 1;

	 //プレイヤーの周囲にあるステージポリゴンを取得する
	 //( 検出する範囲は移動距離も考慮する )
	st_model_hit.hitdim[0] = MV1CollCheck_Sphere(ground.handle, -1, sph[0].pos, PLAYER_ENUM_DEFAULT_SIZE + VSize(MoveVector));

	// プレイヤーの周囲にあるコリジョンオブジェクトのポリゴンも取得する
	//for (int i = 0; i < stg.CollObjNum; i++)
	//{
	//	st_model_hit.hitdim[i + 1] = MV1CollCheck_Sphere(stg.CollObjModelHandle[i], -1, sph[0].pos, PLAYER_ENUM_DEFAULT_SIZE + VSize(MoveVector));
	//}

	

	// HitDim の有効な数はコリジョンオブジェクトの数とステージ自体のコリジョン
	//HitDimの配列要素
	st_model_hit.hitdimnum = stg.CollObjNum + 1;
	// x軸かy軸方向に 0.01f 以上移動した場合は「移動した」フラグを１にする
	if (fabs(MoveVector.x) > 0.01f || fabs(MoveVector.z) > 0.01f)
	{
		st_model_hit.moveflag = 1;
	}
	else
	{
		st_model_hit.moveflag = 0;
	}

	// 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断する
	{
		// 壁ポリゴンと床ポリゴンの数を初期化する
		st_model_hit.kabenum = 0;
		st_model_hit.yukanum = 0;

		// 検出されたポリゴンの数だけ繰り返し
		for (int j = 0; j < st_model_hit.hitdimnum; j++) //2回回る。
		{
			for (int i = 0; i < st_model_hit.hitdim[j].HitNum; i++)//ヒットしたポリゴンの数分回る
			{
				
				// ＸＺ平面に垂直かどうかはポリゴンの法線のＹ成分が０に限りなく近いかどうかで判断する
				if (st_model_hit.hitdim[j].Dim[i].Normal.y < 0.9f && st_model_hit.hitdim[j].Dim[i].Normal.y > -0.9f)
				{
					//	 壁ポリゴンと判断された場合でも、プレイヤーのＹ座標＋１．０ｆより高いポリゴンのみ当たり判定を行う
					//if (st_model_hit.hitdim[j].Dim[i].Position[0].y > sph[0].pos.y + 1.0f ||
					//	st_model_hit.hitdim[j].Dim[i].Position[1].y > sph[0].pos.y + 1.0f ||
					//	st_model_hit.hitdim[j].Dim[i].Position[2].y > sph[0].pos.y + 1.0f)
					//{
						//		 ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
						if (st_model_hit.kabenum < PLAYER_MAX_HITCOLL)
						{
							//			 ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
							st_model_hit.kabe[st_model_hit.kabenum] = &st_model_hit.hitdim[j].Dim[i];

							//			 壁ポリゴンの数を加算する
							st_model_hit.kabenum++;
						}
					//}
				}
				else
				{
				//	 ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
					if (st_model_hit.yukanum < PLAYER_MAX_HITCOLL)
					{
				//		 ポリゴンの構造体のアドレスを床ポリゴンポインタ配列に保存する
						st_model_hit.yuka[st_model_hit.yukanum] = &st_model_hit.hitdim[j].Dim[i];

				//		 床ポリゴンの数を加算する
						st_model_hit.yukanum++;
						DrawFormatString(100, 20, GetColor(255, 0, 0), "kabenum %d", st_model_hit.yukanum);
					}
				}
			}
		}
	}
	//ここから壁
	// 壁ポリゴンとの当たり判定処理
	if (st_model_hit.kabenum != 0)
	{
		// 壁に当たったかどうかのフラグは初期状態では「当たっていない」にしておく
		st_model_hit.hitflag = 0;

		// 移動したかどうかで処理を分岐
		if (st_model_hit.moveflag == 1)
		{
			// 壁ポリゴンの数だけ繰り返し
			for (int i = 0; i < st_model_hit.kabenum; i++)
			{
				// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
				st_model_hit.poly = st_model_hit.kabe[i];

				// ポリゴンとプレイヤーが当たっていなかったら次のカウントへ
				/*if (HitCheck_Capsule_Triangle(st_model_hit.nowpos, VAdd(st_model_hit.nowpos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]) == FALSE) continue;*/
				if (HitCheck_Sphere_Triangle(st_model_hit.nowpos, sph[0].radius + 10, st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]) == FALSE) continue;
				//HitCheck_Sphere_Triangle(VECTOR   SphereCenterPos, float  SphereR, VECTOR   TrianglePos1, VECTOR   TrianglePos2, VECTOR   TrianglePos3);									// 球と三角形の当たり判定( TRUE:当たっている  FALSE:当たっていない )
				
				// ここにきたらポリゴンとプレイヤーが当たっているということなので、ポリゴンに当たったフラグを立てる
				st_model_hit.hitflag = 1;

				//壁に当たったら壁に遮られない移動成分分だけ移動する
				{
					VECTOR SlideVec;	// プレイヤーをスライドさせるベクトル

					// 進行方向ベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出
					SlideVec = VCross(MoveVector, st_model_hit.poly->Normal);

					// 算出したベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出、これが
					// 元の移動成分から壁方向の移動成分を抜いたベクトル
					SlideVec = VCross(st_model_hit.poly->Normal, SlideVec);

					//跳ね返りの判定
					if (((g_cameraHAngle > 15 && g_cameraHAngle < 135 && g_cameraHAngle != 90) ||
						(g_cameraHAngle < -15 && g_cameraHAngle > -135 && g_cameraHAngle != -90)) 
						&& st_model_hit.kabeHitflg == false && g_frontflg != 1 && sph[0].zmove > 70) {

						//スピードを半分にする
						if (sph[0].zmove > 15) {
							sph[0].zmove /= 2;
						}

						//角度を逆にしてそれを半分にする
						g_p_direct = (g_p_direct * -1) / 2;
						g_WallHitFlag = 1;
					}

					// それを移動前の座標に足したものを新たな座標とする
					st_model_hit.nowpos = VAdd(st_model_hit.oldpos, SlideVec);

					st_model_hit.kabeHitflg = true;
				}

				int j;
				// 新たな移動座標で壁ポリゴンと当たっていないかどうかを判定する
				for (j = 0; j < st_model_hit.kabenum; j++)
				{
					// j番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					st_model_hit.poly = st_model_hit.kabe[j];

					// 当たっていたらループから抜ける
					if (HitCheck_Sphere_Triangle(st_model_hit.nowpos, sph[0].radius + 10, st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]) == TRUE) break;
				}

				// j が KabeNum だった場合はどのポリゴンとも当たらなかったということなので
				// 壁に当たったフラグを倒した上でループから抜ける
				if (j == st_model_hit.kabenum)
				{
					st_model_hit.hitflag = 0;
					break;
				}
			}
		}
		else
		{
			// 移動していない場合の処理

			// 壁ポリゴンの数だけ繰り返し
			for (int i = 0; i < st_model_hit.kabenum; i++)
			{
				// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
				st_model_hit.poly = st_model_hit.kabe[i];

				// ポリゴンに当たっていたら当たったフラグを立てた上でループから抜ける
				if (HitCheck_Sphere_Triangle(st_model_hit.nowpos, sph[0].radius + 10, st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]) == TRUE)
				{
					st_model_hit.hitflag = 1;
					break;
				}
			}
		}
		// 壁に当たっていたら壁から押し出す処理を行う
		if (st_model_hit.hitflag == 1)
		{
			// 壁からの押し出し処理を試みる最大数だけ繰り返し
			for (int k = 0; k < PLAYER_HIT_TRYNUM; k++)
			{
				// 壁ポリゴンの数だけ繰り返し
				for (st_model_hit.i = 0; st_model_hit.i < st_model_hit.kabenum; st_model_hit.i++)
				{
					// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					st_model_hit.poly = st_model_hit.kabe[st_model_hit.i];

					// プレイヤーと当たっているかを判定
					if (HitCheck_Sphere_Triangle(st_model_hit.nowpos, sph[0].radius + 10, st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]) == FALSE) continue;

					// 当たっていたら規定距離分プレイヤーを壁の法線方向に移動させる
					st_model_hit.nowpos = VAdd(st_model_hit.nowpos, VScale(st_model_hit.poly->Normal, PLAYER_HIT_SLIDE_LENGTH));

					// 移動した上で壁ポリゴンと接触しているかどうかを判定
					for (st_model_hit.j = 0; st_model_hit.j < st_model_hit.kabenum; st_model_hit.j++)
					{
						// 当たっていたらループを抜ける
						st_model_hit.poly = st_model_hit.kabe[st_model_hit.j];
						if (HitCheck_Sphere_Triangle(st_model_hit.nowpos, sph[0].radius + 10, st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]) == TRUE) break;
					}

					// 全てのポリゴンと当たっていなかったらここでループ終了
					if (st_model_hit.j == st_model_hit.kabenum) break;
				}

				// i が KabeNum ではない場合は全部のポリゴンで押し出しを試みる前に全ての壁ポリゴンと接触しなくなったということなのでループから抜ける
				if (st_model_hit.i != st_model_hit.kabenum) break;
			}
		}
	}
	else
	{
		st_model_hit.kabeHitflg = false;
	}


	// 床ポリゴンとの当たり判定
	if (st_model_hit.yukanum != 0)
	{


		float maxy;

		// 下降中かジャンプ中ではない場合の処理

		// 床ポリゴンに当たったかどうかのフラグを倒しておく
		st_model_hit.hitflag = 0;

		// 一番高い床ポリゴンにぶつける為の判定用変数を初期化
		maxy = 0.0f;

		// 床ポリゴンの数だけ繰り返し
		for (int i = 0; i < st_model_hit.yukanum; i++)
		{
			// i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
			st_model_hit.poly = st_model_hit.yuka[i];


			// 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
			/*st_model_hit.LineRes = HitCheck_Line_Triangle(VAdd(st_model_hit.NowPos, VGet(0.0f, 0.0f, 0.0f)), VAdd(st_model_hit.NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), st_model_hit.Poly->Position[0], st_model_hit.Poly->Position[1], st_model_hit.Poly->Position[2]);*/
			st_model_hit.lineres = HitCheck_Line_Triangle(st_model_hit.nowpos, VAdd(st_model_hit.nowpos, VGet(0.0f, -200.0f, 0.0f)), st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]);

			g_frontpos2 = HitCheck_Line_Triangle(frontpos,VAdd(frontpos,VGet(0.0f,-200.0f,0.0f)), st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]);
			rightposhit = HitCheck_Line_Triangle(rightpos, VAdd(rightpos, VGet(0.0f, -200.0f, 0.0f)), st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]);
			leftposhit = HitCheck_Line_Triangle(leftpos, VAdd(leftpos, VGet(0.0f, -200.0f, 0.0f)), st_model_hit.poly->Position[0], st_model_hit.poly->Position[1], st_model_hit.poly->Position[2]);


			
			if (st_model_hit.lineres.Position.y > g_frontpos2.Position.y) {
				g_frontflg = 0;//プレイヤーの位置が高かったら前に坂があるフラグを0にする
			}
			else if (st_model_hit.lineres.Position.y < g_frontpos2.Position.y) {
				g_frontflg = 1;//プレイヤーの位置とちょっと前の位置を比較してプレイヤーの位置の方が小さかったら前に坂があるフラグを1にする
			}
			if (g_frontpos2.Position.y > rightposhit.Position.y) {
				g_rightflg = 0;
			}
			else if (g_frontpos2.Position.y < rightposhit.Position.y) {
				g_rightflg = 1;
				g_p_direct += 0.25f;
			}
			if (g_frontpos2.Position.y > leftposhit.Position.y) {
				g_leftflg = 0;
			}
			else if (g_frontpos2.Position.y < leftposhit.Position.y) {
				g_leftflg = 1;
				g_p_direct -= 0.25f;
			}



			if (st_model_hit.lineres.HitFlag == FALSE) { 
				
				continue; 
			}
			//ここまでやった
			
			// 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
			if (st_model_hit.hitflag == 1 && maxy > st_model_hit.lineres.Position.y) continue;

			// ポリゴンに当たったフラグを立てる
			st_model_hit.hitflag = 1;
			// 接触したＹ座標を保存する
			maxy = st_model_hit.lineres.Position.y + sph[0].radius;
			/*DrawFormatString(100, 240, GetColor(255, 0, 0), " Line.Y %d", st_model_hit.LineRes.Position.y);*/
			st_model_hit.groundflg = true; //地面についたフラグを立てる
		}
		///DrawFormatString(450, 40, GetColor(255, 255, 255), "[smhx %.0f] [smhy %.0f] [smhz %.0f]", rightposhit.Position.x, rightposhit.Position.y, rightposhit.Position.z);
		///DrawFormatString(450, 60, GetColor(255, 255, 255), "[g_frox %.0f] [g_froy %.0f] [g_froz %.0f]", leftposhit.Position.x, leftposhit.Position.y, leftposhit.Position.z);

		///DrawLine3D(rightposhit.Position, VAdd(rightposhit.Position, VGet(0.0f, -300.0f, 0.0f)), GetColor(255, 255, 0));
		///DrawLine3D(leftposhit.Position, VAdd(leftposhit.Position, VGet(0.0f, -300.0f, 0.0f)), GetColor(255, 255, 0));
		////DrawLine3D(st_model_hit.nowpos, VAdd(st_model_hit.nowpos,VGet(0.0f,600.f,0.0f)), GetColor(255, 0, 0));
		////DrawLine3D(frontpos, VAdd(frontpos, VGet(0.0f, -300.0f, 0.0f)), GetColor(255, 255, 0));
		////DrawLine3D(g_frontVector, VAdd(g_frontVector, VGet(0.0f, -200.0f, 0.0f)), GetColor(255, 0, 0));
		//DrawLine3D(VAdd(st_model_hit.nowpos, VGet(-300.0f, -110.0f, 0.0f)), VAdd(st_model_hit.nowpos, VGet(300.0f, -200.0f, 0.0f)), GetColor(255, 0, 0));
		//DrawLine3D(VAdd(st_model_hit.nowpos, VGet(0.0f, -110.0f, -300.0f)), VAdd(st_model_hit.nowpos, VGet(0.0f, -200.0f, 300.0f)), GetColor(255, 0, 0));
		//// 岩の周囲を簡易的に見る線
		//DrawLine3D(VAdd(st_model_hit.nowpos, VGet(-300.0f, 0.0f, 0.0f)), VAdd(st_model_hit.nowpos, VGet(300.0f, 0.0f, 0.0f)), GetColor(255, 0, 0));
		//DrawLine3D(VAdd(st_model_hit.nowpos, VGet(0.0f, 0.0f, -300.0f)), VAdd(st_model_hit.nowpos, VGet(0.0f, 0.0f, 300.0f)), GetColor(255, 0, 0));
		// 床ポリゴンに当たったかどうかで処理を分岐
		if (st_model_hit.hitflag == 1)
		{
			// 当たった場合

			// 接触したポリゴンで一番高いＹ座標をプレイヤーのＹ座標にする
			st_model_hit.nowpos.y = maxy;
		}

	}



	
	sph[0].pos = st_model_hit.nowpos;
	
	MV1SetPosition(rock[rock[0].handle_num].handle, sph[0].pos);//プレイヤーモデル描画

	/*DrawSphere3D(sph[0].pos, sph[0].radius, 32, sph[0].color, GetColor(255, 255, 255), TRUE);*/
	// 検出したプレイヤーの周囲のポリゴン情報を開放する
	for (int i = 0; i < st_model_hit.hitdimnum; i++)
	{
		MV1CollResultPolyDimTerminate(st_model_hit.hitdim[i]);
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
