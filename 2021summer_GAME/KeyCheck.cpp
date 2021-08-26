#include"DxLib.h"
#include"KeyCheck.h"

void KeyChecker() {

	//“ü—ÍƒL[‚ğæ“¾
	g_OldKey = g_NowKey;
	g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	g_KeyFlg = g_NowKey & ~g_OldKey;

}