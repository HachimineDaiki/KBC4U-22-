#include "Goal.h"

void DrawPlanet() {
	for (int i = 0; i < 4;i++) {
		if (planet[i].draw_flg) {
			DrawSphere3D(planet[i].pos, planet[i].radius, 32, planet[i].color, GetColor(255, 255, 255), TRUE);
		}
	}
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
