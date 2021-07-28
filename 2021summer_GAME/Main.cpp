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
    // ��ʃ��[�h�̐ݒ�
    SetGraphMode(1920,1080, 32);
    ChangeWindowMode(FALSE);

    //SetGraphMode(800, 600, 32);

    SetBackgroundColor(70, 130, 180);

    if (DxLib_Init() < 0)
    {
        // �G���[�����������璼���ɏI��
        return -1;
    }

    //--------------�������֐�

    Sph_init();//���̏�����
    Obj_init();//�s�@�������̏�����
    Decelearia_init();//�����G���A������
    Model_init();
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

        //------------------------------���͊֐�
        Input_camera_move();//�J��������
        //------------------------------�v�Z�֐�
        Ground_model_hit();
        Camera_move();//�J����������
       
        //�s�@�������ƃv���C���[�̓����蔻��
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


        //�����G���A�ɓ����Ă��邩�`�F�b�N
        decel.hit_flg = false;//�����t���O
        for (int i = 0; i < DECELEARIA_NUM; i++) {
            if (Decel_aria_check(sph, decelearia,i)) {
                decel.hit_flg = true;//���������猸���̃t���O��ON
            }
        }
        //�v���C���[�̍�������
        if (sph[0].pos.y <= -12000) {
            sph[0].pos.y = -12000;
            p_zmoveflg = false;
        }

        
        //------------------------------�`��֐�
        Model3d_draw();//3D���f���`��
         //�������̉�]�p�x���Z�b�g
        MV1SetRotationXYZ(rock.handle, VGet(sph[0].pos.z, 0.0f, 0.0f));
        //�s�@�������`��
        DrawSphere3D(obj.pos, obj.radius, 32, obj.color, GetColor(255, 255, 255), TRUE);
        

        //�����G���A�`��
        for (int i = 0; i < DECELEARIA_NUM;i++) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);		//�u�����h���[�h����(128/255)�ɐݒ�
            DrawSphere3D(decelearia[i].pos, decelearia[i].radius, 32, decelearia[i].color, GetColor(255, 255, 255), TRUE);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t
        }

        //�����G���A�ɓ����Ă���ԂɌ������イ�̕�����`��
        if (decel.hit_flg) {
            Decel_aria_effect();
            SetFontSize(50);
            DrawFormatString(1000, 140, GetColor(0, 255, 255), "������");
            SetFontSize(20);
        }

        //�s�@�������ɓ����������ɕ\�����������
        if (htdrow.hitflg) {  DrawFormatString(100, 340, GetColor(0, 255, 255), "��΂���������\��������\��"); }

        DrawParam_Info();

        ScreenFlip();//����ʂ̓��e��\��ʂɔ��f����
    }

    Model3d_dlet();//3d���f���폜
    DxLib_End();
    // �\�t�g�̏I��
    return 0;
}