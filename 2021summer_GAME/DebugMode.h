#pragma once
#include <DxLib.h>
#include"Player.h"
#define MAXOBJ 30

struct DebugObj {
	int r;
	VECTOR pos;
	bool drawflg;
};

void InitObj();
void DrawObj();
void GameObj();

extern DebugObj d_obj[MAXOBJ];