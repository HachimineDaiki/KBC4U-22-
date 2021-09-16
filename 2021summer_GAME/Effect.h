#pragma once
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Player.h"
void Init_Effect();
void  LoadEffect();
void ImageEffect();
struct Effect
{
	int playing_effect_handle;//エフェクトプレイhandle
	int effect_handle;//エフェクトhandle
	VECTOR pos;//座標
	bool effect_flg;//effectフラグ
	bool play_effect_flg;
	bool stop_effect_flg;
	int image_handle;
};

extern Effect e_move;
extern Effect e_orbit;
extern Effect e_bom;
extern Effect e_hit;
extern Effect e_planet_hit;
extern Effect e_wind;