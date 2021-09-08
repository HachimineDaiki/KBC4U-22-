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

	DrawBox(780, 600, 1020, 620, GetColor(255, 255, 255), TRUE);
	DrawFormatString(800, 600, GetColor(0, 0, 0), "2021/09/08/ 16:20");//ビルド時間表示

}
