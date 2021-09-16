#pragma once
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Player.h"
void Init_Effect();
int LoadEffect();

struct Effect
{
	int playing_effect_handle;//エフェクトプレイhandle
	int effect_handle;//エフェクトhandle
	VECTOR pos;//座標
};

extern Effect e_move;
extern Effect e_orbit;
extern Effect e_bom;