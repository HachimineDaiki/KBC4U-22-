#include "Init.h"
#include "3Dmodel.h"
#include "Player.h"
void Sph_init() {
	//プレイヤーの初期化
	for (int i = 0; i < 2; i++) {
		sph[i].speed = 10.0f; //プレイヤー速度
		sph[i].radius = 200.0f;//プレイヤー半径
		sph[i].v0y = 0.0f; //プレイヤーY軸初速度
		sph[i].pos = VGet(100.0f, 468.0f, 1300.0f);//プレイヤー初期座標
		sph[i].color = GetColor(255, 255, 255);//プレイヤーカラー
		sph[i].zaccl = 2.0f;//プレイヤーz方向accelerator
		sph[i].zmove = 0.0f;//プレイヤーZ方向移動
		sph[i].control = 0.02f;//プレイヤー速度調整変数
		sph[i].hp = 100;//プレイヤー体力
	}
	
	sph[0].v = VGet(0.0f, 0.0f, 0.0f);//プレイヤーベクトル

}
//不法投棄初期化
void Obj_init(){
	obj.pos = VGet(-3000.0f, -20000.0f, 120000.0f);//不法投棄初期座標
	obj.radius = 400.0f;//不法投棄半径
	obj.color = GetColor(0, 255, 100);//不法投棄カラー
}
//当たったらダメ―ジを受ける障害物初期化
void Damege_Init() {
	for (int i = 0; i < E_DAMEGE;i++) {
		e_obj[i].radius = 500.0f;
		e_obj[i].color = GetColor(255, 255, 100);
	}

	//ダメージ初期座標
	e_obj[0].pos = VGet(27000.0f,-11351.0f,69486.0f);
	e_obj[1].pos = VGet(25555.0f,-12654.0f,76525.0f);
	e_obj[2].pos = VGet(27000.0f, -12654.0f, 76525.0f);
	e_obj[3].pos = VGet(11922.0f, -4477.0f, 29957.0f);
	e_obj[4].pos = VGet(20700.0f, -6489.0f, 41609.0f);
	e_obj[5].pos = VGet(24500.0f, -6489.0f, 42000.0f);
}

//減速エリア初期化
void Decelearia_init() {
	for (int i = 0; i < DECELEARIA_NUM; i++) {
		decelearia[i].radius = 500.0f;
		decelearia[i].color = GetColor(255, 0, 0);
		decelearia[i].v = VGet(0.0f, 0.0f, 0.0f);
	}
	
	//初期座標
	decelearia[0].pos = VGet(-1000.0f, -200.0f, 5000.0f);
	decelearia[1].pos = VGet(1000.0f, -200.0f, 5000.0f);
	decelearia[3].pos = VGet(100.0f, -1070.0f, 10000.0f);
	decelearia[4].pos = VGet(500.0f, -2000.0f, 15000.0f);
	decelearia[5].pos = VGet(-500.0f, -2000.0f, 15000.0f);
	decelearia[6].pos = VGet(-6695.0f, -3820.0f, 25958.0f);
	/*decelearia[7].pos = VGet(-6695.0f, -3820.0f,26400.0f);*/
	decelearia[8].pos = VGet(-20548.0f, -6289.0f, 40640.0f);
	decelearia[9].pos = VGet(-26253.0f, -10815.0f, 66417.0f);
	decelearia[10].pos = VGet(-25289.0f, -12677.0f, 76443.0f);
	decelearia[11].pos = VGet(-11387.0f, -16461.0f, 98970.0f);
}
//モデルの初期化
void Model_init() {
	//地面初期座標
	ground.x = 0.0f;
	ground.y = 0.0f;
	ground.z = 0.0f;

	//プレイヤー岩初期座標
	rock.x = 100.0f;
	rock.y = 5471.0f;
	rock.z = 20000.0f;
}