#include "Time.h"

void InitTime() {
	effect_time.count = 0;
	effect_time.time = 0;
}

int EffectTime() {
	effect_time.count++;
	return effect_time.time = effect_time.count / 60;
}