#include <DxLib.h>
#include"Gameover.h"
#include"Init.h"
#include"Player.h"
#include"3Dmodel.h"
#include"Camera.h"



int Gameoverload() {  //�Q�[���I�[�o�[�̉摜�����[�h����
	if ((gameover.g_gameover = LoadGraph("images/gameover2.png")) == -1)return -1;
}

void Gameoverinit() {  //�Q�[���I�[�o�[�̉摜�����[�h����
	Gameoverload();
}


void Gameoverdraw() {   //�Q�[���I�[�o�[�̉摜��`�悷��
	DrawGraph(0, 0, gameover.g_gameover, FALSE);

	
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			WaitTimer(1000);
			All_Init();
			gameMode = 0;

		}


}
