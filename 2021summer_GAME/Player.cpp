#include<DxLib.h>
#include<math.h>
#include"Player.h"
#include"Hit_check.h"
#include"3Dmodel.h"
float g = 9.81f; //�n���̏d��

void Sph_Gravity() {
        //�d�͍쐬
       sph[0].v0y += g;
       sph[0].pos.y -= sph[0].v0y;

       if (sph[0].v0y >= 80) {
           g = 0;
       }
}
void Accl() {
    //���䏈��
    float p_vz2 = -5 * tan(5);
    //float p_vx = 30 * cos(5);
    //float p_vy = 30 * sin(5);
    //p_vz2 / 30; //�ǂ�ǂ񑬂���ς���

    if (p_zmoveflg) {
        sph[0].zmove += p_vz2 * sph[0].control;
    }

    //�X�s�[�h����
    if (sph[0].zmove >= 150.0f) {
        sph[0].zmove = 150.0f;
    }
    MV1SetRotationXYZ(rock.handle, VGet(sph[0].pos.z, 0.0f, 0.0f));
}
void P_move() {    
   Accl();//accelerator���� //7/29���@���x���~�߂�
   //������Ă���������e�L�X�g�\��
    //switch (Input_PlayerMoveDir())
    //{
    //case Left:DrawFormatString(100, 300, GetColor(255, 255, 255), "[��]");
    //    break;
    //case Right:DrawFormatString(100, 300, GetColor(255, 255, 255), "[�E]");
    //    break;
    //case Up:DrawFormatString(100, 300, GetColor(255, 255, 255), "[��]");
    //    break;
    //}
}
void P_input_move() {
    //�X�y�[�X����������O�i
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        p_zmoveflg = true;
    }

    switch (Input_PlayerMoveDir())
    {
    case Left:st_model_hit.movepos = st_model_hit.leftvec; st_model_hit.MoveFlag = 1; st_model_hit.gplayer_limits -= sph[0].speed;
        break;
    case Right:st_model_hit.movepos = st_model_hit.rightvec; st_model_hit.MoveFlag = 1; st_model_hit.gplayer_limits += sph[0].speed;
        break;
    }

 /*      switch (Input_PlayerMoveDir())
    {
       case Left:sph[0].pos.x -= 50;
        break;
       case Right:sph[0].pos.x += 50;
        break;
       case Up:sph[0].pos.z += 50;
        break;
       case Down:sph[0].pos.z -= 50;
        break;
    }*/

    //���菈��
    Move_Limits();

}
//�v���C���[�������Ă��������Ԃ��֐�
int Input_PlayerMoveDir() {

    int input_dir = -1;

    if (CheckHitKey(KEY_INPUT_A)&& st_model_hit.glimits_verification[0] < st_model_hit.gplayer_limits)
    {
        input_dir = Left;
    }
    if (CheckHitKey(KEY_INPUT_D) && st_model_hit.glimits_verification[1] > st_model_hit.gplayer_limits)
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
