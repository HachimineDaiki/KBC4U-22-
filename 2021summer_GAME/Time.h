#pragma once
#include <Dxlib.h>

void InitTime();
int EffectTime();
int EffectExitTime();
struct Time_ {
	int count;
	int time;
};

extern Time_ effect_time;
extern Time_ effect_exit_time;//effectèIóπ