#include <Dxlib.h>
#include <math.h>
#include "Hit_check.h"

bool Sph_hit_check(Sph sp[]) {
	float vx = sp[1].x - sp[0].x;//x¬•ª
	float vy = sp[1].y - sp[0].y;//y¬•ª
	float vz = sp[1].z - sp[0].z;//z¬•ª

	float distance = sqrtf(vx * vx + vy * vy + vz * vz);//2“_ŠÔ‚Ì‹——£

	float radius_sum = sp[0].radius + sp[1].radius; //”¼Œa‚Ì˜a
	bool hit = false;

	return distance < radius_sum ? true : false;

}

void Sph_init() {
	
	for (int i = 0; i < 2; i++) {
		sph[i].x = 100.0f * (i + 1) + (sph[0].radius + sph[0].radius);
		sph[i].y = 100.0f;
		sph[i].z = 100.0f;

		sph[i].speed = 10.0f;

		sph[i].radius = 100.0f;
	}
}