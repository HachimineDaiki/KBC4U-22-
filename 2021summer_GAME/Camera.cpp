#include <DxLib.h>
#include <math.h>
#include "Init.h"
#include "Camera.h"
#include "Player.h"
#include "Hit_check.h"
#include"KeyCheck.h"



// 移動速度
#define MOVESPEED				     10.0f

// カメラの回転速度
#define CAMERA_ANGLE_SPEED	          3.0f

// カメラの注視点の高さ
#define CAMERA_LOOK_AT_HEIGHT         250.0f

// カメラと注視点の距離
#define CAMERA_LOOK_AT_DISTANCE    1100.0f


//ZAHA追加
// カメラの注視点の高さ
#define OBJ_CAMERA_LOOK_AT_HEIGHT         300.0f

// カメラと注視点の距離 1100.0f
#define OBJ_CAMERA_LOOK_AT_DISTANCE    5000.0f

float AT_HEIGHT = 300.0f;
float AT_Distance = 5000.0f;
extern bool obj_switchflg;
int    ModelHandle;
float  AnimTotalTime;
float  AnimNowTime;
int    AnimAttachIndex;
int    RunFlag;
int    MoveAnimFrameIndex;
VECTOR Position;
int    MoveFlag;
float  Angle;
extern float  CameraHAngle;
extern float  CameraVAngle;
VECTOR MoveVector;
float  SinParam;
float  CosParam;
VECTOR InitPos;

void Camera_set() {
	// カメラの向きを初期化
	g_cameraHAngle = 0.0f;
	g_cameraVAngle = 25.0f;
    g_p_direct = 0.0f;
   // g_cameraPosition;
    camera.switching = false;//カメラ切り替え追加
    obj_switchflg = false; //オブジェクト視点切り替え
    InitPos = obj.pos;
}
void Obj_Camera_move() {
    VECTOR TempPosition1;
    VECTOR TempPosition2;
    VECTOR CameraPosition;
    VECTOR CameraLookAtPosition;
    
    // 注視点はキャラクターモデルの座標から CAMERA_LOOK_AT_HEIGHT 分だけ高い位置
    
    CameraLookAtPosition = obj.pos;
    CameraLookAtPosition.y += OBJ_CAMERA_LOOK_AT_HEIGHT;

    // カメラの位置はカメラの水平角度と垂直角度から算出

    // 最初に垂直角度を反映した位置を算出
    SinParam = sinf(CameraVAngle / 180.0f * DX_PI_F);
    CosParam = cosf(CameraVAngle / 180.0f * DX_PI_F);
    TempPosition1.x = 0.0f;
    TempPosition1.y = SinParam * AT_Distance;
    TempPosition1.z = -CosParam * AT_Distance;

    // 次に水平角度を反映した位置を算出
    SinParam = sinf(CameraHAngle / 180.0f * DX_PI_F);
    CosParam = cosf(CameraHAngle / 180.0f * DX_PI_F);
    TempPosition2.x = CosParam * TempPosition1.x - SinParam * TempPosition1.z;
    TempPosition2.y = TempPosition1.y;
    TempPosition2.z = SinParam * TempPosition1.x + CosParam * TempPosition1.z;

    // 算出した座標に注視点の位置を加算したものがカメラの位置
    CameraPosition = VAdd(TempPosition2, CameraLookAtPosition);

    // カメラの設定に反映する
    SetCameraPositionAndTarget_UpVecY(CameraPosition, CameraLookAtPosition);
}

void Camera_move() {
    SetCameraNearFar(100.0f, 300000.0f);
    VECTOR tempPosition1;
    VECTOR tempPosition2;
    VECTOR cameraLookAtPosition;
    float sinParam;
    float cosParam;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 注視点はキャラクターモデルの座標から CAMERA_LOOK_AT_HEIGHT 分だけ高い位置
    if (obj_switchflg) {
        Obj_Camera_move();
    }
    else {
        //カメラが切り替える処理
        if (camera.switching) {
            /*Obj_Camera_move();*/
            g_cameraVAngle -= 1.0f;
            if (g_cameraVAngle <= 0.0f)
            {
                g_cameraVAngle = 0.0f;
            }

            cameraLookAtPosition = VGet(sph[0].pos.x, sph[0].pos.y, sph[0].pos.z);
            cameraLookAtPosition.y += CAMERA_LOOK_AT_HEIGHT;
        }
        else {
            cameraLookAtPosition = VGet(sph[0].pos.x, sph[0].pos.y, sph[0].pos.z);
            cameraLookAtPosition.y += CAMERA_LOOK_AT_HEIGHT;
        }
    }
        // カメラの位置はカメラの水平角度と垂直角度から算出

        // 最初に垂直角度を反映した位置を算出
        sinParam = (float)sin(g_cameraVAngle / 180.0f * DX_PI_F);
        cosParam = (float)cos(g_cameraVAngle / 180.0f * DX_PI_F);
        tempPosition1.x = 0.0f;
        tempPosition1.y = sinParam * CAMERA_LOOK_AT_DISTANCE;
        tempPosition1.z = -cosParam * CAMERA_LOOK_AT_DISTANCE;

        // 次に水平角度を反映した位置を算出
        sinParam = (float)sin(g_cameraHAngle / 180.0f * DX_PI_F);
        cosParam = (float)cos(g_cameraHAngle / 180.0f * DX_PI_F);
        tempPosition2.x = cosParam * tempPosition1.x - sinParam * tempPosition1.z;
        tempPosition2.y = tempPosition1.y;
        tempPosition2.z = sinParam * tempPosition1.x + cosParam * tempPosition1.z;

        // 算出した座標に注視点の位置を加算したものがカメラの位置
        g_cameraPosition = VAdd(tempPosition2, cameraLookAtPosition);

        // 角度表示
        //DrawFormatString(300, 0, GetColor(255, 255, 255), "カメラ座標 X%.0f Y%.0f Z%.0f", g_cameraPosition.x, g_cameraPosition.y, g_cameraPosition.z);
       // DrawFormatString(100, 40, GetColor(255, 255, 255), "カメラ横角度 %.0f", g_cameraHAngle);
        //DrawFormatString(0,0,GetColor(255,255,255), "カメラざ");
        // カメラの設定に反映する
        SetCameraPositionAndTarget_UpVecY(g_cameraPosition, cameraLookAtPosition);
    

}

void Input_camera_move() {
    // 方向キーでカメラを回転（ゴールした後のカメラアングル確認用）
    if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0)
    {
        CameraVAngle -= CAMERA_ANGLE_SPEED / 4;
        if (CameraVAngle <= -89.0f)
        {
            CameraVAngle = -89.0f;
        }
    }
    if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0)
    {
       /* CameraVAngle += CAMERA_ANGLE_SPEED / 4;*/
        if (CameraVAngle >= 89.0f)
        {
            CameraVAngle = 89.0f;
        }
    }

    //if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0)
    //{
    //    g_cameraHAngle += CAMERA_ANGLE_SPEED / 4;
        //if (g_cameraHAngle >= 180.0f)
        //{
        //    g_cameraHAngle -= 360.0f;
        //}
    //}
    //if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0)
    //{
    //    g_cameraHAngle -= CAMERA_ANGLE_SPEED / 4;
    //    if (g_cameraHAngle <= -180.0f)
    //    {
    //        g_cameraHAngle += 360.0f;
    //    }
    //}
    if (p_zmoveflg == true) {
        // if (sph[0].pos.z >= branch.branch_point[branch.branch_position]) {
        if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0)
        {
            g_p_direct += CAMERA_ANGLE_SPEED / 2;
            if (g_p_direct >= 180.0f)
            {
                g_p_direct -= 360.0f;

                g_cameraHAngle -= 360.0f;
            }

        }
        if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0)
        {
            g_p_direct -= CAMERA_ANGLE_SPEED / 2;
            if (g_p_direct <= -180.0f) {
                g_p_direct += 360.0f;

                g_cameraHAngle += 360.0f;
            }

        }

        //if ((sph[0].zmove >= 0) || (g_CollisionReflectionFlag == 1 && sph[0].zmove < 0)) {// 岩が前に進んでいるときの岩の処理
        //if (g_frontflg == 0 && ((sph[0].zmove > 0) || (sph[0].zmove < 0))) {// 岩が前に進んでいるときの岩の処理
        //////////////////
        ///左右４５°の設定
        //////////////////
        if (g_WallHitFlag == 0) {
            if (g_p_direct >= g_cameraHAngle - 45 || g_p_direct <= g_cameraHAngle + 45) {//岩の前方の範囲
                if (g_p_direct > g_cameraHAngle) {
                    g_cameraHAngle += CAMERA_ANGLE_SPEED / 3;
                    if (g_cameraHAngle >= g_p_direct) {
                        g_cameraHAngle = g_p_direct;
                    }
                    if (g_WallHitFlag == 0 && (g_cameraHAngle <= g_p_direct - 45)) {
                        g_cameraHAngle = g_p_direct - 45;
                    }
                }
                if (g_p_direct < g_cameraHAngle) {
                    g_cameraHAngle -= CAMERA_ANGLE_SPEED / 3;
                    if (g_cameraHAngle <= g_p_direct) {
                        g_cameraHAngle = g_p_direct;
                    }
                    if (g_WallHitFlag == 0 && (g_cameraHAngle >= g_p_direct + 45)) {
                        g_cameraHAngle = g_p_direct + 45;
                    }
                }
            }
        }
        ///////////////
        ///左右90°の設定
        ///////////////       
        if (g_WallHitFlag == 1) {
            if (g_p_direct >= g_cameraHAngle - 180 || g_p_direct <= g_cameraHAngle + 180) {//岩の前方の範囲
                if (g_p_direct > g_cameraHAngle) {
                    g_cameraHAngle += CAMERA_ANGLE_SPEED / 3;
                    if (g_cameraHAngle >= g_p_direct) {
                        g_cameraHAngle = g_p_direct;
                        g_WallHitFlag = 0;
                    }
                    if (g_cameraHAngle <= g_p_direct - 180) {
                        g_cameraHAngle = g_p_direct - 180;
                    }
                }
                if (g_p_direct < g_cameraHAngle) {
                    g_cameraHAngle -= CAMERA_ANGLE_SPEED / 3;
                    if (g_cameraHAngle <= g_p_direct) {
                        g_cameraHAngle = g_p_direct;
                        g_WallHitFlag = 0;
                    }
                    if (g_cameraHAngle >= g_p_direct + 180) {
                        g_cameraHAngle = g_p_direct + 180;
                    }
                }
            }
        }
        //}
        //else if ((sph[0].zmove < 0) || (g_CollisionReflectionFlag == 1 && sph[0].zmove >= 0)) {//後ろに進んでいるときのカメラの動き
        //else if (g_frontflg == 1 && ((sph[0].zmove < 0) || (sph[0].zmove >= 0))) {//後ろに進んでいるときのカメラの動き
        //    if (g_p_direct >= 0) {//岩の向きが整数なら
        //        if ((g_p_direct - 180) >= g_cameraHAngle - 10 || (g_p_direct - 180) <= g_cameraHAngle + 10) {
        //            if ((g_p_direct - 180) >= g_cameraHAngle) {
        //                g_cameraHAngle += CAMERA_ANGLE_SPEED / 4;
        //                if (g_cameraHAngle >= g_p_direct - 180) {
        //                    g_cameraHAngle = g_p_direct - 180;
        //                }
        //                if (g_cameraHAngle <= (g_p_direct - 180) - 10) {
        //                    g_cameraHAngle = (g_p_direct - 180) - 10;
        //                }
        //            }
        //            if ((g_p_direct - 180) <= g_cameraHAngle) {
        //                g_cameraHAngle -= CAMERA_ANGLE_SPEED / 4;
        //                if (g_cameraHAngle <= g_p_direct - 180) {
        //                    g_cameraHAngle = g_p_direct - 180;
        //                }
        //                if (g_cameraHAngle >= (g_p_direct - 180) + 10) {
        //                    g_cameraHAngle = (g_p_direct - 180) + 10;
        //                }
        //            }
        //        }
        //    }
        //    else if (g_p_direct < 0) {// 輪の向きが負の数なら
        //        if ((g_p_direct + 180) >= g_cameraHAngle - 10 || (g_p_direct + 180) <= g_cameraHAngle + 10) {
        //            if ((g_p_direct + 180) >= g_cameraHAngle) {
        //                g_cameraHAngle += CAMERA_ANGLE_SPEED / 4;
        //                if (g_cameraHAngle >= g_p_direct + 180) {
        //                    g_cameraHAngle = g_p_direct + 180;
        //                }
        //                if (g_cameraHAngle <= (g_p_direct + 180) - 10) {
        //                    g_cameraHAngle = (g_p_direct + 180) - 10;
        //                }
        //            }
        //            if ((g_p_direct + 180) <= g_cameraHAngle) {
        //                g_cameraHAngle -= CAMERA_ANGLE_SPEED / 4;
        //                if (g_cameraHAngle <= g_p_direct + 180) {
        //                    g_cameraHAngle = g_p_direct + 180;
        //                }
        //                if (g_cameraHAngle >= (g_p_direct + 180) + 10) {
        //                    g_cameraHAngle = (g_p_direct + 180) + 10;
        //                }
        //            }
        //        }

        //    }
        //}
    }
}

