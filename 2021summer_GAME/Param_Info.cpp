#include "Param_Info.h"
#include "User_Interface.h"
//���������
void Init_Draw_Display() {
    speed_draw_str.color = GetColor(255, 255, 255);//�����F
    speed_draw_str.x = 100;
    speed_draw_str.y = 300;
    speed_draw_str.speed = 0.0f;
}

//��ʕ`��\��
void DrawDisplay() {
    
    speed_draw_str.speed = sph[0].zmove;

    if (speed_draw_str.speed < 0) {
        speed_draw_str.speed = speed_draw_str.speed * -1;
    }

}

void DrawParam_Info() {
    SetFontSize(20);
    //SetFontSize(100);
    //DrawFormatString(341, 40, GetColor(255, 255, 0), " ���� ");
    //SetFontSize(50);
    ////DrawFormatString(341, 140, GetColor(255, 255, 0), " �ǂ�������\n  ��񂾂� ");
    //DrawFormatString(341, 140, GetColor(255, 255, 0), "   ������\n  ��ׂ�� ");

    //DrawFormatString(300, 0, GetColor(255, 255, 255), "[smhx %.0f] [smhy %.0f] [smhz %.0f]", st_model_hit.lineres.Position.x, st_model_hit.lineres.Position.y, st_model_hit.lineres.Position.z);
    //DrawFormatString(300, 20, GetColor(255, 255, 255), "[g_frox %.0f] [g_froy %.0f] [g_froz %.0f]", g_frontpos2.Position.x, g_frontpos2.Position.y, g_frontpos2.Position.z);
    //DrawFormatString(300, 40, GetColor(255, 255, 255), "�ő�X�R�A�@%.0f ", g_GoalFullScore);
    //// Camera.cpp�Ŏg�p���Ă���ϐ��̐��l�Ȃ�
    // �֐��@Camera_move()�@�Ŏg�p
    //DrawFormatString(100, 20, GetColor(255, 255, 255), "�J�����c�p�x %.0f", g_cameraVAngle);
    //DrawFormatString(100, 40, GetColor(255, 255, 255), "�J�������p�x %.0f", g_cameraHAngle);

    //DrawFormatString(100, 60, GetColor(255, 255, 255), "�≡�p�x %.0f", g_p_direct);

    //// Hit_check.cpp�Ŏg�p���Ă���ϐ��̐��l�Ȃ� ////
    // �֐��@Sph_hit(float dis)�@�Ŏg�p
    //for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
    //    DrawFormatString(500, 100 + (i + 1) * 20, GetColor(255, 255, 255), "[speed %.0f]", damege_aria[i].hit_speed);
    //}
    // �֐� Ground_model_hit_check(VECTOR MoveVector) �Ŏg�p
    //DrawFormatString(300, 20, GetColor(255, 255, 255), "�O�ɐi��ł��邩 %d �i��ł���� 0 ", g_frontmoveflg);
    //DrawFormatString(300, 40, GetColor(255, 255, 255), "�O�ɍ₪���邩 %d  ", g_frontpos2.HitFlag);
    //DrawFormatString(300, 60, GetColor(255, 255, 255), "�X�e�[�W�̏ォ %d", st_model_hit.lineres.HitFlag);
    
    DrawFormatString(100, 100, GetColor(255, 255, 255), "[sphx %.0f] [sphy %.0f] [sphz %.0f]", sph[0].pos.x, sph[0].pos.y, sph[0].pos.z);
    ////Player.cpp�Ŏg�p���Ă���ϐ��̐��l�Ȃ�
    //DrawFormatString(100, 250, GetColor(255, 255, 255), "%f", sph[0].zaccl);
    /*if(st_model_hit.gmoveflg==true)DrawFormatString(100, 200, GetColor(255, 255, 255), "true");
    if (st_model_hit.gmoveflg == false)DrawFormatString(100, 200, GetColor(255, 255, 255), "false");*/
    /*DrawFormatString(300, 300, GetColor(255, 255, 255), "handle num [ %d ]", rock[0].handle_num);
    DrawFormatString(100, 300, GetColor(255, 255, 255), "�X�s�[�h [ %.0f /150 ]", sph[0].zmove);
    DrawFormatString(100, 250, GetColor(255, 0, 0), "���� %.1f, %.1f, %.1f ", st_model_hit.targetmovedirection.x, st_model_hit.targetmovedirection.y, st_model_hit.targetmovedirection.z);*/
}