#include <Dxlib.h>
#include "Hit_check.h"
#include "Player.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 画面モードの設定
    SetGraphMode(1920,1080, 32);
    ChangeWindowMode(FALSE);
    SetBackgroundColor(70, 130, 180);

    if (DxLib_Init() < 0)
    {
        // エラーが発生したら直ちに終了
        return -1;
    }

    Sph_init();

    // Ｚバッファを有効にする
    SetUseZBuffer3D(TRUE);
    // Ｚバッファへの書き込みを有効にする
    SetWriteZBuffer3D(TRUE);

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {

        // 画面をクリア
        ClearDrawScreen();

        

        if (Sph_hit_check(sph)) {
            DrawFormatString(100, 500, GetColor(255, 0, 0), "HIT");
        }
        else
        {
            DrawFormatString(100, 500, GetColor(255, 255, 255), "Not HIT");
        }

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

