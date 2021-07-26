#include <Dxlib.h>
#include "Init.h"
#include "Hit_check.h"
#include "Player.h"
#include "Camera.h"
#include "3Dmodel.h"
#include "Param_Info.h"

MV1_COLL_RESULT_POLY_DIM HitPolyDim[TREE_NUM];
Sph sph[2];
Sph obj;
Sph deceleAria[4];
Model ground;
Model rock;
StageModelHit st_model_hit;
HitDrow htdrow;
VECTOR TempMoveVector;


float  vx, vy, vz;
int tree_handle[TREE_NUM];
float s_dis;
bool p_zmoveflg;


float sinParam;
float cosParam;
float cameraHAngle;
float  cameraVAngle;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //// 画面モードの設定
    //SetGraphMode(1920,1080, 32);
    //ChangeWindowMode(FALSE);

    // ウインドウモードで起動
    ChangeWindowMode(TRUE);

    SetGraphMode(1024, 768, 32);

    SetBackgroundColor(70, 130, 180);

    if (DxLib_Init() < 0)
    {
        // エラーが発生したら直ちに終了
        return -1;
    }

    //--------------初期化関数

    Sph_init();//球の初期化
    Obj_init();//不法投棄物の初期化
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
        
       
        if (Sph_hit_check(sph, obj)) {
            Sph_hit(s_dis);
            htdrow.hitflg = true;
        }
        /*Sph_hit(s_dis);*/
        //------------------------------描画関数
        Model3d_draw();//3Dモデル描画

        DrawSphere3D(obj.pos, obj.radius, 32, obj.color, GetColor(255, 255, 255), TRUE);
        

        for (int i = 0; i < 4;i++) {
            DrawSphere3D(deceleAria[i].pos, deceleAria[i].radius, 32, deceleAria[i].color, GetColor(255, 255, 255), TRUE);
        }


        if (htdrow.hitflg) { SetFontSize(30); DrawFormatString(100, 340, GetColor(0, 255, 255), "飛ばした距離をさせる予定"); }

        /*Model_hit();*/
        /*Model_hit();*/

        DrawParam_Info();

        if (sph[0].pos.y <= -12000) {
            sph[0].pos.y = -12000;
            p_zmoveflg = false;
        }
        ScreenFlip();//裏画面の内容を表画面に反映する
    }

    Model3d_dlet();//3dモデル削除
    DxLib_End();
    // ソフトの終了
    return 0;
}