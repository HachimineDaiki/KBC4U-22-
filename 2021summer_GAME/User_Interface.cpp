#include <DxLib.h>
#include "User_Interface.h"
#include "player.h"

VECTOR Ill_dump2;//�ړ����Ă���s�@�������̈ʒu������

int judgement = 0;//1�����@2�听���@�̃t���O

//UI�Ɏg�p������̏�����
void UIinit() {
	g_Ill_dump1 = obj.pos;
	Ill_dump2 = VGet(0.0f, 0.0f, 0.0f);
	g_goalflag = 0;//�S�[���������ǂ����@0�S�[�����ĂȂ��@1�S�[������
	g_dist = 150 * (300 * 3.33);//�S�[���̍ő哾�_�̊i�[
	g_GoalFullScore = 0;
}

void Judgement() {
	if ((0.8 * g_GoalFullScore) <= distance) {//�ő��80%�ȏ� 80% => 0.8
		judgement = 1;
	}
	else if ((0.6 * g_GoalFullScore) <= distance) {//�ő��60%�ȏ� 60% => 0.6
		judgement = 2;
	}
	else if ((0.5 * g_GoalFullScore) <= distance) {//�ő��50%�ȏ� 50% => 0.5
		judgement = 3;
	}
	else{//�ő��50%�����������Ƃ�
		judgement = 4;
	}
}

//�s�@�������̔�񂾋������v�Z
void Distance_Calculation() {
	float x, y, z;

	Ill_dump2 = obj.pos;

	x = Ill_dump2.x - g_Ill_dump1.x;
	y = Ill_dump2.y - g_Ill_dump1.y;
	z = Ill_dump2.z - g_Ill_dump1.z;
	distance = VSize(VGet(x, y, z));
	 
}


//UI�̕\��
void UIdraw() {
	
	//SetFontSize(100);//�����T�C�Y��ύX
//	DrawFormatString(341, 334, GetColor(255, 255, 0), " GOAL "); 
	//if (g_dist >= 1) {
	//	//DrawFormatString(341, 140, GetColor(0, 255, 255), " GOAL ");
	//	DrawFormatString(291, 140, GetColor(0, 255, 255), " �S�[�� ");
	//}
	//if (g_dist < 1) {
	//	if (judgement == 1) {
	//		SetFontSize(50);
	//		DrawFormatString(300, 170, GetColor(255, 255, 0), " ���z�܂Ŕ�񂾂�I ");
	//		SetFontSize(10);
	//	}
	//	else if (judgement == 2) {
	//		SetFontSize(50);
	//		DrawFormatString(300, 170, GetColor(255, 255, 0), " �����܂Ŕ�񂾂�I ");
	//		SetFontSize(10);
	//	}
	//	else if (judgement == 3) {
	//		SetFontSize(50);
	//		DrawFormatString(300, 170, GetColor(255, 255, 0), " �����܂Ŕ�񂾂�I ");
	//		SetFontSize(10);
	//	}
	//	else if (judgement == 4) {
	//		SetFontSize(50);
	//		DrawFormatString(300, 170, GetColor(255, 255, 0), " ���܂Ŕ�񂾂�I ");
	//		SetFontSize(10);

	//	}
	//}
	//DrawFormatString(341, 20, GetColor(0, 255, 255), " GOAL ");
	//SetFontSize(50);
	//DrawFormatString(341, 120, GetColor(0, 0, 0), "%.0f", distance);//�^��
	//DrawFormatString(341, 241, GetColor(255, 255, 255), "   �򋗗� ", distance);//�^�� ���̐��������̈Ӗ���������
	//DrawFormatString(341, 290, GetColor(255, 255, 255), "  %8.0fkm", distance);//�^�� �򋗗�

	//DrawFormatString(0, 0, GetColor(0, 0, 0), "%.0f", distance);//����
	//DrawFormatString(341, 0, GetColor(0, 0, 0), "%.0f", distance);//��
	//DrawFormatString(682, 0, GetColor(0, 0, 0), "%.0f", distance);//�E��
	//DrawFormatString(0, 256, GetColor(0, 0, 0), "%.0f", distance);//��
	//DrawFormatString(682, 434, GetColor(0, 0, 0), "%.0f", distance);//�E
	//DrawFormatString(0, 512, GetColor(0, 0, 0), "%.0f", distance);//����
	//DrawFormatString(341, 512, GetColor(0, 0, 0), "%.0f", distance);//��
	//DrawFormatString(682, 512, GetColor(0, 0, 0), "%.0f", distance);//�E��

	//DrawFormatString(341, 484, GetColor(0, 0, 0), "%.5f", obj.zmove);//�s�@��������zmove�̕\���m�F�p
	//DrawFormatString(341, 584, GetColor(0, 0, 0), "%.5f", g_dist);//g_dist�̕\���m�F�p
	SetFontSize(20);//�����T�C�Y��ύX
}