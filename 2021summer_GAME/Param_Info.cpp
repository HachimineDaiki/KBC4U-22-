#include "DxLib.h"

#include "Init.h"
#include "Hit_check.h"
#include "Player.h"
#include "Camera.h"
#include "3Dmodel.h"
#include "Param_Info.h"

void DrawParam_Info() {

    //// Camera.cppで使用している変数の数値など
    // 関数　Camera_move()　で使用
    DrawFormatString(100, 20, GetColor(255, 255, 255), "カメラ縦角度 %.0f", g_cameraVAngle);
    DrawFormatString(100, 40, GetColor(255, 255, 255), "カメラ横角度 %.0f", g_cameraHAngle);

    DrawFormatString(100, 60, GetColor(255, 255, 255), "岩横角度 %.0f", g_p_direct);

    //// Hit_check.cppで使用している変数の数値など ////
    // 関数　Sph_hit(float dis)　で使用
    for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
        DrawFormatString(500, 100 + (i + 1) * 20, GetColor(255, 255, 255), "[speed %.0f]", damege_aria[i].hit_speed);
    }
    // 関数 Ground_model_hit_check(VECTOR MoveVector) で使用
    DrawFormatString(100, 100, GetColor(255, 255, 255), "[sphx %.0f] [sphy %.0f] [sphz %.0f]", sph[0].pos.x, sph[0].pos.y, sph[0].pos.z);
    ////Player.cppで使用している変数の数値など
    //DrawFormatString(100, 250, GetColor(255, 255, 255), "%f", sph[0].zaccl);
    /*if(st_model_hit.gmoveflg==true)DrawFormatString(100, 200, GetColor(255, 255, 255), "true");
    if (st_model_hit.gmoveflg == false)DrawFormatString(100, 200, GetColor(255, 255, 255), "false");*/
    DrawFormatString(100, 300, GetColor(255, 255, 255), "スピード [ %.0f /150 ]", sph[0].zmove);

 /*   switch (Input_PlayerMoveDir())
    {
    case Left:DrawFormatString(100, 300, GetColor(255, 255, 255), "[左]");
        break;
    case Right:DrawFormatString(100, 300, GetColor(255, 255, 255), "[右]");
        break;
    case Up:DrawFormatString(100, 300, GetColor(255, 255, 255), "[上]");
        break;
    }*/
}