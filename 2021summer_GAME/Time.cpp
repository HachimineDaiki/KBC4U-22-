#include "Time.h"

void InitTime() {
	effect_time.count = 0;
	effect_time.time = 0;

	effect_exit_time.count = 0;
	effect_exit_time.time = 0;
}

int EffectExitTime() {
	effect_exit_time.count++;
	return effect_exit_time.time = effect_exit_time.count / 60;
}

int EffectTime() {
	effect_time.count++;
	return effect_time.time = effect_time.count / 60;
}