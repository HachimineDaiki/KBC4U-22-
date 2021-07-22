#include "Init.h"
#include "3Dmodel.h"
void Sph_init() {
	//‹…‚Ì‰Šú‰»
	for (int i = 0; i < 2; i++) {
		sph[i].speed = 10.0f;
		sph[i].radius = 100.0f;
		sph[i].v0y = 0.0f;
		sph[i].pos = VGet(100.0f, 5471.0f, 1300.0f);
		sph[i].color = GetColor(255, 255, 255);
		sph[i].zaccl = 2.0f;
		sph[i].zmove = 0.0f;
	}
	
	vx = 0.0f;
	vy = 0.0f;
	vz = 0.0f;
}

void Obj_init(){
	obj.pos = VGet(100.0f, -1300.0f, 20000.0f);
	obj.radius = 100.0f;
	obj.color = GetColor(0, 255, 100);
}

void Model_init() {
	ground.x = 0.0f;
	ground.y = 0.0f;
	ground.z = 0.0f;

	rock.x = 100.0f;
	rock.y = 5471.0f;
	rock.z = 20000.0f;
}