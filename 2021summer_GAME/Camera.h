#pragma once
#include <DxLib.h>

void Camera_set();
void Camera_move();
void Input_camera_move();

//ZAHA追加関数

void Obj_Camera_move();

//カメラ構造体 ZAHA追加
struct Camera
{
	bool switching;//カメラ切り替え
};


extern float  g_sinParam;
extern float  g_cosParam;
extern float  g_cameraHAngle;//横アングル
extern float  g_cameraVAngle;//縦アングル
extern VECTOR g_cameraPosition;//カメラの座標
extern Camera camera;//カメラ
extern VECTOR obj_cameraPosition;//オブジェクトのカメラ座標