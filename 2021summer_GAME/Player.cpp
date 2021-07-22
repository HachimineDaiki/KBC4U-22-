#include<DxLib.h>
#include<math.h>
#include"Player.h"
#include"Hit_check.h"
#include"3Dmodel.h"
bool p_zmoveflg = false;//�O�i�Ɉړ�����t���O
float g = 9.81f; //�n���̏d��
float gplayer_limits = 450;      //X�͈̔�
int glimits_verification[2] = { 0,900 }; //�[�̐��l�@0: ���̒[ 900 : �E�̒[
bool gmoveflg = false;    //false:�����͈͓��@true:�����͈͊O

//�v���C���[�d�͏���
void Sph_Gravity() {
        //�d�͍쐬
       sph[0].v0y += g;
       sph[0].pos.y -= sph[0].v0y;
       //�d�̗͂ʂ�10�ȏゾ������d�͂������B
       if (sph[0].v0y >= 10) {
           g = 0;
       }
}

//�v���C���[�ړ�����
void P_move() {    
    //���䏈��
    float p_vz2 = -20 * tan(5);
    //float p_vx = 30 * cos(5);
    //float p_vy = 30 * sin(5);
    //p_vz2 / 30; //�ǂ�ǂ񑬂���ς���

    //Z�����ɉ������鏈��
    sph[0].zmove += sph[0].zaccl;
    if (sph[0].zmove >= 50.0f) {
        sph[0].zaccl = 0.0f;
    }

    //�O�i������t���O���I���Ȃ�O�i������
   if (p_zmoveflg) {
       sph[0].pos.z += sph[0].zmove;
   }
    
   //������Ă���������e�L�X�g�\��
    switch (Input_PlayerMoveDir())
    {
    case Left:DrawFormatString(100, 300, GetColor(255, 255, 255), "[��]");
        break;
    case Right:DrawFormatString(100, 300, GetColor(255, 255, 255), "[�E]");
        break;
    case Up:DrawFormatString(100, 300, GetColor(255, 255, 255), "[��]");
        break;
    }
}
void P_input_move() {
    //�X�y�[�X����������O�i
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        p_zmoveflg = true;
    }

    switch (Input_PlayerMoveDir())
    {
    case Left:st_model_hit.movepos = st_model_hit.leftvec; st_model_hit.MoveFlag = 1; gplayer_limits -= sph[0].speed;
        break;
    case Right:st_model_hit.movepos = st_model_hit.rightvec; st_model_hit.MoveFlag = 1; gplayer_limits += sph[0].speed;
    }

    //���菈��
    Move_Limits();

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

//�v���C���[�̍��E�ړ��͈͂𐧌�����
void Move_Limits()
{
    int lhit_magnification = 5;    //X�̈ړ��͈͊O�ɂł��ꍇ�̖߂��͂̔{��

    //���E�̂ǂ��炩�͈̔͊O�Ɉړ����悤�Ƃ�����t���O��true�ɂ���
    if (gplayer_limits <= glimits_verification[0] || gplayer_limits >= glimits_verification[1]) {
        gmoveflg = true;
    }

    if (gmoveflg == true) {
        //�͈͓��ɖ߂�����(��)
        if (gplayer_limits < sph[0].speed * lhit_magnification) {
            sph[0].pos.x += 10;
            gplayer_limits += 10;
        }
        //�͈͓��ɖ߂�����(�E)
        else if (gplayer_limits > glimits_verification[1] - sph[0].speed * lhit_magnification) {
            sph[0].pos.x -= 10;
            gplayer_limits -= 10;
        }
        //�t���O�����Ƃɖ߂�
        else {
            sph[0].speed = 10.0f;
            gmoveflg = false;
        }
    }
}