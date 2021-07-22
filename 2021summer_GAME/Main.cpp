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
StageModelHit st_model_hit;

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
        Input_camera_move();//カメラ入力
        //------------------------------計算関数
        Ground_model_hit();
        Camera_move();//カメラ動かす
        //Model_hit_check();//モデル
       
        
        //------------------------------描画関数
        Model3d_draw();//3Dモデル描画
        DrawFormatString(100, 320, GetColor(255, 255, 255), "%.0f", sph[0].v0y);
        DrawFormatString(100, 340, GetColor(255, 255, 255), "%.0f", sph[0].pos.y);
        /*Model_hit();*/

        ScreenFlip();//裏画面の内容を表画面に反映する
    }

    Model3d_dlet();//3dモデル削除
    DxLib_End();
    // ソフトの終了
    return 0;
}