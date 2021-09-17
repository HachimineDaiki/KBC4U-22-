#include "Effect.h"

void Init_Effect() {
	e_orbit.playing_effect_handle = -1;
	e_bom.playing_effect_handle = -1;
	e_move.playing_effect_handle = -1;
	e_hit.playing_effect_handle = -1;
	e_planet_hit.playing_effect_handle = -1;
	e_wind.playing_effect_handle = -1;
	e_player_smoke.playing_effect_handle = -1;

	Effekseer_Init(10000);//エフェクターを初期化

	e_bom.effect_flg = false;
	e_move.effect_flg = true;
	e_orbit.effect_flg = false;
	e_planet_hit.effect_flg = false;
	e_planet_hit.play_effect_flg = false;
	e_orbit.play_effect_flg = false;
	e_orbit.stop_effect_flg = false;
	e_player_smoke.effect_flg = true;


	e_hit.count = 0;
	//e_move.pos = sph[0].pos;
	//e_orbit.pos = obj.pos;//軌道の位置
	//e_bom.pos = sph[0].pos;//ボムの位置
}

void LoadEffect() {
	e_orbit.effect_handle = LoadEffekseerEffect("effect/Orbit.efkefc", 350.0f);
	e_bom.effect_handle = LoadEffekseerEffect("3Dmodel/exploadSample03.efk", 50.0f);
	/*e_move.effect_handle = LoadEffekseerEffect("effect/move_1.efkefc", 70.0f);*/
	e_move.effect_handle = LoadEffekseerEffect("effect/smoke_effect.efkefc", 150.0f);
	e_hit.effect_handle = LoadEffekseerEffect("effect/Hit_effect.efkefc", 70.0f);
	e_planet_hit.effect_handle = LoadEffekseerEffect("effect/Planet_Hit_effect.efkefc", 5000.0f);
	e_wind.effect_handle = LoadEffekseerEffect("effect/wind.efkefc", 50.0f);
	e_player_smoke.effect_handle = LoadEffekseerEffect("effect/smoke_effect.efkefc", 50.0f);
}

void ImageEffect() {
	/*e_move.image_handle = LoadGraph("images/Smoke.png");*/
}