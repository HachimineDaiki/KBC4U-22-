#pragma once
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Player.h"
void Init_Effect();
int LoadEffect();

struct Effect
{
	int playing_effect_handle;//�G�t�F�N�g�v���Chandle
	int effect_handle;//�G�t�F�N�ghandle
	VECTOR pos;//���W
};

extern Effect e_move;
extern Effect e_orbit;
extern Effect e_bom;