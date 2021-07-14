#include <DxLib.h>
#include <math.h>
#include "Init.h"



// 移動速度
#define MOVESPEED				     10.0f

// カメラの回転速度
#define CAMERA_ANGLE_SPEED	          3.0f

// カメラの注視点の高さ
#define CAMERA_LOOK_AT_HEIGHT         0.0f

// カメラと注視点の距離
#define CAMERA_LOOK_AT_DISTANCE    1000.0f

float  cameraHAngle;
float  cameraVAngle;
float  sinParam;
float  cosParam;

void Camera_set() {
	// カメラの向きを初期化
	cameraHAngle = 0.0f;
	cameraVAngle = 40.0f;
}

void Camera_move() {
    VECTOR tempPosition1;
    VECTOR tempPosition2;
    VECTOR cameraPosition;
    VECTOR cameraLookAtPosition;

    // 注視点はキャラクターモデルの座標から CAMERA_LOOK_AT_HEIGHT 分だけ高い位置
    cameraLookAtPosition = VGet(sph[0].x,sph[0].y,sph[0].z);
    cameraLookAtPosition.y += CAMERA_LOOK_AT_HEIGHT;

    // カメラの位置はカメラの水平角度と垂直角度から算出

    // 最初に垂直角度を反映した位置を算出
    sinParam = sin(cameraVAngle / 180.0f * DX_PI_F);
    cosParam = cos(cameraVAngle / 180.0f * DX_PI_F);
    tempPosition1.x = 0.0f;
    tempPosition1.y = sinParam * CAMERA_LOOK_AT_DISTANCE;
    tempPosition1.z = -cosParam * CAMERA_LOOK_AT_DISTANCE;

    // 次に水平角度を反映した位置を算出
    sinParam = sin(cameraHAngle / 180.0f * DX_PI_F);
    cosParam = cos(cameraHAngle / 180.0f * DX_PI_F);
    tempPosition2.x = cosParam * tempPosition1.x - sinParam * tempPosition1.z;
    tempPosition2.y = tempPosition1.y;
    tempPosition2.z = sinParam * tempPosition1.x + cosParam * tempPosition1.z;

    // 算出した座標に注視点の位置を加算したものがカメラの位置
    cameraPosition = VAdd(tempPosition2, cameraLookAtPosition);

    // カメラの設定に反映する
    SetCameraPositionAndTarget_UpVecY(cameraPosition, cameraLookAtPosition);
}

void Input_camera_move() {
    // 方向キーでカメラを回転
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

