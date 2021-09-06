#include <Dxlib.h>
#include "Main.h"
#include "Init.h"
#include "Hit_check.h"
#include "Player.h"
#include "Camera.h"
#include "3Dmodel.h"
#include "Param_Info.h"
#include "Title.h"
#include "Gameover.h"
#include "User_Interface.h"
#include"KeyCheck.h"
// EffekseerForDXLib.hをインクルードします。
#include "EffekseerForDXLib.h"

#define PI 3.14

bool g_flg;
float _cos;
float _sin;

float deg;
float rad;

//飛ばす距離初期化
float disposx;
float disposy;
float disposz;


float dis_angle;
float dis_cos;
float dis_sin;

float R, G, B;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //タイトル
    SetMainWindowText("この不法投棄物に粛清を！");
    // 画面モードの設定
    SetGraphMode(1024,768, 32);
    ChangeWindowMode(TRUE);

    //SetGraphMode(800, 600, 32);

    if (DxLib_Init() < 0)
    {
        // エラーが発生したら直ちに終了
        return -1;
    }
    // Effekseerを初期化する。
    // 引数には画面に表示する最大パーティクル数を設定する。
    if (Effekseer_Init(8000) == -1)
    {
        DxLib_End();
        return -1;
    }
    // DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
    // Effekseerを使用するには必ず設定する。
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    // フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
    // Effekseerを使用する場合は必ず設定する。
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DXライブラリのデバイスロストした時のコールバックを設定する。
    // ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
    // ただし、DirectX11を使用する場合は実行する必要はない。
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();


    SetDrawScreen(DX_SCREEN_BACK);
    //--------------初期化関数
    Titleinit();
    Gameoverinit();
    gameMode = TITLE;
    Sph_init();//球の初期化
    Obj_init();//不法投棄物の初期化
    Damege_Init();//障害物の初期化
    Decelearia_init();//減速エリア初期化
    Model_init();//モデル初期化
    Camera_set();//カメラセット
    Model3d_load();//3Dモデル読み込み
    Model3d_init();//3Dモデル初期化
    UIinit();//UIの初期化
    Init_Draw_Display();//画面描画初期化
    InitTime(); //時間初期化
    PlanetInit();
    goal_input_space = false; //ゴールした時のスペース入力

    deg = 22.5f;//飛ばす角度
    g_flg = false;

    haikeiflg = false;
    R = 70, G = 130, B = 180;//背景の色初期化

    // Ｚバッファを有効にする
    SetUseZBuffer3D(TRUE);
    // Ｚバッファへの書き込みを有効にする
    SetWriteZBuffer3D(TRUE);


    // DXライブラリのカメラとEffekseerのカメラを同期する。
    Effekseer_Sync3DSetting();


    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        KeyChecker();  //キー操作

        // 画面をクリア
        ClearDrawScreen();

        if (sph[0].hp <= 0) {
            EffectTime();
            if (effect_time.time >= 2) {
                gameMode = GAMEOVER; //ゲームモード
            }
         }

        //ゲーム遷移
        switch (gameMode)
        {
        case TITLE: Titledraw();
            break;
        case GAME: Gamemain();
            break;
        case GAMEOVER:Gameoverdraw();
            break;
        }

        //ゲーム終了
        if (gameexit) {
            return -1;
        }
        ScreenFlip();//裏画面の内容を表画面に反映する
    }
    // Effekseerを終了する。
    Effkseer_End();

    Model3d_dlet();//3dモデル削除
    DxLib_End();
    // ソフトの終了
    return 0;
}

void Gamemain() {
    
    if (!haikeiflg) {
        R = 70;
        G = 130;
        B = 180;
    }
    else {
        R--;
        G--;
        B--;

        if (R < 0) {
            R = 0;
        }
        else if (G < 0) {
            G = 0;
        }
        else if (B<0) {
            B = 0;
        }
    }

    SetBackgroundColor(R, G, B);
    //読み込む時に大きさを指定する。
    int effectResourceHandle = LoadEffekseerEffect("3Dmodel/exploadSample03.efk", 50.0f);
    // 何でもいいので画像を読み込む。
    int grBackgroundHandle = LoadGraph(_T("images/Star.png"));
    // 再生中のエフェクトのハンドルを初期化する。
    int playingEffectHandle = -1;
    //------------------------------入力関数
    Input_camera_move();//カメラ入力
    //------------------------------計算関数
    Camera_move();//カメラ動かす
    Ground_model_hit();

   //不法投棄物とプレイヤーの当たり判定
    if (Sph_hit_check(sph, obj)) {
        /*Sph_hit(s_dis);*/
        htdrow.hitflg = true;
    }

    //不法投棄物を飛ばす処理
    if (htdrow.hitflg) {
     //   obj.pos.x += 1;
        //obj.pos.y += 30 * cos(10) * 10;
        //obj.pos.z += 200 * tan(10) * 10;

        //obj.pos.z += obj.zmove;
        //g_GoalFullScore += g_dist;
        for (int i = 0; i < 4; i++) {
            planet[i].draw_flg = true;
        }

        camera.switching = true;
        rad = deg * PI / 180.0f;

        if (g_flg) {
            rad = -rad;
        }

        _cos = cos(rad)*100;
        _sin = sin(rad)*100;

        obj.pos.z += _cos;
        obj.pos.y += _sin;

        if (obj.pos.y >= -15000.0f) {
            /*haikeiflg = true;*/
            obj_switchflg = true;
        }
        
        obj.pos.z += _cos;
        obj.pos.y += _sin;

        /*DrawLine3D(obj.pos, VAdd(obj.pos, VGet(0, obj.radius -500, 0)), GetColor(255, 255, 255));*/
        //・弾の発射角度＝atan2(目標までの距離Ｙ、目標までの距離Ｘ)
        //・弾の移動量Ｘ＝cos(弾の発射角度)×弾のスピード
        //・弾の移動量Ｙ＝sin(弾の発射角度)×弾のスピード

    }

    //障害物エリアの当たり判定
    for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
        if (Sph_ehit_chech(sph, damege_aria,i)) {
            g_CollisionReflectionFlag = 1;//衝突フラグを１にする
            Damege_aria_Decele();
            Sph_ehit(es_dis,i);
            sph[0].zmove = P_CollisionVelocity();//衝突後の速度
        }
    }

    //不法投棄飛ばす
    if (htdrow.hitflg) {
        if (obj.zmove > 0) {
            //obj.zmove = obj.zmove * 0.99;
            obj.zmove = obj.zmove - 754;
        }
        else if (obj.zmove <= 0) {
            obj.zmove = 0;
            goal_input_space = true;
        }

        if (g_dist > 0) {
            //g_dist = g_dist * 0.99;
            g_dist = g_dist - 754;
        }
        else if (g_dist <= 0) {
            g_dist = 0;
        }
    }

    // 再生中のエフェクトを移動する。
    SetPosPlayingEffekseer3DEffect(playingEffectHandle, sph[0].pos.x, sph[0].v.y, sph[0].v.z);

    // Effekseerにより再生中のエフェクトを更新する。
    UpdateEffekseer3D();

    //減速エリアに入っているかチェック
    if (g_CollisionReflectionFlag == 0) {
        decel.hit_flg = false;//減速フラグ
        for (int i = 0; i < DECELE_ARIA_MAX; i++) {
            if (Decel_aria_check(sph, decele_aria, i)) {
                decel.hit_flg = true;//当たったら減速のフラグをON
            }
        }
    }
    
   

    //------------------------------描画関数
    Model3d_draw();//3Dモデル描画
    //不法投棄物描画
    DrawSphere3D(obj.pos, obj.radius, 32, obj.color, GetColor(255, 255, 255), TRUE);
    DrawPlanet();
    //障害物描画
    for (int i = 0; i < DAMEGE_ARIA_MAX;i++) {
        if (damege_aria[i].obj_flag) {
            MV1DrawModel(e_rock[i].handle);

            //SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);		//ブレンドモードをα(128/255)に設定
            //DrawSphere3D(damege_aria[i].pos, damege_aria[i].radius, 32, damege_aria[i].color, GetColor(255, 255, 255), TRUE);
            //SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
        }
    }

    
    //DrawFormatString(0, 320, GetColor(0, 255, 255), "[Time: %d]", EffectTime()); //コメントにしないとゲーム開始からカウントが始まる
    DrawDisplay();//画面情報

    //減速エリア描画
    //for (int i = 0; i < DECELE_ARIA_MAX; i++) {
    //    //SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);		//ブレンドモードをα(128/255)に設定
    //    //DrawSphere3D(decele_aria[i].pos, decele_aria[i].radius, 32, decele_aria[i].color, GetColor(255, 255, 255), TRUE);
    //    //SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
    //}

    //減速エリアに入っている間に減速ちゅうの文字を描画
    if (decel.hit_flg) {
        Decel_aria_effect();//減速エリアに入った時の処理
        SetFontSize(50);//文字サイズを変更
        SetFontSize(20);//文字サイズを元のサイズに変更
    }
    /*DrawFormatString(300, 300, speed_draw_str.color, "Obj座標[ %.0f %.0f %.0f", obj.pos.x, obj.pos.y, obj.pos.z);
    DrawFormatString(100, 250, GetColor(255, 0, 0), "向き %.1f, %.1f, %.1f ", st_model_hit.targetmovedirection.x, st_model_hit.targetmovedirection.y, st_model_hit.targetmovedirection.z);*/
    //パラメーターを表示させる処理
    DrawParam_Info();
    //ゴールまで行ったら不法投棄物の飛んだ距離を表示
    if (htdrow.hitflg) {
        UIdraw();
    }
    //エフェクトを使う
    if (sph[0].hp <= 0) {
        g_goalflag = true;
        p_zmoveflg = false;
        // エフェクトを再生する。
        playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);
        //DrawEffect();
        // Effekseerにより再生中のエフェクトを描画する。
        DrawEffekseer3D();
    }

    //ゴールまで言ったら移動を止める
    if (htdrow.hitflg) {
        playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);
        DrawEffekseer3D();
        if (g_goalflag == 0) {
            obj.zmove = fabsf(sph[0].zmove * 499.5) + (sph[0].hp * 249.75);
            g_goalflag = 1;
            playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);
            DrawEffekseer3D();
        }
        StopEffekseer3DEffect(playingEffectHandle);
        p_zmoveflg = false;
        g_p_Rotate = 0;
        sph[0].zmove = 0.0f;
        SetFontSize(50);
        //DrawFormatString(512, 140, GetColor(0, 255, 255), " GOAL ");
        SetFontSize(20);
        Distance_Calculation();
        Judgement();
        if (goal_input_space) {
            if (g_KeyFlg & PAD_INPUT_2) {  //Bキーでスタート
                WaitTimer(1000);
                All_Init();
                gameMode = 0;

            }
        }
    }

    DrawBox(50, 20, 390, 50, GetColor(255, 255, 255), TRUE);
    //体力描画
    DrawFormatString(100, 300, GetColor(255, 255, 255), "[camera V: %.4f]", CameraVAngle);

    DrawFormatString(55, 25, GetColor(0, 0, 0), "[HP: %d]", sph[0].hp);
    DrawFormatString(155, 25, GetColor(0,0,0), "スピード [ %.0f / 150 ]", speed_draw_str.speed);
    /*DrawFormatString(0, 360, GetColor(0, 255, 255), "[ x %.0f y %.0f z %.0f]", obj.pos.x, obj.pos.y, obj.pos.z);*/
    //for (int i = 0; i<MAXOBJ; i++) {
    //    DrawFormatString(500, 200 + (i + 1) * 20, GetColor(0, 255, 255), "[ x %.0f y %.0f z %.0f]", d_obj[i].pos.x, d_obj[i].pos.y, d_obj[i].pos.z);
    //}
    // エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
    DeleteEffekseerEffect(effectResourceHandle);
}