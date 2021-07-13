#include <Dxlib.h>
#include <math.h>
#include "Hit_check.h"

bool Sph_hit_check(Sph sp[]) {
	float vx = sp[1].x - sp[0].x;//x����
	float vy = sp[1].y - sp[0].y;//y����
	float vz = sp[1].z - sp[0].z;//z����
	float distance = vx * vx + vy * vy + vz * vz;//2�_�Ԃ̋���
	float radius_sum = (sp[0].radius + sp[1].radius) * (sp[0].radius + sp[1].radius); //���a�̘a
	return distance < radius_sum ? true : false;//2�_�Ԃ̋��������a�̘a��菬������Γ������Ă���Ɣ���

}