#include <DxLib.h>
#include "Title.h"
#include "Init.h"

int TitleLoad() {//�摜�̓ǂݍ���	
	if ((title.g_title = LoadGraph("images/title.png")) == -1)return -1;
}
void Titleinit() {
	TitleLoad();
	//�^�C�g���̏������W�Ƃ������
}
void Titledraw() {//�摜�̕`��
	DrawGraph(0,0,title.g_title,FALSE); 
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		gameMode = 1;
	}

	//if (CheckHitKey(KEY_INPUT_S)) {
	////	gameMode = 1;
	//}
}