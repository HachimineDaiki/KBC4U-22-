#include "Effect.h"

void Init_Effect() {
	e_orbit.playing_effect_handle = -1;
	e_bom.playing_effect_handle = -1;
	

	e_orbit.pos = obj.pos;//�O���̈ʒu
	e_bom.pos = sph[0].pos;//�{���̈ʒu
}

int LoadEffect() {
}