#include "Effect.h"

void Init_Effect() {
	e_orbit.playing_effect_handle = -1;
	e_bom.playing_effect_handle = -1;
	e_move.playing_effect_handle = -1;

	e_move.pos = sph[0].pos;
	e_orbit.pos = obj.pos;//軌道の位置
	e_bom.pos = sph[0].pos;//ボムの位置
}

int LoadEffect() {
}