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

    LoadEffect();

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
    Init_Effect();

    goal_input_space = false; //ゴールした時のスペース入力

    deg = 22.5f;//飛ばす角度
    g_flg = false;
    obj_move = false;;
    haikeiflg = false;
    R = 70, G = 130, B = 180;//背景の色初期化
    
    // Ｚバッファを有効にする
    SetUseZBuffer3D(TRUE);
    // Ｚバッファへの書き込みを有効にする
    SetWriteZBuffer3D(TRUE);

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        KeyChecker();  //キー操作

        // 画面をクリア
        ClearDrawScreen();

        //HPが0だったらゲームオーバーに遷移
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
    // エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
    DeleteEffekseerEffect(e_bom.effect_handle);
    DeleteEffekseerEffect(e_orbit.effect_handle);
    DeleteEffekseerEffect(e_hit.effect_handle);
    DeleteEffekseerEffect(e_planet_hit.effect_handle);
    DeleteEffekseerEffect(e_move.effect_handle);
    
    // Effekseerを終了する。
    Effkseer_End();

    Model3d_dlet();//3dモデル削除
    DxLib_End();
    // ソフトの終了
    return 0;
}

void Gamemain() {

    //背景を宇宙（黒）にする処理
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
    //------------------------------入力関数
    Input_camera_move();//カメラ入力
    //------------------------------計算関数
    Camera_move();//カメラ動かす
    Effekseer_Sync3DSetting();//effectとカメラ同期
    Ground_model_hit();

   //不法投棄物とプレイヤーの当たり判定
    if (Sph_hit_check(sph, obj)) {
        /*Sph_hit(s_dis);*/
        htdrow.hitflg = true;
    }

    //不法投棄物を飛ばす処理
    if (htdrow.hitflg) {
        if (!e_orbit.play_effect_flg) {
            e_orbit.effect_flg = true;//軌道effectフラグオン
        }
        //プレイヤーが不法投棄に衝突した時のスピード保存する。
        if (speed_draw_str.last_speed_flg) {
            speed_draw_str.last_speed = fabsf(sph[0].zmove);
            speed_draw_str.last_speed_flg = false;
        }

        PlanetMove();//惑星移動処理

        //惑星を表示させる
        for (int i = 0; i < 4; i++) {
            planet[i].draw_flg = true;
        }

        camera.switching = true;//カメラ切り替えオン
        rad = deg * PI / 180.0f;//ラジアン変換

 /*       if (g_flg) {
            rad = -rad;
        }*/

        //不法投棄移動スピード
        _cos = cos(rad) * goal_obj.speed;
        _sin = sin(rad) * goal_obj.speed;

        //不法投棄の移動をとめる
        if (obj.pos.z + obj.radius >= planet[CheckPlanet(speed_draw_str.last_speed, sph[0].hp)].pos.z - planet[CheckPlanet(speed_draw_str.last_speed, sph[0].hp)].radius) {
            obj_move = true;
            if (!e_planet_hit.play_effect_flg) {
                e_planet_hit.effect_flg = true;
            }
            e_orbit.stop_effect_flg = true;
        }

        //不法投棄座標更新
        if (!obj_move) {
            obj.pos.z += _cos;
            obj.pos.y += _sin;
        }

        //爆発effect時間が3秒経過したら
        if (EffectExitTime() >= 3) {
           obj_switchflg = true;//カメラswitch切り替える
           haikeiflg = true;//空を暗くする
           obj.radius = 50.0f;//不法投棄の大きさを小さくする。
        };

        //effect描画　軌道
       /* StopEffekseer3DEffect(e_orbit.playing_effect_handle);*/
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
            e_hit.effect_flg = true;
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

    //減速エリアに入っているかチェック
    decel.hit_flg = false;//減速フラグ
    if (g_CollisionReflectionFlag == 0) {
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
         // 再生中のエフェクトを移動する。
        e_bom.playing_effect_handle = PlayEffekseer3DEffect(e_bom.effect_handle);
        SetPosPlayingEffekseer3DEffect(e_bom.playing_effect_handle, sph[0].pos.x, sph[0].pos.y, sph[0].pos.z);
    }

    //ゴールまで言ったら移動を止める
    if (htdrow.hitflg) {
        // 再生中のエフェクトを移動する。
        /*e_bom.playing_effect_handle = PlayEffekseer3DEffect(e_bom.effect_handle);*/
        /*SetPosPlayingEffekseer3DEffect(e_bom.playing_effect_handle, sph[0].pos.x, sph[0].v.y, sph[0].v.z);*/
        /*DrawEffekseer3D();*/
        if (g_goalflag == 0) {
            g_goalflag = 1;
            e_bom.playing_effect_handle = PlayEffekseer3DEffect(e_bom.effect_handle);
            SetPosPlayingEffekseer3DEffect(e_bom.playing_effect_handle, sph[0].pos.x, sph[0].pos.y, sph[0].pos.z);
        }
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

//effect再生
    if (e_move.effect_flg && sph[0].zmove > 75) {
        e_move.playing_effect_handle = PlayEffekseer3DEffect(e_move.effect_handle);//土煙effect再生
        e_move.effect_flg = false;
    } else if (sph[0].zmove <= 75) {
        StopEffekseer3DEffect(e_move.playing_effect_handle);
        e_move.playing_effect_handle = PlayEffekseer3DEffect(e_move.effect_handle);//土煙effect再生
    }
    SetPosPlayingEffekseer3DEffect(e_move.playing_effect_handle, sph[0].pos.x, sph[0].pos.y - sph[0].radius, sph[0].pos.z + sph[0].radius);
    
    if (e_orbit.effect_flg) {
        e_orbit.playing_effect_handle = PlayEffekseer3DEffect(e_orbit.effect_handle);//軌道effect再生
        e_orbit.play_effect_flg = true;
        e_orbit.effect_flg = false;
    }
    SetPosPlayingEffekseer3DEffect(e_orbit.playing_effect_handle, obj.pos.x, obj.pos.y, obj.pos.z);

    //衝突したらオフになっているか見ている。
    if (e_orbit.stop_effect_flg) {
        StopEffekseer3DEffect(e_orbit.playing_effect_handle);
    }

    if (e_hit.effect_flg) {
        e_hit.playing_effect_handle = PlayEffekseer3DEffect(e_hit.effect_handle);//ヒットした時のeffect再生
        e_hit.effect_flg = false;

        SetPosPlayingEffekseer3DEffect(e_hit.playing_effect_handle, sph[0].pos.x, sph[0].pos.y + sph[0].radius, sph[0].pos.z);
    }
    
    if (e_planet_hit.effect_flg) {
        e_planet_hit.playing_effect_handle = PlayEffekseer3DEffect(e_planet_hit.effect_handle);//ヒットした時のeffect再生
        e_planet_hit.play_effect_flg = true;
        e_planet_hit.effect_flg = false;
        SetPosPlayingEffekseer3DEffect(e_planet_hit.playing_effect_handle, obj.pos.x, obj.pos.y, obj.pos.z + obj.radius);
    }

    // Effekseerにより再生中のエフェクトを更新する。
    UpdateEffekseer3D();
    // Effekseerにより再生中のエフェクトを描画する。
    DrawEffekseer3D();


    DrawBox(50, 20, 390, 50, GetColor(255, 255, 255), TRUE);
    //体力描画
    
    DrawFormatString(55, 25, GetColor(0, 0, 0), "[HP: %d]", sph[0].hp);

    if (!htdrow.hitflg) {
        DrawFormatString(155, 25, GetColor(0, 0, 0), "スピード [ %.0f / 150 ]", speed_draw_str.speed);
    }
    else {
        DrawFormatString(155, 25, GetColor(0, 0, 0), "スピード [ %.0f / 150 ]", speed_draw_str.last_speed);
    }

    DrawFormatString(155, 100, GetColor(255, 255, 255), " 土煙 play handle %d ", e_move.playing_effect_handle);
    DrawFormatString(155, 120, GetColor(255, 255, 255), " ヒット play handle %d ", e_hit.playing_effect_handle);
    DrawFormatString(155, 160, GetColor(255, 255, 255), " 土煙 handle %d ", e_move.effect_handle);
    DrawFormatString(155, 180, GetColor(255, 255, 255), " ヒット handle %d ", e_hit.effect_handle);
    
    char str0[4][20] = { "月に衝突" ,"金星に衝突","水星に衝突","太陽に衝突" };

    DrawBox(780, 600, 1020, 620, GetColor(255, 255, 255), TRUE);
    if (obj_move) {
        DrawFormatString(350, 300, GetColor(255, 255, 255), "%s", str0[CheckPlanet(speed_draw_str.last_speed, sph[0].hp)]);
    }

    DrawFormatString(800, 600, GetColor(0, 0, 0), "2021/09/14/ 13:05");
}