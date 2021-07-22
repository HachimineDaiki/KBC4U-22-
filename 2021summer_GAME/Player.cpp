#include<DxLib.h>
#include<math.h>
#include"Player.h"
#include"Hit_check.h"
#include"3Dmodel.h"
bool p_zmoveflg = false;//前進に移動するフラグ
float g = 9.81f; //地球の重力
float gplayer_limits = 450;      //Xの範囲
int glimits_verification[2] = { 0,900 }; //端の数値　0: 左の端 900 : 右の端
bool gmoveflg = false;    //false:制限範囲内　true:制限範囲外

//プレイヤー重力処理
void Sph_Gravity() {
        //重力作成
       sph[0].v0y += g;
       sph[0].pos.y -= sph[0].v0y;
       //重力の量が10以上だったら重力を消す。
       if (sph[0].v0y >= 10) {
           g = 0;
       }
}

//プレイヤー移動処理
void P_move() {    
    //鉢嶺処理
    float p_vz2 = -20 * tan(5);
    //float p_vx = 30 * cos(5);
    //float p_vy = 30 * sin(5);
    //p_vz2 / 30; //どんどん速さを変える

    //Z方向に加速する処理
    sph[0].zmove += sph[0].zaccl;
    if (sph[0].zmove >= 50.0f) {
        sph[0].zaccl = 0.0f;
    }

    //前進させるフラグがオンなら前進させる
   if (p_zmoveflg) {
       sph[0].pos.z += sph[0].zmove;
   }
    
   //押されている方向をテキスト表示
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
void P_input_move() {
    //スペースを押したら前進
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        p_zmoveflg = true;
    }

    switch (Input_PlayerMoveDir())
    {
    case Left:st_model_hit.movepos = st_model_hit.leftvec; st_model_hit.MoveFlag = 1; gplayer_limits -= sph[0].speed;
        break;
    case Right:st_model_hit.movepos = st_model_hit.rightvec; st_model_hit.MoveFlag = 1; gplayer_limits += sph[0].speed;
    }

    //判定処理
    Move_Limits();

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

//プレイヤーの左右移動範囲を制限する
void Move_Limits()
{
    int lhit_magnification = 5;    //Xの移動範囲外にでた場合の戻す力の倍率

    //左右のどちらかの範囲外に移動しようとしたらフラグをtrueにする
    if (gplayer_limits <= glimits_verification[0] || gplayer_limits >= glimits_verification[1]) {
        gmoveflg = true;
    }

    if (gmoveflg == true) {
        //範囲内に戻す処理(左)
        if (gplayer_limits < sph[0].speed * lhit_magnification) {
            sph[0].pos.x += 10;
            gplayer_limits += 10;
        }
        //範囲内に戻す処理(右)
        else if (gplayer_limits > glimits_verification[1] - sph[0].speed * lhit_magnification) {
            sph[0].pos.x -= 10;
            gplayer_limits -= 10;
        }
        //フラグをもとに戻す
        else {
            sph[0].speed = 10.0f;
            gmoveflg = false;
        }
    }
}