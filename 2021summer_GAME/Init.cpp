#include "Init.h"
#include "3Dmodel.h"
void Sph_init() {
	//‹…‚Ì‰Šú‰»
	for (int i = 0; i < 2; i++) {
		sph[i].x = 100.0f * (i + 1) + (sph[0].radius + sph[0].radius);
		sph[i].y = 100.0f;
		sph[i].z = 100.0f;
		sph[i].speed = 10.0f;
		sph[i].radius = 100.0f;
		sph[i].v0y = 0.0f;
		sph[i].pos = VGet(sph[i].x, sph[i].y, sph[i].z);
		sph[i].color = GetColor(255, 255, 255);
	}
	
	vx = 0.0f;
	vy = 0.0f;
	vz = 0.0f;
}

void Model_init() {
	ground.x = 0.0f;
	ground.y = -300.0f;
	ground.z = -700.0f;

	wall.x = 0.0f;
	wall.y = -300.0f;
	wall.z = 11000.0f;
}