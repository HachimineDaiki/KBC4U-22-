#include "Goal.h"

void DrawPlanet() {
	for (int i = 0; i < 5;i++) {
		if (planet[i].draw_flg) {
			DrawSphere3D(planet[i].pos, planet[i].radius, 32, planet[i].color, GetColor(255, 255, 255), TRUE);
		}
	}
	/*DrawSphere3D(planet[0].pos, planet[0].radius, 32, planet[0].color, GetColor(0, 0, 0), TRUE);*/
}
//惑星の動き
void PlanetMove() {
	switch (CheckPlanet(speed_draw_str.last_speed, sph[0].hp))
	{
	case 0: MonthMove();
		break;
	case 1: VenusMove();
		break;
	case 2: MercuryMove();
		break;
	case 3: SunMove();
		break;
	}
	
}
void MonthMove() {//月
	
	goal_obj.speed = 350.0f;//不法投棄物移動スピード]
	planet[0].pos = VGet(0, 36597, earth_pos_z + 38000);//月//座標更新
}
void VenusMove() {//金星
	
	goal_obj.speed = 900.0f;//不法投棄物移動スピード
	planet[1].pos = VGet(0, 182466, earth_pos_z + 400000);//金星//座標更新
}
void MercuryMove() {//水星
	
	goal_obj.speed = 1600.0f;//不法投棄物移動スピード
	planet[2].pos = VGet(0, 339155, earth_pos_z + 770000);//水星//座標更新
}
void SunMove() {//太陽
	
	goal_obj.speed = 2200.0f;//不法投棄物移動スピード
	planet[3].pos = VGet(0, 525050, 1451646);//太陽//座標更新
}

//どこの惑星か判別処理
int CheckPlanet(float speed, int hp) {
	float check_speed = speed;
	int check_hp = hp;
	int planet_num = -1;
	
	if (check_speed >= 0 && check_speed <= 70) {
		planet_num = 0;
		
	}
	else if (check_speed >= 71 && check_speed <= 100) {
		if (check_hp >= 50) {
			planet_num = 1;
		}
		else {
			planet_num = 0;
		}
	}
	else if (check_speed >= 101 && check_speed <= 130) {
		if (check_hp >= 100) {
			planet_num = 2;
		}
		else {
			planet_num = 1;
		}
	}
	else if (check_speed >= 131 && check_speed <= 150) {
		if (check_hp >= 200) {
			planet_num = 3;
		}
		else {
			planet_num = 2;
		}
	}

	return planet_num;
}
//
//void InitMap() {
//	goal_scene.x = 0;
//	goal_scene.y = 0;
//	goal_scene.width = 1920;
//}
//int MapLoad() {
//	if ((title.g_title = LoadGraph("images/goal_map.png")) == -1)return -1;
//}
//void MoveMap() {
//}
