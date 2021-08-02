#include<DxLib.h>
#include<math.h>
#include"Player.h"
#include"Hit_check.h"
#include"3Dmodel.h"
float g = 9.81f; //地球の重力

void Sph_Gravity() {
        //重力作成
       sph[0].v0y += g;
       sph[0].pos.y -= sph[0].v0y;

       if (sph[0].v0y >= 80) {
           g = 0;
       }
}
void Accl() {
    //鉢嶺処理
    float p_vz2 = -5 * tan(5);
    //float p_vx = 30 * cos(5);
    //float p_vy = 30 * sin(5);
    //p_vz2 / 30; //どんどん速さを変える

    if (p_zmoveflg) {
        sph[0].zmove += p_vz2 * sph[0].control;
    }

    if (sph[0].zmove >= 150.0f) {
        sph[0].zmove = 150.0f;
    }

    if (sph[0].zmove >= 50.0f) {
        sph[0].zaccl = 0.0f;
    }
}
void P_move() {    
    if (p_zmoveflg == true) {
        switch (Input_PlayerMoveDir())
        {
        case Left:
            st_model_hit.movepos = st_model_hit.leftvec; st_model_hit.MoveFlag = 1;
            break;
        case Right:
            st_model_hit.movepos = st_model_hit.rightvec; st_model_hit.MoveFlag = 1;
            break;
        }
    
    }
   Accl();//accelerator処理
   P_rotate();//回転処理
}

//プレイヤー回転
void P_rotate() {
    const int rotate_amount = 15;//回転量
    g_p_rotate_amount = sph[0].zmove / rotate_amount;//回転量生成
    g_p_Rotate += g_p_rotate_amount;//回転量を回転に反映させる。
    DrawFormatString(500, 160, GetColor(0, 255, 255), " プレイヤーの回転量 %.0f ",g_p_rotate_amount);
    if (g_p_Rotate >= 360) {
        g_p_Rotate = 0;
    }
    //回転をセット
    MV1SetRotationXYZ(rock.handle, VGet(g_p_Rotate * DX_PI_F / 180.0f, -g_p_direct * DX_PI_F / 180.0f, 0.0f));
}
void P_input_move() {
    //スペースを押したら前進
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        p_zmoveflg = true;
    }

    switch (Input_PlayerMoveDir())
    {
    case Left:st_model_hit.movepos = st_model_hit.leftvec; st_model_hit.MoveFlag = 1; 
        break;
    case Right:st_model_hit.movepos = st_model_hit.rightvec; st_model_hit.MoveFlag = 1;
        break;
    }

    //判定処理
    Move_Limits();

}
//プレイヤーが押している方向を返す関数
int Input_PlayerMoveDir() {

    int input_dir = -1;
    
    if (p_zmoveflg==false) {
        if (CheckHitKey(KEY_INPUT_A)&& sph[0].pos.x > st_model_hit.glimits_verification[0]+10)
        {
            input_dir = Left;
        }
        if (CheckHitKey(KEY_INPUT_D) && sph[0].pos.x < st_model_hit.glimits_verification[1]-10)
        {
            input_dir = Right;
        }
    }
    else {
        if (CheckHitKey(KEY_INPUT_A)&&st_model_hit.gmoveflg == false)
        {
            input_dir = Left;
            st_model_hit.landr_move = 1;
        }
        if (CheckHitKey(KEY_INPUT_D) && st_model_hit.gmoveflg == false)
        {
            input_dir = Right;
            st_model_hit.landr_move = 2;
        }

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
