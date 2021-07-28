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
Sph decelearia[DECELEARIA_NUM];
Model ground;
Model rock;
StageModelHit st_model_hit;
HitDrow htdrow;
VECTOR TempMoveVector;
Decel decel;

//int tree_handle[TREE_NUM];
float s_dis;
bool p_zmoveflg;

float sinParam;
float cosParam;
float cameraHAngle;
float  cameraVAngle;

float merikomi;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 画面モードの設定
    SetGraphMode(1920,1080, 32);
    ChangeWindowMode(FALSE);

    //SetGraphMode(800, 600, 32);

    SetBackgroundColor(70, 130, 180);

    if (DxLib_Init() < 0)
    {
        // エラーが発生したら直ちに終了
        return -1;
    }

    //--------------初期化関数

    Sph_init();//球の初期化
    Obj_init();//不法投棄物の初期化
    Decelearia_init();//減速エリア初期化
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
       
        //不法投棄物とプレイヤーの当たり判定
        if (Sph_hit_check(sph, obj)) {
            Sph_hit(s_dis);
            htdrow.hitflg = true;
        }
         if (htdrow.hitflg) {
                obj.pos.x += 1;
                 obj.pos.y += 30 * cos(10)*10;
                 obj.pos.z += 200 * tan(10)*10;
                 //obj.pos.x += 90 * tan(5);
                DrawFormatString(100,600, GetColor(0, 255, 255),"[x %.0f][y %.0f][z %.0f]",obj.pos.x,obj.pos.y,obj.pos.z);
               
         }


        //減速エリアに入っているかチェック
        decel.hit_flg = false;//減速フラグ
        for (int i = 0; i < DECELEARIA_NUM; i++) {
            if (Decel_aria_check(sph, decelearia,i)) {
                decel.hit_flg = true;//当たったら減速のフラグをON
            }
        }
        //プレイヤーの高さ制限
        if (sph[0].pos.y <= -12000) {
            sph[0].pos.y = -12000;
            p_zmoveflg = false;
        }

        
        //------------------------------描画関数
        Model3d_draw();//3Dモデル描画
         //第二引数の回転角度をセット
        MV1SetRotationXYZ(rock.handle, VGet(sph[0].pos.z, 0.0f, 0.0f));
        //不法投棄物描画
        DrawSphere3D(obj.pos, obj.radius, 32, obj.color, GetColor(255, 255, 255), TRUE);
        

        //減速エリア描画
        for (int i = 0; i < DECELEARIA_NUM;i++) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);		//ブレンドモードをα(128/255)に設定
            DrawSphere3D(decelearia[i].pos, decelearia[i].radius, 32, decelearia[i].color, GetColor(255, 255, 255), TRUE);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
        }

        //減速エリアに入っている間に減速ちゅうの文字を描画
        if (decel.hit_flg) {
            Decel_aria_effect();
            SetFontSize(50);
            DrawFormatString(1000, 140, GetColor(0, 255, 255), "減速中");
            SetFontSize(20);
        }

        //不法投棄物に当たった時に表示させるもの
        if (htdrow.hitflg) {  DrawFormatString(100, 340, GetColor(0, 255, 255), "飛ばした距離を表示させる予定"); }

        DrawParam_Info();

        ScreenFlip();//裏画面の内容を表画面に反映する
    }

    Model3d_dlet();//3dモデル削除
    DxLib_End();
    // ソフトの終了
    return 0;
}