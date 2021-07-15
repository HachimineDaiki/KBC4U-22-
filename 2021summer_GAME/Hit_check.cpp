#include <Dxlib.h>
#include <math.h>
#include "Hit_check.h"
#include "3Dmodel.h"

bool Sph_hit_check(Sph sp[]) {
	vx = sp[1].x - sp[0].x;//x����
	vy = sp[1].y - sp[0].y;//y����
	vz = sp[1].z - sp[0].z;//z����
	float distance = vx * vx + vy * vy + vz * vz;//2�_�Ԃ̋���
	float radius_sum = (sp[0].radius + sp[1].radius) * (sp[0].radius + sp[1].radius); //���a�̘a
	return distance < radius_sum ? true : false;//2�_�Ԃ̋��������a�̘a��菬������Γ������Ă���Ɣ���
}

//���Ƌ��̓����蔻������m������̏���
void Sph_hit() {
}

//���f���Ƌ��̓����蔻��`�F�b�N
void Model_hit_check() {
	//���̃x�N�g���^ Pos�ɑ��
	sph[0].pos = VGet(sph[0].x, sph[0].y, sph[0].z);

	//���f���Ƌ��̓����蔻����擾
	for (int i = 0; i < TREE_NUM; i++) {
		HitPolyDim[i] = MV1CollCheck_Sphere(tree_handle[i], -1, sph[0].pos, sph[0].radius);
	}
}

void Model_hit() {
	//�����蔻������m������̏���
	for (int j = 0; j < TREE_NUM; j++) {
		if (HitPolyDim[j].HitNum >= 1)
		{
			SetFontSize(50);
			DrawFormatString(600, 250, GetColor(255, 0, 0), "[�؂̃��f�� HIT]");
			SetFontSize(20);
		}
		//DrawFormatString(100, 300 + ((j + 1) * 20), GetColor(255, 255, 255), "%d", HitPolyDim[j].HitNum);//�����������f����polygon���\��
	}

	//���f������̃��������
	for (int i = 0; i < TREE_NUM; i++) {
		MV1CollResultPolyDimTerminate(HitPolyDim[i]);
	}
}