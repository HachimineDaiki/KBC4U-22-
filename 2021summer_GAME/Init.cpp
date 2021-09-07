#include "Init.h"
#include "3Dmodel.h"
#include "Player.h"
#include"Hit_check.h"
#include"User_Interface.h"
#include"Camera.h"
void Sph_init() {
	//プレイヤーの初期化
	for (int i = 0; i < 2; i++) {
		sph[0].speed = 10.0f; //プレイヤー速度
		sph[0].radius = 200.0f;//プレイヤー半径
		sph[0].v0y = 0.0f; //プレイヤーY軸初速度
		sph[0].pos = VGet(100.0f, 468.0f, 1300.0f);//プレイヤー初期座標
		sph[0].color = GetColor(255, 255, 255);//プレイヤーカラー
		sph[0].zaccl = 2.0f;//プレイヤーz方向accelerator
		sph[0].zmove = 0.0f;//プレイヤーZ方向移動
		sph[0].control = 0.02f;//プレイヤー速度調整変数
		sph[0].hp = 300;//プレイヤー体力
		sph[0].front = 200;//プレイヤーの前方500
	}
	
	sph[0].v = VGet(0.0f, 0.0f, 0.0f);//プレイヤーベクトル
	g_frontflg = 0;//前に坂があるかどうかの初期化
	g_CollisionReflectionFlag = 0;//0 衝突して反射していない 1 衝突して反射している
	p_zmoveflg = false;

	sph[0].direction = VGet(0, 0, 1);//プレイヤの向いて方向 初期 z方向
}

//不法投棄初期化
void Obj_init(){
	obj.pos = VGet(-170.0f, -21160.0f, 132270.0f);//不法投棄初期座標
	obj.radius = 400.0f;//不法投棄半径
	obj.color = GetColor(0, 255, 100);//不法投棄カラー
	obj.zmove = 1;
}
//当たったらダメ―ジを受ける障害物初期化
void Damege_Init() {
	for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
		//if (i >= 0 && i <= 2) {
		//	damege_aria[i].radius = 100.0f;
		//	damege_aria[i].color = GetColor(255, 0, 0);
		//	damege_aria[i].name = S;//障害物の大きさS
		//	damege_aria[i].hp = 10;//test用の体力
		//	damege_aria[i].obj_flag = true;
		//}
		//if (i >= 0 && i <= 5) {
		//	damege_aria[i].radius = 200.0f;
		//	damege_aria[i].color = GetColor(255, 255, 0);
		//	damege_aria[i].name = L;//障害物の大きさM
		//	damege_aria[i].hp = 50;//test用の体力
		//	damege_aria[i].obj_flag = true;
		//}
		//else {
		//	damege_aria[i].radius = 400.0f;
		//	damege_aria[i].color = GetColor(0, 255, 0);
		//	damege_aria[i].name = L;//障害物の大きさL
		//	damege_aria[i].hp = 100;//test用の体力
		//	damege_aria[i].obj_flag = true;
		//}

		damege_aria[i].radius = 600.0f;
		damege_aria[i].color = GetColor(0, 255, 0);
		damege_aria[i].name = L;//障害物の大きさL
		damege_aria[i].hp = 100;//test用の体力
		damege_aria[i].obj_flag = true;

			//ダメージエリア初期座標
			damege_aria[0].pos = VGet(4230.0f, -3260.0f, 21370.0f);
			damege_aria[1].pos = VGet(3330.0f, -3260.0f, 22070.0f);
			damege_aria[2].pos = VGet(9980.0f, -4410.0f, 30020.0f);
			damege_aria[3].pos = VGet(11009.0f, -4372.0f, 29354.0f);
			damege_aria[4].pos = VGet(12930.0f, -5460.0f, 35820.0f);
			damege_aria[5].pos = VGet(13830.0f, -5460.0f, 35120.0f);
			damege_aria[6].pos = VGet(14580.0f, -5460.0f, 34170.0f);
			damege_aria[7].pos = VGet(22830.0f, -10360.0f, 61170.0f);
			damege_aria[8].pos = VGet(24330.0f, -10460.0f, 61170.0f);
			damege_aria[9].pos = VGet(25830.0f, -10560.0f, 61170.0f);
			damege_aria[10].pos = VGet(12130.0f, -5660.0f, 36470.0f);
			damege_aria[11].pos = VGet(21330.0f, -6960.0f, 42570.0f);
			damege_aria[12].pos = VGet(20530.0f, -6860.0f, 42970.0f);
			damege_aria[13].pos = VGet(29330.0f, -11260.0f, 64470.0f);
			damege_aria[14].pos = VGet(28030.0f, -11260.0f, 64770.0f);
			damege_aria[15].pos = VGet(30730.0f, -13460.0f, 76670.0f);
			damege_aria[16].pos = VGet(29580.0f, -13460.0f, 76670.0f);
			damege_aria[17].pos = VGet(28230.0f, -13460.0f, 76670.0f);
			damege_aria[18].pos = VGet(27130.0f, -13460.0f, 76670.0f);
			damege_aria[19].pos = VGet(25830.0f, -13460.0f, 76670.0f);
			damege_aria[20].pos = VGet(21530.0f, -14860.0f, 84270.0f);
			damege_aria[21].pos = VGet(20730.0f, -14860.0f, 85270.0f);
			damege_aria[22].pos = VGet(8830.0f, -16960.0f, 99670.0f);
			damege_aria[23].pos = VGet(16830.0f, -15460.0f, 89070.0f);
			damege_aria[24].pos = VGet(6630.0f, -18010.0f, 108020.0f);
			damege_aria[25].pos = VGet(2230.0f, -19610.0f, 118920.0f);
			damege_aria[26].pos = VGet(-1420.0f, -19610.0f, 118920.0f);
			damege_aria[27].pos = VGet(-4120.0f, -19660.0f, 119420.0f);
			damege_aria[28].pos = VGet(22130.0f, -14560.0f, 83570.0f);
			damege_aria[29].pos = VGet(17580.0f, -15310.0f, 87920.0f);
			damege_aria[30].pos = VGet(15980.0f, -15660.0f, 89970.0f);
			damege_aria[31].pos = VGet(12580.0f, -16210.0f, 94420.0f);
			//未入力
			damege_aria[32].pos = VGet(12180.0f, -16160.0f, 95270.0f);
			damege_aria[33].pos = VGet(9480.0f, -16810.0f, 98620.0f);
			damege_aria[34].pos = VGet(8230.0f, -17110.0f, 100420.0f);

			damege_aria[35].pos = VGet(-14190.0f, -4433.0f, 28859.0f);
			damege_aria[36].pos = VGet(-3937.0f, -4289.0f, 29849.0f);
			damege_aria[37].pos = VGet(-4598.0f, -4199.0f, 28829.0f);

			
			damege_aria[38].pos = VGet(-10004.0f, -4982.0f, 32989.0f);
			damege_aria[39].pos = VGet(-27877.0f, -7122.0f, 43730.0f);
			
			damege_aria[40].pos = VGet(-17661.0f, -14017.0f, 83622.0f);
			damege_aria[41].pos = VGet(-18472.0f, -5326.0f, 34370.0f);

			damege_aria[42].pos = VGet(-26595.0f, -9633.0f, 59294.0f);
			damege_aria[43].pos = VGet(-29484.0f, -12506.0f, 75512.0f);

			damege_aria[44].pos = VGet(-18972.0f, -14799.0f, 88910.0f);
			damege_aria[45].pos = VGet(-10160.0f, -16186.0f, 96576.0f);

			MV1SetRotationXYZ(e_rock[i].handle, VGet(5 * DX_PI_F / 180.0f, 0.0f, 0.0));
	}
}

//減速エリア初期化
void Decelearia_init() {
	for (int i = 0; i < DECELE_ARIA_MAX; i++) {
		decele_aria[i].radius = 1100.0f;
		decele_aria[i].color = GetColor(255, 0, 0);
		decele_aria[i].v = VGet(0.0f, 0.0f, 0.0f);

		MV1SetRotationXYZ(gensoku[i].handle, VGet(5 * DX_PI_F / 180.0f, 0.0f, 0.0));
	}
	
	//初期座標
	//decele_aria[0].pos = VGet(-1000.0f, -300.0f, 5000.0f);
	//decele_aria[1].pos = VGet(1000.0f, -300.0f, 5000.0f);

	decele_aria[2].pos = VGet(100.0f, -1170.0f, 10000.0f);
	decele_aria[3].pos = VGet(500.0f, -2100.0f, 15000.0f);

	
	decele_aria[13].pos = VGet(22380.0f, -8160.0f, 51620.0f);
	decele_aria[14].pos = VGet(24430.0f, -8360.0f, 51620.0f);
	decele_aria[15].pos = VGet(22430.0f, -14860.0f, 86670.0f);
	decele_aria[16].pos = VGet(15030.0f, -15310.0f, 88720.0f);
	decele_aria[17].pos = VGet(14830.0f, -16310.0f, 95920.0f);
	decele_aria[18].pos = VGet(8080.0f, -16510.0f, 96670.0f);
	//左
	decele_aria[4].pos = VGet(-500.0f, -2100.0f, 15000.0f);
	decele_aria[5].pos = VGet(-6695.0f, -3820.0f, 25958.0f);
	decele_aria[6].pos = VGet(-20548.0f, -6289.0f, 40640.0f);
	decele_aria[7].pos = VGet(-26253.0f, -10815.0f, 66417.0f);
	decele_aria[8].pos = VGet(-25289.0f, -12677.0f, 76443.0f);

	decele_aria[9].pos = VGet(-11387.0f, -16461.0f, 98970.0f);
	decele_aria[10].pos = VGet(-2710.0f, -19610.0f, 118830.0f);
	decele_aria[11].pos = VGet(-170.0f, -20100.0f, 122550.0f);
	decele_aria[12].pos = VGet(-16130.0f, -4810.0f, 30470.0f);

	//未入力
	//decele_aria[19].pos = VGet(6630.0f, 18010.0f, 108020.0f);
	//decele_aria[20].pos = VGet(-25289.0f, -12777.0f, 76443.0f);
	//decele_aria[21].pos = VGet(-11387.0f, -16561.0f, 98970.0f);
	//decele_aria[22].pos = VGet(-2710.0f, -19610.0f, 118830.0f);
	//decele_aria[23].pos = VGet(-170.0f, -20090.0f, 122550.0f);
}

//モデルの初期化
void Model_init() {
	//地面初期座標
	ground.x = 0.0f;
	ground.y = 0.0f;
	ground.z = 0.0f;

	//壁の初期座標
	wall[0].x = -2000.0f;
	wall[0].y = -1000.0f;
	wall[0].z = 8000.0f;

	wall[1].x = 2000.0f;
	wall[1].y = -1000.0f;
	wall[1].z = 8000.0f;

	//プレイヤー岩初期座標
	//rock[0].x = 100.0f;
	//rock[0].y = 5471.0f;
	//rock[0].z = 20000.0f;
}

void All_Init() {
	g = 9.81;
	p_zmoveflg = true;
	htdrow.hitflg = false;
	rock[0].handle_num = 0;
	effect_time.count = 0;
	goal_input_space = false;
	Sph_init();//球の初期化
	Obj_init();//不法投棄物の初期化
	Damege_Init();//障害物の初期化
	Decelearia_init();//減速エリア初期化
	Model_init();//モデル初期化
	Camera_set();//カメラセット
	Model3d_init();//3Dモデル初期化
	UIinit();//UIの初期化
	PlanetInit();
	haikeiflg = false;
}
void PlanetInit() {
	planet[0].radius = 3474;//月
	planet[1].radius = 12104;//金星
	planet[2].radius = 4879;//水星
	planet[3].radius = 696350;//太陽
	planet[4].radius = 50000;//地球
	
	planet[0].color = GetColor(204, 204, 204);
	planet[1].color = GetColor(218, 179, 0);
	planet[2].color = GetColor(188, 226, 232);
	planet[3].color = GetColor(238, 120, 0);
	planet[4].color = GetColor(0, 0, 200);

	float sun_radius = 696350;//太陽半径
	float sun_pos_z = obj.pos.z + sun_radius + 149600;
	
	planet[0].pos = VGet(-170, 45, 183465);//月
	planet[1].pos = VGet(-150, 45, 250000);//金星
	planet[2].pos = VGet(-150, 45, 300000);//水星
	planet[3].pos = VGet(-150, 45, 350000+sun_radius);//太陽
	planet[4].pos = VGet(-170, -10000, 100000);//地球

	for (int i = 1; i < 5; i++) {
		planet[i].draw_flg = false;
	}
	planet[0].draw_flg = true;
	//planet[1].pos = VGet(100, 413, 1300);
	//planet[2].pos = VGet(100, 413, 1300);
	//planet[3].pos = VGet(100, 413, 1300);
	
}
//ファイル読み込み
//int Fail_Read_Init() {
	//f_damege_aria.filehandle = FileRead_open("Text/test.txt");
	//FileRead_gets(f_damege_aria.str, 256, f_damege_aria.filehandle);
	//DrawString(0, 100, f_damege_aria.str, GetColor(0, 255, 0));
	//WaitKey();//確認するためキー入力まち
	//FileRead_close(f_damege_aria.filehandle);

	//FILE* fp;
	//errno_t error;
	//int pos = 100;

	//error = fopen_s(&fp, "Text/test.txt", "w");

	//if (error != NULL) {
	//	printf("ファイルオープンエラー");
	//	exit(EXIT_FAILURE);
	//	return 0;
	//}
	//else {
	//	/*fwrite(&pos, sizeof(int), 1, fp);*/
	//	fprintf(fp, "666676658565656585");
	//	fclose(fp);
	//}
//}
