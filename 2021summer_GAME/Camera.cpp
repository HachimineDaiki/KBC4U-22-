#include <DxLib.h>
#include <math.h>
#include "Init.h"



// �ړ����x
#define MOVESPEED				     10.0f

// �J�����̉�]���x
#define CAMERA_ANGLE_SPEED	          3.0f

// �J�����̒����_�̍���
#define CAMERA_LOOK_AT_HEIGHT         0.0f

// �J�����ƒ����_�̋���
#define CAMERA_LOOK_AT_DISTANCE    1000.0f

float  cameraHAngle;
float  cameraVAngle;
float  sinParam;
float  cosParam;

void Camera_set() {
	// �J�����̌�����������
	cameraHAngle = 0.0f;
	cameraVAngle = 40.0f;
}

void Camera_move() {
    VECTOR tempPosition1;
    VECTOR tempPosition2;
    VECTOR cameraPosition;
    VECTOR cameraLookAtPosition;

    // �����_�̓L�����N�^�[���f���̍��W���� CAMERA_LOOK_AT_HEIGHT �����������ʒu
    cameraLookAtPosition = VGet(sph[0].x,sph[0].y,sph[0].z);
    cameraLookAtPosition.y += CAMERA_LOOK_AT_HEIGHT;

    // �J�����̈ʒu�̓J�����̐����p�x�Ɛ����p�x����Z�o

    // �ŏ��ɐ����p�x�𔽉f�����ʒu���Z�o
    sinParam = sin(cameraVAngle / 180.0f * DX_PI_F);
    cosParam = cos(cameraVAngle / 180.0f * DX_PI_F);
    tempPosition1.x = 0.0f;
    tempPosition1.y = sinParam * CAMERA_LOOK_AT_DISTANCE;
    tempPosition1.z = -cosParam * CAMERA_LOOK_AT_DISTANCE;

    // ���ɐ����p�x�𔽉f�����ʒu���Z�o
    sinParam = sin(cameraHAngle / 180.0f * DX_PI_F);
    cosParam = cos(cameraHAngle / 180.0f * DX_PI_F);
    tempPosition2.x = cosParam * tempPosition1.x - sinParam * tempPosition1.z;
    tempPosition2.y = tempPosition1.y;
    tempPosition2.z = sinParam * tempPosition1.x + cosParam * tempPosition1.z;

    // �Z�o�������W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
    cameraPosition = VAdd(tempPosition2, cameraLookAtPosition);

    // �J�����̐ݒ�ɔ��f����
    SetCameraPositionAndTarget_UpVecY(cameraPosition, cameraLookAtPosition);
}

void Input_camera_move() {
    // �����L�[�ŃJ��������]
    if (CheckHitKey(KEY_INPUT_UP) == 1)
    {
        cameraVAngle -= CAMERA_ANGLE_SPEED;
        if (cameraVAngle <= 0.0f)
        {
            cameraVAngle = 0.0f;
        }
    }
    if (CheckHitKey(KEY_INPUT_DOWN) == 1)
    {
        cameraVAngle += CAMERA_ANGLE_SPEED;
        if (cameraVAngle >= 80.0f)
        {
            cameraVAngle = 80.0f;
        }
    }
    if (CheckHitKey(KEY_INPUT_LEFT) == 1)
    {
        cameraHAngle += CAMERA_ANGLE_SPEED;
        if (cameraHAngle >= 180.0f)
        {
            cameraHAngle -= 360.0f;
        }
    }
    if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
    {
        cameraHAngle -= CAMERA_ANGLE_SPEED;
        if (cameraHAngle <= -180.0f)
        {
            cameraHAngle += 360.0f;
        }
    }
}

