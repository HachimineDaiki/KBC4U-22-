#include<DxLib.h>
#include<math.h>
#include"Player.h"
#include"Hit_check.h"
#include"3Dmodel.h"
bool p_zmoveflg = false;//�O�i�Ɉړ�����t���O
float g = 9.81f; //�n���̏d��


void Sph_Gravity() {
        //�d�͍쐬
       /*sph[0].v0y += g;*/
       /*sph[0].pos.y -= sph[0].v0y;*/

       sph[0].pos.y -= g;
        //if (sph[0].pos.y < ground.y  + sph[0].radius) {
        //    /*sph[i].v0y *= -1 * sph[i].bounce;*/
        //    sph[0].pos.y = ground.y + sph[0].radius;
        //    if (abs(int(sph[0].v0y)) < g) { //���x��������x�������Ȃ����狭���I��0�ɂ���
        //        sph[0].v0y = 0;
        //    }
        //}
}

void P_move() {
    accl();
    
    //if (p_zmoveflg == true) {
    //    switch (Input_PlayerMoveDir())
    //    {
    //    case Left:/*sph[0].z += sph[0].speed;*/
    //        /*sph[0].x -= sph[0].speed;*/ st_model_hit.movepos = st_model_hit.leftvec; st_model_hit.MoveFlag = 1;
    //        break;
    //    case Right:/*sph[0].x += sph[0].speed;*/
    //        /* sph[0].z += sph[0].speed;*/ st_model_hit.movepos = st_model_hit.rightvec; st_model_hit.MoveFlag = 1;
    //        break;
    //    }

    //}

   if (p_zmoveflg == true) {
        sph[0].pos.z += 10;
        if (sph[0].pos.z > wall.z - sph[0].radius) {
            sph[0].speed = 0;
        }
    }

    /*if (p_zmoveflg == true) {
        st_model_hit.movepos = VGet(0.0f, 0.0f, 10.0f);
        if (sph[0].z > wall.z - sph[0].radius) {
            sph[0].speed = 0;
        }
    }*/
    
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
    /*
    //�X�y�[�X����������O�i
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        p_zmoveflg = true;
    }*/
    
    accl();

    switch (Input_PlayerMoveDir())
    {
    case Left:st_model_hit.movepos = st_model_hit.leftvec; st_model_hit.MoveFlag = 1;
        break;
    case Right:st_model_hit.movepos = st_model_hit.rightvec; st_model_hit.MoveFlag = 1;
        break;
    case Up:st_model_hit.movepos = st_model_hit.upvec; st_model_hit.MoveFlag = 1;
        break;
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
void accl() {

}