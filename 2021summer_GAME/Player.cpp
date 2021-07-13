#include<DxLib.h>
#include"Player.h"
#include"Hit_check.h"

void P_move() {
    switch (Input_PlayerMoveDir())
    {
    case Left:sph[0].x -= sph[0].speed;
        break;
    case Right:sph[0].x += sph[0].speed;
        break;
    case Down:sph[0].z -= sph[0].speed;
        break;
    case Up:sph[0].z += sph[0].speed;
        break;
    }

    switch (Input_PlayerMoveDir())
    {
    case Left:DrawFormatString(100, 300, GetColor(255, 255, 255), "[ç∂]");
        break;
    case Right:DrawFormatString(100, 300, GetColor(255, 255, 255), "[âE]");
        break;
    case Down:DrawFormatString(100, 300, GetColor(255, 255, 255), "[â∫]");
        break;
    case Up:DrawFormatString(100, 300, GetColor(255, 255, 255), "[è„]");
        break;
    }
}


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