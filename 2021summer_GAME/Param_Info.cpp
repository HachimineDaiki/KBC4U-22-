#include "Param_Info.h"
#include "User_Interface.h"
//初期化画面
void Init_Draw_Display() {
    speed_draw_str.color = GetColor(255, 255, 255);//文字色
    speed_draw_str.x = 100;
    speed_draw_str.y = 300;
    speed_draw_str.speed = 0.0f;
}

//画面描画表示
void DrawDisplay() {
    
    speed_draw_str.speed = sph[0].zmove;

    if (speed_draw_str.speed < 0) {
        speed_draw_str.speed = speed_draw_str.speed * -1;
    }

}

void DrawParam_Info() {
    SetFontSize(20);
    //SetFontSize(100);
    //DrawFormatString(341, 40, GetColor(255, 255, 0), " 成功 ");
    //SetFontSize(50);
    ////DrawFormatString(341, 140, GetColor(255, 255, 0), " 良い感じに\n  飛んだね ");
    //DrawFormatString(341, 140, GetColor(255, 255, 0), "   もっと\n  飛べるよ ");

    //DrawFormatString(300, 0, GetColor(255, 255, 255), "[smhx %.0f] [smhy %.0f] [smhz %.0f]", st_model_hit.lineres.Position.x, st_model_hit.lineres.Position.y, st_model_hit.lineres.Position.z);
    //DrawFormatString(300, 20, GetColor(255, 255, 255), "[g_frox %.0f] [g_froy %.0f] [g_froz %.0f]", g_frontpos2.Position.x, g_frontpos2.Position.y, g_frontpos2.Position.z);
    //DrawFormatString(300, 40, GetColor(255, 255, 255), "最大スコア　%.0f ", g_GoalFullScore);
    //// Camera.cppで使用している変数の数値など
    // 関数　Camera_move()　で使用
    //DrawFormatString(100, 20, GetColor(255, 255, 255), "カメラ縦角度 %.0f", g_cameraVAngle);
    //DrawFormatString(100, 40, GetColor(255, 255, 255), "カメラ横角度 %.0f", g_cameraHAngle);

    //DrawFormatString(100, 60, GetColor(255, 255, 255), "岩横角度 %.0f", g_p_direct);

    //// Hit_check.cppで使用している変数の数値など ////
    // 関数　Sph_hit(float dis)　で使用
    //for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
    //    DrawFormatString(500, 100 + (i + 1) * 20, GetColor(255, 255, 255), "[speed %.0f]", damege_aria[i].hit_speed);
    //}
    // 関数 Ground_model_hit_check(VECTOR MoveVector) で使用
    //DrawFormatString(300, 20, GetColor(255, 255, 255), "前に進んでいるか %d 進んでいると 0 ", g_frontmoveflg);
    //DrawFormatString(300, 40, GetColor(255, 255, 255), "前に坂があるか %d  ", g_frontpos2.HitFlag);
    //DrawFormatString(300, 60, GetColor(255, 255, 255), "ステージの上か %d", st_model_hit.lineres.HitFlag);
    
    DrawFormatString(100, 100, GetColor(255, 255, 255), "[sphx %.0f] [sphy %.0f] [sphz %.0f]", sph[0].pos.x, sph[0].pos.y, sph[0].pos.z);
    ////Player.cppで使用している変数の数値など
    //DrawFormatString(100, 250, GetColor(255, 255, 255), "%f", sph[0].zaccl);
    /*if(st_model_hit.gmoveflg==true)DrawFormatString(100, 200, GetColor(255, 255, 255), "true");
    if (st_model_hit.gmoveflg == false)DrawFormatString(100, 200, GetColor(255, 255, 255), "false");*/
    /*DrawFormatString(300, 300, GetColor(255, 255, 255), "handle num [ %d ]", rock[0].handle_num);
    DrawFormatString(100, 300, GetColor(255, 255, 255), "スピード [ %.0f /150 ]", sph[0].zmove);
    DrawFormatString(100, 250, GetColor(255, 0, 0), "向き %.1f, %.1f, %.1f ", st_model_hit.targetmovedirection.x, st_model_hit.targetmovedirection.y, st_model_hit.targetmovedirection.z);*/
}