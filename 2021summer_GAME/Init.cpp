#include "Init.h"
#include "3Dmodel.h"
#include "Player.h"
void Sph_init() {
	//球の初期化
	for (int i = 0; i < 2; i++) {
		sph[i].speed = 10.0f;
		sph[i].radius = 200.0f;
		sph[i].v0y = 0.0f;
		sph[i].pos = VGet(100.0f, 5471.0f, 1300.0f);
		sph[i].color = GetColor(255, 255, 255);
		sph[i].zaccl = 2.0f;
		sph[i].zmove = 0.0f;
		sph[i].control = 0.02f;
		sph[i].hp = 100;
	}
	
	sph[0].v = VGet(0.0f, 0.0f, 0.0f);

}

void Obj_init(){
	obj.pos = VGet(-2000.0f, -42459.0f, 130100.0f);
	obj.radius = 400.0f;
	obj.color = GetColor(0, 255, 100);
}
//当たったらダメ―ジを受ける障害物初期化
void Damege_Init() {
	e_obj.pos = VGet(0.0f,1000.0f,7500.0f);
	e_obj.radius = 600.0f;
	e_obj.color = GetColor(255,255,100);
}

//減速エリア初期化
void Decelearia_init() {
	for (int i = 0; i < DECELEARIA_NUM; i++) {
		decelearia[i].radius = 500.0f;
		decelearia[i].color = GetColor(255, 0, 0);
		decelearia[i].v = VGet(0.0f, 0.0f, 0.0f);
	}

	//直線の位置//////////////////////////////////////////////////////
	decelearia[0].pos = VGet(-1000.0f, 1800.0f, 5000.0f);
	decelearia[1].pos = VGet(1000.0f, 1800.0f, 5000.0f);
	/*decelearia[2].pos = VGet(0.0f, 1800.0f, 5000.0f);*/

	decelearia[3].pos = VGet(-1000.0f, 500.0f, 10000.0f);
	/*decelearia[4].pos = VGet(1000.0f, 500.0f, 10000.0f);*/
	decelearia[5].pos = VGet(0.0f, 500.0f, 10000.0f);

	/*decelearia[6].pos = VGet(-1000.0f, -800.0f, 15000.0f);*/
	decelearia[7].pos = VGet(1000.0f, -800.0f, 15000.0f);
	decelearia[8].pos = VGet(0.0f, -800.0f, 15000.0f);

	//コーナー1////////////////////////////////////////////////////////////
	decelearia[9].pos = VGet(-1000.0f, -2300.0f, 20000.0f);
	decelearia[10].pos = VGet(1000.0f, -2300.0f, 20000.0f);
	/*decelearia[11].pos = VGet(0.0f, -2300.0f, 20000.0f);*/

	decelearia[12].pos = VGet(-1500.0f, -3500.0f, 25000.0f);
	decelearia[13].pos = VGet(0.0f, -3500.0f, 25000.0f);
	decelearia[14].pos = VGet(1000.0f, -3500.0f, 25000.0f);

	decelearia[15].pos = VGet(-3000.0f, -4700.0f, 30000.0f);
	decelearia[16].pos = VGet(-2000.0f, -4700.0f, 30000.0f);
	/*decelearia[17].pos = VGet(0.0f, -4000.0f, 30000.0f);*/

	decelearia[18].pos = VGet(-6000.0f, -6400.0f, 35000.0f);
	/*decelearia[19].pos = VGet(-5000.0f, -5700.0f, 35000.0f);*/
	decelearia[20].pos = VGet(-3400.0f, -6400.0f, 36000.0f);

	//直線2////////////////////////////////////////////////////////////////
	decelearia[21].pos = VGet(-14000.0f, -8300.0f, 42000.0f);
	decelearia[22].pos = VGet(-14000.0f, -8000.0f, 40000.0f);
	decelearia[23].pos = VGet(-14000.0f, -7500.0f, 38000.0f);

	decelearia[24].pos = VGet(-20000.0f, -8300.0f, 40000.0f);
	decelearia[25].pos = VGet(-20000.0f, -8100.0f, 39000.0f);
	decelearia[26].pos = VGet(-20000.0f, -8000.0f, 38000.0f);

	decelearia[27].pos = VGet(-25000.0f, -9000.0f, 42000.0f);
	decelearia[28].pos = VGet(-25000.0f, -8900.0f, 40000.0f);
	decelearia[29].pos = VGet(-25000.0f, -8800.0f, 38000.0f);

	//コーナー2//////////////////////////////////////////////////////////////
	decelearia[30].pos = VGet(-30000.0f, -9600.0f, 42000.0f);
	/*decelearia[31].pos = VGet(-30000.0f, -9500.0f, 41000.0f);*/
	decelearia[32].pos = VGet(-30000.0f, -9400.0f, 40000.0f);

	/*decelearia[33].pos = VGet(-36000.0f, -10000.0f, 45000.0f);*/
	decelearia[34].pos = VGet(-37000.0f, -10500.0f, 45000.0f);
	/*decelearia[35].pos = VGet(-38000.0f, -10000.0f, 45000.0f);*/

	decelearia[36].pos = VGet(-42000.0f, -11700.0f, 50000.0f);
	decelearia[37].pos = VGet(-41000.0f, -11700.0f, 50000.0f);
	decelearia[38].pos = VGet(-40000.0f, -11700.0f, 50000.0f);

	decelearia[39].pos = VGet(-43000.0f, -13000.0f, 55000.0f);
	decelearia[40].pos = VGet(-42000.0f, -13000.0f, 55000.0f);
	decelearia[41].pos = VGet(-41000.0f, -13000.0f, 55000.0f);

	decelearia[42].pos = VGet(-37000.0f, -14500.0f, 60000.0f);
	decelearia[43].pos = VGet(-38000.0f, -14500.0f, 60000.0f);
	decelearia[44].pos = VGet(-38000.0f, -14500.0f, 60000.0f);
	//直線3//////////////////////////////////////////////////////////////
	decelearia[45].pos = VGet(-24000.0f, -17600.0f, 69000.0f);
	decelearia[46].pos = VGet(-24000.0f, -17500.0f, 68000.0f);
	decelearia[47].pos = VGet(-24000.0f, -17400.0f, 67000.0f);
	//コーナー3///////////////////////////////////////////////////////////
	decelearia[48].pos = VGet(0.0f, -19600.0f, 69000.0f);
	decelearia[49].pos = VGet(0.0f, -19500.0f, 68000.0f);
	decelearia[50].pos = VGet(0.0f, -19400.0f, 67000.0f);

	decelearia[51].pos = VGet(14000.0f, -22800.0f, 78000.0f);
	decelearia[52].pos = VGet(13000.0f, -22700.0f, 78000.0f);
	decelearia[53].pos = VGet(12000.0f, -22600.0f, 78000.0f);

	//直線4
	decelearia[54].pos = VGet(5000.0f, -26400.0f, 91000.0f);
	/*decelearia[55].pos = VGet(5000.0f, -26000.0f, 90000.0f);*/
	decelearia[56].pos = VGet(5000.0f, -25900.0f, 88000.0f);

	decelearia[57].pos = VGet(-2000.0f, -26900.0f, 90000.0f);
	decelearia[58].pos = VGet(-2000.0f, -26700.0f, 88000.0f);
	/*decelearia[59].pos = VGet(-2000.0f, -19000.0f, 000.0f);*/

	decelearia[60].pos = VGet(-7400.0f, -27300.0f, 89000.0f);
	//decelearia[61].pos = VGet(-11000.0f, -22600.0f, 68000.0f);
	//decelearia[62].pos = VGet(-11000.0f, -22500.0f, 67000.0f);
	//コーナー4
	decelearia[63].pos = VGet(-23000.0f, -28500.0f, 89000.0f);
	decelearia[64].pos = VGet(-23000.0f, -28400.0f, 88000.0f);
	decelearia[65].pos = VGet(-23000.0f, -28300.0f, 87000.0f);

	decelearia[66].pos = VGet(-37050.0f, -31900.0f, 98000.0f);
	decelearia[67].pos = VGet(-37050.0f, -31900.0f, 97000.0f);
	decelearia[68].pos = VGet(-37050.0f, -31900.0f, 96000.0f);
	//直線5
	decelearia[67].pos = VGet(-27000.0f, -34900.0f, 109000.0f);
	decelearia[68].pos = VGet(-27000.0f, -34700.0f, 107000.0f);
	decelearia[69].pos = VGet(-27000.0f, -34500.0f, 105000.0f);

	decelearia[70].pos = VGet(-20000.0f, -35500.0f, 108000.0f);
	//コーナー5
	decelearia[71].pos = VGet(-8000.0f, -36500.0f, 109000.0f);
	decelearia[72].pos = VGet(-8000.0f, -36300.0f, 107000.0f);
	decelearia[73].pos = VGet(-8000.0f, -36100.0f, 105000.0f);
}

void Model_init() {
	ground.x = 0.0f;
	ground.y = 0.0f;
	ground.z = 0.0f;

	rock.x = 100.0f;
	rock.y = 5471.0f;
	rock.z = 20000.0f;
}