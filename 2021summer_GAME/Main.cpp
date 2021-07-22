#include <Dxlib.h>
#include "Init.h"
#include "Hit_check.h"
#include "Player.h"
#include "Camera.h"
#include "3Dmodel.h"

MV1_COLL_RESULT_POLY_DIM HitPolyDim[TREE_NUM];
Sph sph[2];
Model ground;
Model wall; 
float  vx, vy, vz;
int wall_handle;
int ground_handle;
int tree_handle[TREE_NUM];
StageModelHit st_model_hit;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // ��ʃ��[�h�̐ݒ�
    SetGraphMode(1920,1080, 32);
    ChangeWindowMode(FALSE);
    SetBackgroundColor(70, 130, 180);

    if (DxLib_Init() < 0)
    {
        // �G���[�����������璼���ɏI��
        return -1;
    }

    //--------------�������֐�

    Sph_init();//���̏�����
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
        //Model_hit_check();//���f��
       
        
        //------------------------------�`��֐�
        Model3d_draw();//3D���f���`��
        DrawFormatString(100, 320, GetColor(255, 255, 255), "%.0f", sph[0].v0y);
        DrawFormatString(100, 340, GetColor(255, 255, 255), "%.0f", sph[0].pos.y);
        /*Model_hit();*/

        ScreenFlip();//����ʂ̓��e��\��ʂɔ��f����
    }

    Model3d_dlet();//3d���f���폜
    DxLib_End();
    // �\�t�g�̏I��
    return 0;
}