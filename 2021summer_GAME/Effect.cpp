#include "Effect.h"

void Init_Effect() {
	e_bom.playing_effect_handle = -1;
	e_orbit.playing_effect_handle = -1;

	e_orbit.pos = obj.pos;//軌道の位置
	e_bom.pos = sph[0].pos;//ボムの位置
}

int LoadEffect() {
	if (e_orbit.effect_handle = LoadEffekseerEffect("effect/orbit.efkpkg", 25.0f) == -1)return-1;
	if (e_bom.effect_handle = LoadEffekseerEffect("3Dmodel/exploadSample03.efk", 50.0f) == -1)return-1;
}