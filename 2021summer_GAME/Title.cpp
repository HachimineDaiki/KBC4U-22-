#include <DxLib.h>
#include "Title.h"

int TitleLoad() {//�摜�̓ǂݍ���	
	if ((title.g_title = LoadGraph("images/title.png")) == -1)return -1;
}
void Titleinit() {
	//�^�C�g���̏������W�Ƃ������
}
void Titledraw() {//�摜�̕`��
	DrawGraph(0,0,title.g_title,FALSE); 
	if (CheckHitKey(KEY_INPUT_SPACE)) {
	}
}