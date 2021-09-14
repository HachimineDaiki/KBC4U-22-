#include "Effect.h"

void Init_Effect() {
	e_bom.playing_effect_handle = -1;
	e_orbit.playing_effect_handle = -1;

	e_orbit.pos = obj.pos;//‹O“¹‚ÌˆÊ’u
	e_bom.pos = sph[0].pos;//ƒ{ƒ€‚ÌˆÊ’u
}

int LoadEffect() {
	if (e_orbit.effect_handle = LoadEffekseerEffect("effect/Orbit.efkefc", 25.0f) == -1)return-1;
	if (e_bom.effect_handle = LoadEffekseerEffect("3Dmodel/exploadSample03.efk", 50.0f) == -1)return-1;
}