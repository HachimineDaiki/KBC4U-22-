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
    DrawFormatString(100, 20, GetColor(255, 255, 255), "カメラ縦角度 %.0f", cameraVAngle);
    DrawFormatString(100, 40, GetColor(255, 255, 255), "カメラ横角度 %.0f", cameraHAngle);

    //// Hit_check.cppで使用している変数の数値など ////
    // 関数　Sph_hit(float dis)　で使用

    // 関数 Ground_model_hit_check(VECTOR MoveVector) で使用
    DrawFormatString(100, 100, GetColor(255, 255, 255), "[sphx %.0f] [sphy %.0f] [sphz %.0f]", sph[0].pos.x, sph[0].pos.y, sph[0].pos.z);


    //Player.cppで使用している変数の数値など
    DrawFormatString(100, 250, GetColor(255, 255, 255), "%f", sph[0].zaccl);

    DrawFormatString(100, 300, GetColor(255, 255, 255), "p_zmove%f", sph[0].zmove);

    switch (Input_PlayerMoveDir())
    {
    case Left:DrawFormatString(100, 300, GetColor(255, 255, 255), "[左]");
        break;
    case Right:DrawFormatString(100, 300, GetColor(255, 255, 255), "[右]");
        break;
    case Up:DrawFormatString(100, 300, GetColor(255, 255, 255), "[上]");
        break;
    }
}