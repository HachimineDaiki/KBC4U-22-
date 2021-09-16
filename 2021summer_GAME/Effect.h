#pragma once
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Player.h"
void Init_Effect();
void  LoadEffect();
void ImageEffect();
struct Effect
{
	int playing_effect_handle;//�G�t�F�N�g�v���Chandle
	int effect_handle;//�G�t�F�N�ghandle
	VECTOR pos;//���W
	bool effect_flg;//effect�t���O
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