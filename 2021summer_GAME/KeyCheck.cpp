#include"DxLib.h"
#include"KeyCheck.h"

void KeyChecker() {

	//入力キーを取得
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;

}