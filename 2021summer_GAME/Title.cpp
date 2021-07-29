#include <DxLib.h>
#include "Title.h"

int TitleLoad() {//画像の読み込み	
	if ((title.g_title = LoadGraph("images/title.png")) == -1)return -1;
}
void Titleinit() {
	//タイトルの初期座標とかいれる
}
void Titledraw() {//画像の描画
	DrawGraph(0,0,title.g_title,FALSE); 
	if (CheckHitKey(KEY_INPUT_SPACE)) {
	}
}