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
    //// ��ʃ��[�h�̐ݒ�
    //SetGraphMode(1920,1080, 32);
    //ChangeWindowMode(FALSE);

    // �E�C���h�E���[�h�ŋN��
    ChangeWindowMode(TRUE);

    SetGraphMode(1024, 768, 32);

    SetBackgroundColor(70, 130, 180);

    if (DxLib_Init() < 0)
    {
        // �G���[�����������璼���ɏI��
        return -1;
    }

    //--------------�������֐�

    Sph_init();//���̏�����
    Obj_init();//�s�@�������̏�����
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
        
       
        if (Sph_hit_check(sph, obj)) {
            Sph_hit(s_dis);
            htdrow.hitflg = true;
        }
        /*Sph_hit(s_dis);*/
        //------------------------------�`��֐�
        Model3d_draw();//3D���f���`��

        DrawSphere3D(obj.pos, obj.radius, 32, obj.color, GetColor(255, 255, 255), TRUE);
        

        for (int i = 0; i < 4;i++) {
            DrawSphere3D(deceleAria[i].pos, deceleAria[i].radius, 32, deceleAria[i].color, GetColor(255, 255, 255), TRUE);
        }


        if (htdrow.hitflg) { SetFontSize(30); DrawFormatString(100, 340, GetColor(0, 255, 255), "��΂���������������\��"); }

        /*Model_hit();*/
        /*Model_hit();*/

        DrawParam_Info();

        if (sph[0].pos.y <= -12000) {
            sph[0].pos.y = -12000;
            p_zmoveflg = false;
        }
        ScreenFlip();//����ʂ̓��e��\��ʂɔ��f����
    }

    Model3d_dlet();//3d���f���폜
    DxLib_End();
    // �\�t�g�̏I��
    return 0;
}