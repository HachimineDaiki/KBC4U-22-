#include <DxLib.h>
#include <math.h>
#include "Init.h"
#include "Camera.h"
#include "Player.h"
#include "Hit_check.h"



// �ړ����x
#define MOVESPEED				     10.0f

// �J�����̉�]���x
#define CAMERA_ANGLE_SPEED	          3.0f

// �J�����̒����_�̍���
#define CAMERA_LOOK_AT_HEIGHT         250.0f

// �J�����ƒ����_�̋���
#define CAMERA_LOOK_AT_DISTANCE    1100.0f



void Camera_set() {
	// �J�����̌�����������
	g_cameraHAngle = 0.0f;
	g_cameraVAngle = 25.0f;

    g_p_direct = 0.0f;
}

void Camera_move() {
    VECTOR tempPosition1;
    VECTOR tempPosition2;
    VECTOR cameraPosition;
    VECTOR cameraLookAtPosition;

    // �����_�̓L�����N�^�[���f���̍��W���� CAMERA_LOOK_AT_HEIGHT �����������ʒu
    cameraLookAtPosition = VGet(sph[0].pos.x,sph[0].pos.y,sph[0].pos.z);
    cameraLookAtPosition.y += CAMERA_LOOK_AT_HEIGHT;

    // �J�����̈ʒu�̓J�����̐����p�x�Ɛ����p�x����Z�o

    // �ŏ��ɐ����p�x�𔽉f�����ʒu���Z�o
    g_sinParam = (float)sin(g_cameraVAngle / 180.0f * DX_PI_F);
    g_cosParam = (float)cos(g_cameraVAngle / 180.0f * DX_PI_F);
    tempPosition1.x = 0.0f;
    tempPosition1.y = g_sinParam * CAMERA_LOOK_AT_DISTANCE;
    tempPosition1.z = -g_cosParam * CAMERA_LOOK_AT_DISTANCE;

    // ���ɐ����p�x�𔽉f�����ʒu���Z�o
    g_sinParam = (float)sin(g_cameraHAngle / 180.0f * DX_PI_F);
    g_cosParam = (float)cos(g_cameraHAngle / 180.0f * DX_PI_F);
    tempPosition2.x = g_cosParam * tempPosition1.x - g_sinParam * tempPosition1.z;
    tempPosition2.y = tempPosition1.y;
    tempPosition2.z = g_sinParam * tempPosition1.x + g_cosParam * tempPosition1.z;

    // �Z�o�������W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
    cameraPosition = VAdd(tempPosition2, cameraLookAtPosition);

    // �p�x�\��
   // DrawFormatString(100, 0, GetColor(255, 255, 255), "�J�������W X%.0f Y%.0f Z%.0f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
   // DrawFormatString(100, 40, GetColor(255, 255, 255), "�J�������p�x %.0f", g_cameraHAngle);

    // �J�����̐ݒ�ɔ��f����
    SetCameraPositionAndTarget_UpVecY(cameraPosition, cameraLookAtPosition);

}

void Input_camera_move() {
    // �����L�[�ŃJ��������]
    if (CheckHitKey(KEY_INPUT_UP) == 1)
    {
        g_cameraVAngle -= CAMERA_ANGLE_SPEED / 4;
        if (g_cameraVAngle <= 0.0f)
        {
            g_cameraVAngle = 0.0f;
        }
    }
    if (CheckHitKey(KEY_INPUT_DOWN) == 1)
    {
        g_cameraVAngle += CAMERA_ANGLE_SPEED / 4;
        if (g_cameraVAngle >= 45.0f)
        {
            g_cameraVAngle = 45.0f;
        }
    }
    if (CheckHitKey(KEY_INPUT_LEFT) == 1)
    {
        g_cameraHAngle += CAMERA_ANGLE_SPEED / 4;
        if (g_cameraHAngle >= 180.0f)
        {
            g_cameraHAngle -= 360.0f;
        }
    }
    if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
    {
        g_cameraHAngle -= CAMERA_ANGLE_SPEED / 4;
        if (g_cameraHAngle <= -180.0f)
        {
            g_cameraHAngle += 360.0f;
        }
    }
    if (p_zmoveflg == true) {
        // if (sph[0].pos.z >= branch.branch_point[branch.branch_position]) {
        if (CheckHitKey(KEY_INPUT_A) == 1)
        {
            g_p_direct += CAMERA_ANGLE_SPEED / 2;
            if (g_p_direct >= 180.0f)
            {
                g_p_direct -= 360.0f;

                g_cameraHAngle -= 360.0f;
            }

        }
        if (CheckHitKey(KEY_INPUT_D) == 1)
        {
            g_p_direct -= CAMERA_ANGLE_SPEED / 2;
            if (g_p_direct <= -180.0f) {
                g_p_direct += 360.0f;

                g_cameraHAngle += 360.0f;
            }

        }

        if (g_p_direct >= g_cameraHAngle - 10 || g_p_direct <= g_cameraHAngle + 10) {
            if (g_p_direct >= g_cameraHAngle) {
                g_cameraHAngle += CAMERA_ANGLE_SPEED / 4;
                if (g_cameraHAngle >= g_p_direct) {
                    g_cameraHAngle = g_p_direct;
                }
                if (g_cameraHAngle <= g_p_direct - 10) {
                    g_cameraHAngle = g_p_direct - 10;
                }
            }
            if (g_p_direct <= g_cameraHAngle) {
                g_cameraHAngle -= CAMERA_ANGLE_SPEED / 4;
                if (g_cameraHAngle <= g_p_direct) {
                    g_cameraHAngle = g_p_direct;
                }
                if (g_cameraHAngle >= g_p_direct + 10) {
                    g_cameraHAngle = g_p_direct + 10;
                }
            }
        }
    }
}

