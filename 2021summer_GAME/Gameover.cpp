#include <DxLib.h>
#include"Gameover.h"
#include"Init.h"
#include"Player.h"
#include"3Dmodel.h"
#include"Camera.h"
#include"KeyCheck.h"



int Gameoverload() {  //ゲームオーバーの画像をロードする
	if ((gameover.g_gameover = LoadGraph("images/gameover2.png")) == -1)return -1;
}

void Gameoverinit() {  //ゲームオーバーの画像をロードする
	Gameoverload();
}


void Gameoverdraw() {   //ゲームオーバーの画像を描画する
	DrawGraph(0, 0, gameover.g_gameover, FALSE);

	
	if (g_KeyFlg & PAD_INPUT_2) {  //Ａキーでスタート
			//WaitTimer(1000);
			All_Init();
			gameMode = 0;

		}


}
