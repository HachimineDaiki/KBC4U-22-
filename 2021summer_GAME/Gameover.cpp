#include <DxLib.h>
#include"Gameover.h"
#include"Init.h"
#include"Player.h"
#include"3Dmodel.h"
#include"Camera.h"
#include"KeyCheck.h"



int Gameoverload() {  //�Q�[���I�[�o�[�̉摜�����[�h����
	if ((gameover.g_gameover = LoadGraph("images/gameover2.png")) == -1)return -1;
}

void Gameoverinit() {  //�Q�[���I�[�o�[�̉摜�����[�h����
	Gameoverload();
}


void Gameoverdraw() {   //�Q�[���I�[�o�[�̉摜��`�悷��
	DrawGraph(0, 0, gameover.g_gameover, FALSE);

	
	if (g_KeyFlg & PAD_INPUT_2) {  //�`�L�[�ŃX�^�[�g
			//WaitTimer(1000);
			All_Init();
			gameMode = 0;

		}


}
