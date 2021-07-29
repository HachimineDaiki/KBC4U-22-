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
		sph[i].control = 0.02f;
	}
	
	sph[0].v = VGet(0.0f, 0.0f, 0.0f);
}

void Obj_init(){
	obj.pos = VGet(100.0f, -1300.0f, 20000.0f);
	obj.radius = 100.0f;
	obj.color = GetColor(0, 255, 100);
}

//Œ¸‘¬ƒGƒŠƒA‰Šú‰»
void Decelearia_init() {
	for (int i = 0; i < DECELEARIA_NUM; i++) {
		decelearia[i].radius = 500.0f;
		decelearia[i].color = GetColor(255, 0, 0);
		decelearia[i].v = VGet(0.0f, 0.0f, 0.0f);
	}

	decelearia[0].pos = VGet(-1000.0f, 3800.0f, 5000.0f);
	decelearia[1].pos = VGet(2000.0f, 3800.0f, 5000.0f);
	decelearia[2].pos = VGet(0.0f, 2000.0f, 10000.0f);
	decelearia[3].pos = VGet(-1000.0f, 300.0f, 15000.0f);
	decelearia[4].pos = VGet(2000.0f, 300.0f, 15000.0f);
}

void Model_init() {
	ground.x = 0.0f;
	ground.y = 0.0f;
	ground.z = 0.0f;

	rock.x = 100.0f;
	rock.y = 5471.0f;
	rock.z = 20000.0f;
}