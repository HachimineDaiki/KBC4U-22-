#include "Effect.h"

void Init_Effect() {
	e_orbit.playing_effect_handle = -1;
	e_bom.playing_effect_handle = -1;
	e_move.playing_effect_handle = -1;

	e_move.pos = sph[0].pos;
	e_orbit.pos = obj.pos;//‹O“¹‚ÌˆÊ’u
	e_bom.pos = sph[0].pos;//ƒ{ƒ€‚ÌˆÊ’u
}

int LoadEffect() {
}