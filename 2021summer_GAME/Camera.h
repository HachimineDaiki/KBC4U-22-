#pragma once
#include <DxLib.h>

void Camera_set();
void Camera_move();
void Input_camera_move();

//ZAHA�ǉ��֐�

void Obj_Camera_move();

//�J�����\���� ZAHA�ǉ�
struct Camera
{
	bool switching;//�J�����؂�ւ�
};


extern float  g_sinParam;
extern float  g_cosParam;
extern float  g_cameraHAngle;//���A���O��
extern float  g_cameraVAngle;//�c�A���O��
extern VECTOR g_cameraPosition;//�J�����̍��W
extern Camera camera;//�J����
extern VECTOR obj_cameraPosition;//�I�u�W�F�N�g�̃J�������W