#include <Dxlib.h>
//#include "Draw.h"
//#include "Hit_check.h"

enum Dir { Left, Right, Down, Up };

void Init_Sph();
int Input_PlayerMoveDir();

struct Sph
{
    float x, y, z;
    float radius;
    float speed;
};

const int sph_num = 2;

Sph sph[sph_num];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    SetGraphMode(1920, 1080, 16);
    ChangeWindowMode(TRUE);
    SetBackgroundColor(70, 130, 180);

    if (DxLib_Init() < 0)
    {
        // エラーが発生したら直ちに終了
        return -1;
    }

    Init_Sph();

    // Ｚバッファを有効にする
    SetUseZBuffer3D(TRUE);
    // Ｚバッファへの書き込みを有効にする
    SetWriteZBuffer3D(TRUE);

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {

        // 画面をクリア
        ClearDrawScreen();

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
        case Left:DrawFormatString(100, 300, GetColor(255, 255, 255), "[左]");
            break;
        case Right:DrawFormatString(100, 300, GetColor(255, 255, 255), "[右]");
            break;
        case Down:DrawFormatString(100, 300, GetColor(255, 255, 255), "[下]");
            break;
        case Up:DrawFormatString(100, 300, GetColor(255, 255, 255), "[上]");
            break;
        }

        //if (Sph_Hit_Check(sph[0].x, sph[0].y, sph[0].z, sph[0].radius, sph[1].x, sph[1].y, sph[1].z, sph[1].radius)) {
        //    DrawFormatString(100, 500, GetColor(255, 0, 0), "HIT");
        //}
        //else
        //{
        //    DrawFormatString(100, 500, GetColor(255, 255, 255), "Not HIT");
        //}

        /* DrawSphere3D(VGet(sph[0].x, sph[0].y, sph[0].z), sph[0].radius, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
         DrawSphere3D(VGet(sph[1].x, sph[1].y, sph[1].z), sph[1].radius, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);*/
         //球描画
        for (int i = 0; i < sph_num; i++) {
            DrawSphere3D(VGet(sph[i].x, sph[i].y, sph[i].z), sph[i].radius, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
            DrawFormatString(100, 100 * (i + 1), GetColor(255, 255, 255), "[x %.0f] [y %.0f] [z %.0f]", sph[i].x, sph[i].y, sph[i].z);
        }
 
        //裏画面の内容を表画面に反映する
        ScreenFlip();
    }

    DxLib_End();
    // ソフトの終了
    return 0;
}

void Init_Sph() {
    for (int i = 0; i < sph_num; i++) {
        sph[i].x = 100.0f * (i + 1) + (sph[0].radius + sph[0].radius);
        sph[i].y = 100.0f;
        sph[i].z = 100.0f;

        sph[i].speed = 10.0f;

        sph[i].radius = 100.0f;
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