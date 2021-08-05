#include "Init.h"
#include "3Dmodel.h"
#include "Player.h"
void Sph_init() {
	//�v���C���[�̏�����
	for (int i = 0; i < 2; i++) {
		sph[i].speed = 10.0f; //�v���C���[���x
		sph[i].radius = 200.0f;//�v���C���[���a
		sph[i].v0y = 0.0f; //�v���C���[Y�������x
		sph[i].pos = VGet(100.0f, 468.0f, 1300.0f);//�v���C���[�������W
		sph[i].color = GetColor(255, 255, 255);//�v���C���[�J���[
		sph[i].zaccl = 2.0f;//�v���C���[z����accelerator
		sph[i].zmove = 0.0f;//�v���C���[Z�����ړ�
		sph[i].control = 0.02f;//�v���C���[���x�����ϐ�
		sph[i].hp = 100;//�v���C���[�̗�
	}
	
	sph[0].v = VGet(0.0f, 0.0f, 0.0f);//�v���C���[�x�N�g��

}
//�s�@����������
void Obj_init(){
	obj.pos = VGet(-3000.0f, -20000.0f, 120000.0f);//�s�@�����������W
	obj.radius = 400.0f;//�s�@�������a
	obj.color = GetColor(0, 255, 100);//�s�@�����J���[
}
//����������_���\�W���󂯂��Q��������
void Damege_Init() {
	for (int i = 0; i < E_DAMEGE;i++) {
		e_obj[i].radius = 500.0f;
		e_obj[i].color = GetColor(255, 255, 100);
	}

	//�_���[�W�������W
	e_obj[0].pos = VGet(27000.0f,-11351.0f,69486.0f);
	e_obj[1].pos = VGet(25555.0f,-12654.0f,76525.0f);
	e_obj[2].pos = VGet(27000.0f, -12654.0f, 76525.0f);
	e_obj[3].pos = VGet(11922.0f, -4477.0f, 29957.0f);
	e_obj[4].pos = VGet(20700.0f, -6489.0f, 41609.0f);
	e_obj[5].pos = VGet(24500.0f, -6489.0f, 42000.0f);
}

//�����G���A������
void Decelearia_init() {
	for (int i = 0; i < DECELEARIA_NUM; i++) {
		decelearia[i].radius = 500.0f;
		decelearia[i].color = GetColor(255, 0, 0);
		decelearia[i].v = VGet(0.0f, 0.0f, 0.0f);
	}
	
	//�������W
	decelearia[0].pos = VGet(-1000.0f, -200.0f, 5000.0f);
	decelearia[1].pos = VGet(1000.0f, -200.0f, 5000.0f);
	decelearia[3].pos = VGet(100.0f, -1070.0f, 10000.0f);
	decelearia[4].pos = VGet(500.0f, -2000.0f, 15000.0f);
	decelearia[5].pos = VGet(-500.0f, -2000.0f, 15000.0f);
	decelearia[6].pos = VGet(-6695.0f, -3820.0f, 25958.0f);
	/*decelearia[7].pos = VGet(-6695.0f, -3820.0f,26400.0f);*/
	decelearia[8].pos = VGet(-20548.0f, -6289.0f, 40640.0f);
	decelearia[9].pos = VGet(-26253.0f, -10815.0f, 66417.0f);
	decelearia[10].pos = VGet(-25289.0f, -12677.0f, 76443.0f);
	decelearia[11].pos = VGet(-11387.0f, -16461.0f, 98970.0f);
}
//���f���̏�����
void Model_init() {
	//�n�ʏ������W
	ground.x = 0.0f;
	ground.y = 0.0f;
	ground.z = 0.0f;

	//�v���C���[�⏉�����W
	rock.x = 100.0f;
	rock.y = 5471.0f;
	rock.z = 20000.0f;
}