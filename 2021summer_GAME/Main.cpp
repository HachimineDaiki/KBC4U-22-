#include <Dxlib.h>
#include "Init.h"
#include "Hit_check.h"
#include "Player.h"
#include "Camera.h"
#include "3Dmodel.h"

MV1_COLL_RESULT_POLY_DIM HitPolyDim[TREE_NUM];
Sph sph[2];
Model ground;
Model wall;
float  vx, vy, vz;
int wall_handle;
int ground_handle;
int tree_handle[TREE_NUM];

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

    //--------------初期化関数

    Sph_init();//球の初期化
    Model_init();
    Camera_set();//カメラセット
    Model3d_load();//3Dモデル読み込み
    Model3d_init();//3Dモデル初期化

    // Ｚバッファを有効にする
    SetUseZBuffer3D(TRUE);
    // Ｚバッファへの書き込みを有効にする
    SetWriteZBuffer3D(TRUE);

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {

        // 画面をクリア
        ClearDrawScreen();

        //------------------------------入力関数
        P_move();//プレイヤー入力
        Input_camera_move();//カメラ入力

        //------------------------------計算関数
        Camera_move();//カメラ動かす
        Sph_Gravity();//重力
        Model_hit_check();//モデル
       

        //------------------------------描画関数

        DrawSphere3D(VGet(sph[0].x, sph[0].y, sph[0].z), sph[0].radius, 32, sph[0].color, GetColor(255, 255, 255), TRUE);
        DrawFormatString(100, 100, GetColor(255, 255, 255), "[x %.0f] [y %.0f] [z %.0f]", sph[0].x, sph[0].y, sph[0].z);
       

        Model3d_draw();//3Dモデル描画
        Model_hit();

        ScreenFlip();//裏画面の内容を表画面に反映する
    }

    Model3d_dlet();//3dモデル削除
    DxLib_End();
    // ソフトの終了
    return 0;
}