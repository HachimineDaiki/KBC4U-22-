#include<DxLib.h>
#include"Player.h"
#include"Hit_check.h"
#include"3Dmodel.h"
bool p_zmoveflg = false;//�O�i�Ɉړ�����t���O
float g = 9.8f;

void Sph_Gravity() {
       // �d�͍쐬
        sph[0].v0y += g;
        sph[0].y -= sph[0].v0y;

        if (sph[0].y < ground.y  + sph[0].radius) {
            /*sph[i].v0y *= -1 * sph[i].bounce;*/
            sph[0].y = ground.y + sph[0].radius;
            if (abs(int(sph[0].v0y)) < g) { //���x��������x�������Ȃ����狭���I��0�ɂ���
                sph[0].v0y = 0;
            }
        }
}

void P_move() {
    //�X�y�[�X����������O�i
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        p_zmoveflg = true;
    }

    if (p_zmoveflg == true){
           switch (Input_PlayerMoveDir())
           {
           case Left:sph[0].z += sph[0].speed;
               sph[0].x -= sph[0].speed;
               break;
           case Right:sph[0].x += sph[0].speed;
               sph[0].z += sph[0].speed;
               break;
           /*case Down:sph[0].z -= sph[0].speed;
               break;*/
           /*case Up:sph[0].z += sph[0].speed;
               break;*/
           }
    }

   if (p_zmoveflg == true) {
        sph[0].z += sph[0].speed;
        if (sph[0].z > wall.z - sph[0].radius) {
            sph[0].speed = 0;
        }
    }
    


   //������Ă���������e�L�X�g�\��
    switch (Input_PlayerMoveDir())
    {
    case Left:DrawFormatString(100, 300, GetColor(255, 255, 255), "[��]");
        break;
    case Right:DrawFormatString(100, 300, GetColor(255, 255, 255), "[�E]");
        break;
    /*case Down:DrawFormatString(100, 300, GetColor(255, 255, 255), "[��]");
        break;*/
    /*case Up:DrawFormatString(100, 300, GetColor(255, 255, 255), "[��]");
        break;*/
    }
}

//�v���C���[�������Ă��������Ԃ��֐�
int Input_PlayerMoveDir() {

    int input_dir = -1;

    if (CheckHitKey(KEY_INPUT_A))
    {
        input_dir = Left;
    }
    if (CheckHitKey(KEY_INPUT_D))
    {
        input_dir = Right;
    }
    if (CheckHitKey(KEY_INPUT_S))
    {
        input_dir = Down;
    }
    if (CheckHitKey(KEY_INPUT_W))
    {
        input_dir = Up;
    }
    return input_dir;
}