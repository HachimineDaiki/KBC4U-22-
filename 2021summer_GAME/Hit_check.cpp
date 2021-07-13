#include <Dxlib.h>
#include <math.h>
#include "Hit_check.h"

bool Sph_hit_check(Sph sp[]) {
	float vx = sp[1].x - sp[0].x;//x¬•ª
	float vy = sp[1].y - sp[0].y;//y¬•ª
	float vz = sp[1].z - sp[0].z;//z¬•ª
	float distance = vx * vx + vy * vy + vz * vz;//2“_ŠÔ‚Ì‹——£
	float radius_sum = (sp[0].radius + sp[1].radius) * (sp[0].radius + sp[1].radius); //”¼Œa‚Ì˜a
	return distance < radius_sum ? true : false;//2“_ŠÔ‚Ì‹——£‚ª”¼Œa‚Ì˜a‚æ‚è¬‚³‚¯‚ê‚Î“–‚½‚Á‚Ä‚¢‚é‚Æ”»’è

}