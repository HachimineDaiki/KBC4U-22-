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

//��΂�����������
float disposx;
float disposy;
float disposz;


float dis_angle;
float dis_cos;
float dis_sin;

float R, G, B;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //�^�C�g��
    SetMainWindowText("���̕s�@�������ɏl�����I");
    // ��ʃ��[�h�̐ݒ�
    SetGraphMode(1024,768, 32);
    ChangeWindowMode(TRUE);

    //SetGraphMode(800, 600, 32);

    if (DxLib_Init() < 0)
    {
        // �G���[�����������璼���ɏI��
        return -1;
    }
    // Effekseer������������B
    // �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
    if (Effekseer_Init(8000) == -1)
    {
        DxLib_End();
        return -1;
    }

    LoadEffect();

    // DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
    // Effekseer���g�p����ɂ͕K���ݒ肷��B
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    // �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
    // Effekseer���g�p����ꍇ�͕K���ݒ肷��B
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
    // �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
    // �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    SetDrawScreen(DX_SCREEN_BACK);
    //--------------�������֐�
    Titleinit();
    Gameoverinit();
    gameMode = TITLE;
    Sph_init();//���̏�����
    Obj_init();//�s�@�������̏�����
    Damege_Init();//��Q���̏�����
    Decelearia_init();//�����G���A������
    Model_init();//���f��������
    Camera_set();//�J�����Z�b�g
    Model3d_load();//3D���f���ǂݍ���
    Model3d_init();//3D���f��������
    UIinit();//UI�̏�����
    Init_Draw_Display();//��ʕ`�揉����
    InitTime(); //���ԏ�����
    PlanetInit();
    Init_Effect();

    goal_input_space = false; //�S�[���������̃X�y�[�X����

    deg = 22.5f;//��΂��p�x
    g_flg = false;
    obj_move = false;;
    haikeiflg = false;
    R = 70, G = 130, B = 180;//�w�i�̐F������
    
    // �y�o�b�t�@��L���ɂ���
    SetUseZBuffer3D(TRUE);
    // �y�o�b�t�@�ւ̏������݂�L���ɂ���
    SetWriteZBuffer3D(TRUE);

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        KeyChecker();  //�L�[����

        // ��ʂ��N���A
        ClearDrawScreen();

        //HP��0��������Q�[���I�[�o�[�ɑJ��
        if (sph[0].hp <= 0) {
            EffectTime();
            if (effect_time.time >= 2) {
                gameMode = GAMEOVER; //�Q�[�����[�h
            }
         }

        //�Q�[���J��
        switch (gameMode)
        {
        case TITLE: Titledraw();
            break;
        case GAME: Gamemain();
            break;
        case GAMEOVER:Gameoverdraw();
            break;
        }

        //�Q�[���I��
        if (gameexit) {
            return -1;
        }
        ScreenFlip();//����ʂ̓��e��\��ʂɔ��f����
    }
    // �G�t�F�N�g���\�[�X���폜����B(Effekseer�I�����ɔj�������̂ō폜���Ȃ��Ă�����)
    DeleteEffekseerEffect(e_bom.effect_handle);
    DeleteEffekseerEffect(e_orbit.effect_handle);
    DeleteEffekseerEffect(e_hit.effect_handle);
    DeleteEffekseerEffect(e_planet_hit.effect_handle);
    DeleteEffekseerEffect(e_move.effect_handle);
    
    // Effekseer���I������B
    Effkseer_End();

    Model3d_dlet();//3d���f���폜
    DxLib_End();
    // �\�t�g�̏I��
    return 0;
}

void Gamemain() {

    //�w�i���F���i���j�ɂ��鏈��
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
    //------------------------------���͊֐�
    Input_camera_move();//�J��������
    //------------------------------�v�Z�֐�
    Camera_move();//�J����������
    Effekseer_Sync3DSetting();//effect�ƃJ��������
    Ground_model_hit();

   //�s�@�������ƃv���C���[�̓����蔻��
    if (Sph_hit_check(sph, obj)) {
        /*Sph_hit(s_dis);*/
        htdrow.hitflg = true;
    }

    //�s�@���������΂�����
    if (htdrow.hitflg) {
        if (!e_orbit.play_effect_flg) {
            e_orbit.effect_flg = true;//�O��effect�t���O�I��
        }
        //�v���C���[���s�@�����ɏՓ˂������̃X�s�[�h�ۑ�����B
        if (speed_draw_str.last_speed_flg) {
            speed_draw_str.last_speed = fabsf(sph[0].zmove);
            speed_draw_str.last_speed_flg = false;
        }

        PlanetMove();//�f���ړ�����

        //�f����\��������
        for (int i = 0; i < 4; i++) {
            planet[i].draw_flg = true;
        }

        camera.switching = true;//�J�����؂�ւ��I��
        rad = deg * PI / 180.0f;//���W�A���ϊ�

 /*       if (g_flg) {
            rad = -rad;
        }*/

        //�s�@�����ړ��X�s�[�h
        _cos = cos(rad) * goal_obj.speed;
        _sin = sin(rad) * goal_obj.speed;

        //�s�@�����̈ړ����Ƃ߂�
        if (obj.pos.z + obj.radius >= planet[CheckPlanet(speed_draw_str.last_speed, sph[0].hp)].pos.z - planet[CheckPlanet(speed_draw_str.last_speed, sph[0].hp)].radius) {
            obj_move = true;
            if (!e_planet_hit.play_effect_flg) {
                e_planet_hit.effect_flg = true;
            }
            e_orbit.stop_effect_flg = true;
        }

        //�s�@�������W�X�V
        if (!obj_move) {
            obj.pos.z += _cos;
            obj.pos.y += _sin;
        }

        //����effect���Ԃ�3�b�o�߂�����
        if (EffectExitTime() >= 3) {
           obj_switchflg = true;//�J����switch�؂�ւ���
           haikeiflg = true;//����Â�����
           obj.radius = 50.0f;//�s�@�����̑傫��������������B
        };

        //effect�`��@�O��
       /* StopEffekseer3DEffect(e_orbit.playing_effect_handle);*/
        /*DrawLine3D(obj.pos, VAdd(obj.pos, VGet(0, obj.radius -500, 0)), GetColor(255, 255, 255));*/
        //�E�e�̔��ˊp�x��atan2(�ڕW�܂ł̋����x�A�ڕW�܂ł̋����w)
        //�E�e�̈ړ��ʂw��cos(�e�̔��ˊp�x)�~�e�̃X�s�[�h
        //�E�e�̈ړ��ʂx��sin(�e�̔��ˊp�x)�~�e�̃X�s�[�h
    }

    //��Q���G���A�̓����蔻��
    for (int i = 0; i < DAMEGE_ARIA_MAX; i++) {
        if (Sph_ehit_chech(sph, damege_aria,i)) {
            g_CollisionReflectionFlag = 1;//�Փ˃t���O���P�ɂ���
            Damege_aria_Decele();
            Sph_ehit(es_dis,i);
            sph[0].zmove = P_CollisionVelocity();//�Փˌ�̑��x
            e_hit.effect_flg = true;
        }
    }

    //�s�@������΂�
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

    //�����G���A�ɓ����Ă��邩�`�F�b�N
    decel.hit_flg = false;//�����t���O
    if (g_CollisionReflectionFlag == 0) {
        for (int i = 0; i < DECELE_ARIA_MAX; i++) {
            if (Decel_aria_check(sph, decele_aria, i)) {
                decel.hit_flg = true;//���������猸���̃t���O��ON
            }
        }
    }
    
   

    //------------------------------�`��֐�
    Model3d_draw();//3D���f���`��
    //�s�@�������`��
    DrawSphere3D(obj.pos, obj.radius, 32, obj.color, GetColor(255, 255, 255), TRUE);
    DrawPlanet();
    //��Q���`��
    for (int i = 0; i < DAMEGE_ARIA_MAX;i++) {
        if (damege_aria[i].obj_flag) {
            MV1DrawModel(e_rock[i].handle);

            //SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);		//�u�����h���[�h����(128/255)�ɐݒ�
            //DrawSphere3D(damege_aria[i].pos, damege_aria[i].radius, 32, damege_aria[i].color, GetColor(255, 255, 255), TRUE);
            //SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t
        }
    }

    DrawDisplay();//��ʏ��

    //�����G���A�`��
    //for (int i = 0; i < DECELE_ARIA_MAX; i++) {
    //    //SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);		//�u�����h���[�h����(128/255)�ɐݒ�
    //    //DrawSphere3D(decele_aria[i].pos, decele_aria[i].radius, 32, decele_aria[i].color, GetColor(255, 255, 255), TRUE);
    //    //SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t
    //}

    //�����G���A�ɓ����Ă���ԂɌ������イ�̕�����`��
    if (decel.hit_flg) {
        Decel_aria_effect();//�����G���A�ɓ��������̏���
        SetFontSize(50);//�����T�C�Y��ύX
        SetFontSize(20);//�����T�C�Y�����̃T�C�Y�ɕύX
    }
   
    //�p�����[�^�[��\�������鏈��
    DrawParam_Info();
    //�S�[���܂ōs������s�@�������̔�񂾋�����\��
    if (htdrow.hitflg) {
        UIdraw();
    }
    //�G�t�F�N�g���g��
    if (sph[0].hp <= 0) {
        g_goalflag = true;
        p_zmoveflg = false;
        // �G�t�F�N�g���Đ�����B
         // �Đ����̃G�t�F�N�g���ړ�����B
        e_bom.playing_effect_handle = PlayEffekseer3DEffect(e_bom.effect_handle);
        SetPosPlayingEffekseer3DEffect(e_bom.playing_effect_handle, sph[0].pos.x, sph[0].pos.y, sph[0].pos.z);
    }

    //�S�[���܂Ō�������ړ����~�߂�
    if (htdrow.hitflg) {
        // �Đ����̃G�t�F�N�g���ړ�����B
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
            if (g_KeyFlg & PAD_INPUT_2) {  //B�L�[�ŃX�^�[�g
                WaitTimer(1000);
                All_Init();
                gameMode = 0;

            }
        }
    }

//effect�Đ�
    if (e_move.effect_flg && sph[0].zmove > 75) {
        e_move.playing_effect_handle = PlayEffekseer3DEffect(e_move.effect_handle);//�y��effect�Đ�
        e_move.effect_flg = false;
    } else if (sph[0].zmove <= 75) {
        StopEffekseer3DEffect(e_move.playing_effect_handle);
        e_move.playing_effect_handle = PlayEffekseer3DEffect(e_move.effect_handle);//�y��effect�Đ�
    }
    SetPosPlayingEffekseer3DEffect(e_move.playing_effect_handle, sph[0].pos.x, sph[0].pos.y - sph[0].radius, sph[0].pos.z + sph[0].radius);
    
    if (e_orbit.effect_flg) {
        e_orbit.playing_effect_handle = PlayEffekseer3DEffect(e_orbit.effect_handle);//�O��effect�Đ�
        e_orbit.play_effect_flg = true;
        e_orbit.effect_flg = false;
    }
    SetPosPlayingEffekseer3DEffect(e_orbit.playing_effect_handle, obj.pos.x, obj.pos.y, obj.pos.z);

    //�Փ˂�����I�t�ɂȂ��Ă��邩���Ă���B
    if (e_orbit.stop_effect_flg) {
        StopEffekseer3DEffect(e_orbit.playing_effect_handle);
    }

    if (e_hit.effect_flg) {
        e_hit.playing_effect_handle = PlayEffekseer3DEffect(e_hit.effect_handle);//�q�b�g��������effect�Đ�
        e_hit.effect_flg = false;

        SetPosPlayingEffekseer3DEffect(e_hit.playing_effect_handle, sph[0].pos.x, sph[0].pos.y + sph[0].radius, sph[0].pos.z);
    }
    
    if (e_planet_hit.effect_flg) {
        e_planet_hit.playing_effect_handle = PlayEffekseer3DEffect(e_planet_hit.effect_handle);//�q�b�g��������effect�Đ�
        e_planet_hit.play_effect_flg = true;
        e_planet_hit.effect_flg = false;
        SetPosPlayingEffekseer3DEffect(e_planet_hit.playing_effect_handle, obj.pos.x, obj.pos.y, obj.pos.z + obj.radius);
    }

    // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
    UpdateEffekseer3D();
    // Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
    DrawEffekseer3D();


    DrawBox(50, 20, 390, 50, GetColor(255, 255, 255), TRUE);
    //�̗͕`��
    
    DrawFormatString(55, 25, GetColor(0, 0, 0), "[HP: %d]", sph[0].hp);

    if (!htdrow.hitflg) {
        DrawFormatString(155, 25, GetColor(0, 0, 0), "�X�s�[�h [ %.0f / 150 ]", speed_draw_str.speed);
    }
    else {
        DrawFormatString(155, 25, GetColor(0, 0, 0), "�X�s�[�h [ %.0f / 150 ]", speed_draw_str.last_speed);
    }

    DrawFormatString(155, 100, GetColor(255, 255, 255), " �y�� play handle %d ", e_move.playing_effect_handle);
    DrawFormatString(155, 120, GetColor(255, 255, 255), " �q�b�g play handle %d ", e_hit.playing_effect_handle);
    DrawFormatString(155, 160, GetColor(255, 255, 255), " �y�� handle %d ", e_move.effect_handle);
    DrawFormatString(155, 180, GetColor(255, 255, 255), " �q�b�g handle %d ", e_hit.effect_handle);
    
    char str0[4][20] = { "���ɏՓ�" ,"�����ɏՓ�","�����ɏՓ�","���z�ɏՓ�" };

    DrawBox(780, 600, 1020, 620, GetColor(255, 255, 255), TRUE);
    if (obj_move) {
        DrawFormatString(350, 300, GetColor(255, 255, 255), "%s", str0[CheckPlanet(speed_draw_str.last_speed, sph[0].hp)]);
    }

    DrawFormatString(800, 600, GetColor(0, 0, 0), "2021/09/14/ 13:05");
}