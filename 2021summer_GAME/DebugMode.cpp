//#include "DebugMode.h"
//int i = 0;
//int d_input_count = 0;
//bool inputflg = false;
//void InitObj(){
//	for (int i = 0; i < MAXOBJ; i++) {
//		d_obj[i].drawflg = false;
//		d_obj[i].r = 600;
//	}
//}
//void DrawObj(){
//	for (int i = 0; i < MAXOBJ; i++) {
//		if (d_obj[i].drawflg) {
//			DrawSphere3D(d_obj[i].pos, d_obj[i].r, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
//		}
//	}
//}
//void GameObj(){
//	if (CheckHitKey(KEY_INPUT_3)) {
//		d_input_count++;
//	}
//	else {
//		d_input_count = 0;
//	}
//
//	if (d_input_count == 1) {
//		inputflg = true;
//	}
//
//
//	if (inputflg) {
//		d_obj[i].pos = obj.pos;
//		d_obj[i].drawflg = true;
//		inputflg = false;
//		i++;
//	}
//
//	if (i >= MAXOBJ) {
//		i = MAXOBJ;
//	}
//}