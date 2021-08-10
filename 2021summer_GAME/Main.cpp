#include <Dxlib.h>
#include "Main.h"
#include "Init.h"
#include "Hit_check.h"
#include "Player.h"
#include "Camera.h"
#include "3Dmodel.h"
#include "Param_Info.h"
#include "Title.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // ��ʃ��[�h�̐ݒ�
    SetGraphMode(1024,768, 32);
    ChangeWindowMode(TRUE);

    //SetGraphMode(800, 600, 32);

    SetBackgroundColor(70, 130, 180);

    if (DxLib_Init() < 0)
    {
        // �G���[�����������璼���ɏI��
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);
    //--------------�������֐�
    Titleinit();
    gameMode = TITLE;
    Sph_init();//���̏�����
    Obj_init();//�s�@�������̏�����
    Damege_Init();//��Q���̏�����
    Decelearia_init();//�����G���A������
    Model_init();//���f��������
    Camera_set();//�J�����Z�b�g
    Model3d_load();//3D���f���ǂݍ���
    Model3d_init();//3D���f��������

    // �y�o�b�t�@��L���ɂ���
    SetUseZBuffer3D(TRUE);
    // �y�o�b�t�@�ւ̏������݂�L���ɂ���
    SetWriteZBuffer3D(TRUE);

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // ��ʂ��N���A
        ClearDrawScreen();

        //�Q�[���J��
        switch (gameMode)
        {
        case TITLE: Titledraw();
            break;
        case GAME: Gamemain();
            break;
        }

        ScreenFlip();//����ʂ̓��e��\��ʂɔ��f����
    }

    Model3d_dlet();//3d���f���폜
    DxLib_End();
    // �\�t�g�̏I��
    return 0;
}


void Gamemain() {
    //------------------------------���͊֐�
    Input_camera_move();//�J��������
    //------------------------------�v�Z�֐�
    Camera_move();//�J����������
    Ground_model_hit();

   //�s�@�������ƃv���C���[�̓����蔻��
    if (Sph_hit_check(sph, obj)) {
        Sph_hit(s_dis);
        htdrow.hitflg = true;
    }

    //�s�@���������΂�����
    if (htdrow.hitflg) {
        obj.pos.x += 1;
        obj.pos.y += 30 * cos(10) * 10;
        obj.pos.z += 200 * tan(10) * 10;
        //obj.pos.x += 90 * tan(5);
        DrawFormatString(100, 600, GetColor(0, 255, 255), "[x %.0f][y %.0f][z %.0f]", obj.pos.x, obj.pos.y, obj.pos.z);

    }

    //��Q���G���A�̓����蔻��
    for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
        if (Sph_ehit_chech(sph, damege_aria,i)) {
            sph[0].zmove -= 40;
            Sph_ehit(es_dis,i);
            /*DrawFormatString(0, 100, GetColor(0, 255, 255), "��������B");*/
        }
    }

    //�s�@������΂�
    if (htdrow.hitflg) {

        obj.zmove += -5 * tan(5);
    }

    //�����G���A�ɓ����Ă��邩�`�F�b�N
    decel.hit_flg = false;//�����t���O
    for (int i = 0; i < DECELE_ARIA_MAX; i++) {
        if (Decel_aria_check(sph, decele_aria, i)) {
            decel.hit_flg = true;//���������猸���̃t���O��ON
        }
    }
    
    //�S�[���܂Ō�������ړ����~�߂�
    if (htdrow.hitflg) {
        p_zmoveflg = false;
        g_p_Rotate = 0;
        sph[0].zmove = 0.0f;
        SetFontSize(50);
        DrawFormatString(500, 140, GetColor(0, 255, 255), " GOAL ");
        SetFontSize(20);
    }

    //------------------------------�`��֐�
    Model3d_draw();//3D���f���`��

    //�s�@�������`��
    DrawSphere3D(obj.pos, obj.radius, 32, obj.color, GetColor(255, 255, 255), TRUE);

    //��Q���`��
    for (int i = 0; i < DAMEGE_ARIA_MAX;i++) {
        DrawSphere3D(damege_aria[i].pos, damege_aria[i].radius, 16, damege_aria[i].color, GetColor(0, 0, 0), TRUE);//��Q������e�X�g�Ƃ��Ĉ�u���Ă���B
    }

    //�̗͕`��
    DrawFormatString(0, 300, GetColor(0, 255, 255), "[HP: %d]", sph->hp);

    //�����G���A�`��
    for (int i = 0; i < DECELE_ARIA_MAX; i++) {
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);		//�u�����h���[�h����(128/255)�ɐݒ�
        DrawSphere3D(decele_aria[i].pos, decele_aria[i].radius, 32, decele_aria[i].color, GetColor(255, 255, 255), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t
    }

    //�����G���A�ɓ����Ă���ԂɌ������イ�̕�����`��
    if (decel.hit_flg) {
        Decel_aria_effect();//�����G���A�ɓ��������̏���
        SetFontSize(50);//�����T�C�Y��ύX
        DrawFormatString(1000, 140, GetColor(0, 255, 255), "������");
        SetFontSize(20);//�����T�C�Y�����̃T�C�Y�ɕύX
    }

    //�p�����[�^�[��\�������鏈��
    DrawParam_Info();
}