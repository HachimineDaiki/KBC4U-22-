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
        P_move();//�v���C���[����
        Input_camera_move();//�J��������

        //------------------------------�v�Z�֐�
        Camera_move();//�J����������
        Sph_Gravity();//�d��
        Model_hit_check();//���f��
       

        //------------------------------�`��֐�

        DrawSphere3D(VGet(sph[0].x, sph[0].y, sph[0].z), sph[0].radius, 32, sph[0].color, GetColor(255, 255, 255), TRUE);
        DrawFormatString(100, 100, GetColor(255, 255, 255), "[x %.0f] [y %.0f] [z %.0f]", sph[0].x, sph[0].y, sph[0].z);
       

        Model3d_draw();//3D���f���`��
        Model_hit();

        ScreenFlip();//����ʂ̓��e��\��ʂɔ��f����
    }

    Model3d_dlet();//3d���f���폜
    DxLib_End();
    // �\�t�g�̏I��
    return 0;
}