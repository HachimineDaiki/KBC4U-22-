#include<DxLib.h>
#include"Player.h"
#include"Hit_check.h"
#include"3Dmodel.h"
bool p_zmoveflg = false;//前進に移動するフラグ
float g = 1.0f;

void Sph_Gravity() {
        //重力作成
        /*sph[0].v0y += g;*/
       /* sph[0].y -= g*//*sph[0].v0y*/;

        //if (sph[0].y < ground.y  + sph[0].radius) {
        //    /*sph[i].v0y *= -1 * sph[i].bounce;*/
        //    sph[0].y = ground.y + sph[0].radius;
        //    if (abs(int(sph[0].v0y)) < g) { //速度がある程度小さくなったら強制的に0にする
        //        sph[0].v0y = 0;
        //    }
        //}
}

void P_move() {
    //スペースを押したら前進
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        p_zmoveflg = true;
    }

    if (p_zmoveflg == true) {
        switch (Input_PlayerMoveDir())
        {
        case Left:/*sph[0].z += sph[0].speed;*/
            /*sph[0].x -= sph[0].speed;*/ st_model_hit.movepos = st_model_hit.leftvec; st_model_hit.MoveFlag = 1;
            break;
        case Right:/*sph[0].x += sph[0].speed;*/
            /* sph[0].z += sph[0].speed;*/ st_model_hit.movepos = st_model_hit.rightvec; st_model_hit.MoveFlag = 1;
            break;
        }

    }

   if (p_zmoveflg == true) {
        sph[0].z += sph[0].speed;
        if (sph[0].z > wall.z - sph[0].radius) {
            sph[0].speed = 0;
        }
    }
    


   //押されている方向をテキスト表示
    switch (Input_PlayerMoveDir())
    {
    case Left:DrawFormatString(100, 300, GetColor(255, 255, 255), "[左]");
        break;
    case Right:DrawFormatString(100, 300, GetColor(255, 255, 255), "[右]");
        break;
    }
}

//プレイヤーが押している方向を返す関数
int Input_PlayerMoveDir() {

    int input_dir = -1;

    if (CheckHitKey(KEY_INPUT_A))
    {
        input_dir = Left;
    }
    if (CheckHitKey(KEY_INPUT_D))
    {
        input_dir = Right;
    }
    if (CheckHitKey(KEY_INPUT_S))
    {
        input_dir = Down;
    }
    if (CheckHitKey(KEY_INPUT_W))
    {
        input_dir = Up;
    }
    return input_dir;
}