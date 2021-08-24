#pragma once
#include <Dxlib.h>

void InitTime();
int EffectTime();

struct Time_ {
	int count;
	int time;
};

extern Time_ effect_time;