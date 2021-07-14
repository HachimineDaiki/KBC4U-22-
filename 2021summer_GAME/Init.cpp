#include "Init.h"

void Sph_init() {
	//‹…‚Ì‰Šú‰»
	for (int i = 0; i < 2; i++) {
		sph[i].x = 100.0f * (i + 1) + (sph[0].radius + sph[0].radius);
		sph[i].y = 100.0f;
		sph[i].z = 100.0f;
		sph[i].speed = 10.0f;
		sph[i].radius = 100.0f;
		sph[i].v0y = 0.0f;
	}

	vx = 0.0f;
	vy = 0.0f;
	vz = 0.0f;
}