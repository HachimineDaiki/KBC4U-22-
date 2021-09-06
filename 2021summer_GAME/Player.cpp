#include<DxLib.h>
#include<math.h>
#include"Player.h"
#include"Hit_check.h"
#include"3Dmodel.h"
#include"Init.h"
#include"Camera.h"
#include"User_Interface.h"
#include"KeyCheck.h"

//float g = 9.81f; //�n���̏d��

int count=0;

void Sph_Gravity() {
        //�d�͍쐬
       sph[0].v0y += g;
       sph[0].pos.y -= sph[0].v0y;

       if (sph[0].v0y >= 80) {
           g = 0;
       }
}
//����
float P_CollisionVelocity() {
   // float e = 0.5f;
    float e = 1.0f;
    float v_collision = 0.0f;//�Փˌ�̑��x	

    if (fabsf(sph[0].zmove) <= 75) {
        if (g_frontflg == 0) {//�O���ɍ₪�Ȃ�
            v_collision = -40;
        }
        else if (g_frontflg == 1) {//�O���ɍ₪����
            v_collision = 40;
        }
    }
    else if (fabsf(sph[0].zmove) >= 76) {
        if (g_frontflg == 0) {//�O���ɍ₪�Ȃ�
            v_collision = -50;
        }
        else if (g_frontflg == 1) {//�O���ɍ₪����
            v_collision = 50;
        }
    }
    g_CollisionReflectionFlag = 0;
    //v_collision = -e * sph[0].zmove;
    return v_collision;
}
void P_Direction() {
    //VECTOR p_oldpos;//�O��̍��W
    //
    //sph[0].direction = VSub(sph[0].pos, p_oldpos);
    //p_oldpos = sph[0].pos;

    //float len = sqrtf(sph[0].pos.x * sph[0].pos.x + sph[0].pos.y * sph[0].pos.y + sph[0].pos.z * sph[0].pos.z);
    //sph[0].direction.x = sph[0].pos.x / len;
    //sph[0].direction.y = sph[0].pos.y / len;
    //sph[0].direction.z = sph[0].pos.z / len;

    //���_
    //DrawLine3D(sph[0].pos, VAdd(sph[0].pos, VGet(0, 0, sph[0].radius * 2)), GetColor(255, 255, 255));
    ///*float dis = sqrtf(sph[0].pos.x * sph[0].pos.x + sph[0].pos.y * sph[0].pos.y + sph[0].pos.z * sph[0].pos.z);*/
    //DrawFormatString(300, 80, GetColor(255, 255, 255), " �v���C���[���� x %.1f y %.1f z %.1f", sph[0].direction.x, sph[0].direction.y, sph[0].direction.z);
}
void Accl() {
    //���䏈��
    /*float p_vz2 = -5 * tan(5);*/
    //float p_vx = 30 * cos(5);
    //float p_vy = 30 * sin(5);
    //p_vz2 / 30; //�ǂ�ǂ񑬂���ς���
    float p_vz2 = 10;

    if (p_zmoveflg) {
        if (g_frontflg == 0) {//�O�ɍ₪�Ȃ��ƑO�ɉ���
            sph[0].zmove += p_vz2 * sph[0].control;
            if (sph[0].zmove < 0) {//zmove�����̐��̎��̏���
                sph[0].zmove += (p_vz2 * 2) * sph[0].control;
            }
            //if (g_CollisionReflectionFlag == 1 && sph[0].zmove >= -10) {//��Q���Ɠ���������̏���
            //    g_CollisionReflectionFlag = 0;
            //}
        }
        else if (g_frontflg == 1) {//�O�ɍ₪����ƌ��ɉ���
            sph[0].zmove -= p_vz2 * sph[0].control;
            if (sph[0].zmove >= 0) {//zmove�����̐��̎��̏���
                sph[0].zmove -= (p_vz2 * 2) * sph[0].control;
            }
            //if (g_CollisionReflectionFlag == 1 && sph[0].zmove < 10) {//��Q���Ɠ���������̏���
            //    g_CollisionReflectionFlag = 0;
            //}
        }
    }


    if (sph[0].zmove >= 150.0f) {
        sph[0].zmove = 150.0f;
    }
    else if (sph[0].zmove <= -150.0f) {
        sph[0].zmove = -150.0f;
    }

    if (sph[0].zmove >= 50.0f) {
        sph[0].zaccl = 0.0f;
    }

    //if (g_CollisionReflectionFlag == 1) {
    //    if (sph[0].zmove >= 0 && g_frontpos2.HitFlag == FALSE) {
    //        g_CollisionReflectionFlag == 0;
    //    }
    //    if (sph[0].zmove < 0 && g_frontpos2.HitFlag == TRUE) {
    //        g_CollisionReflectionFlag == 0;
    //    }
    //}



 
}
void P_move() {    
    //�s�@�����ړ�
 /*   int speed = 50;
    if (CheckHitKey(KEY_INPUT_A))
    {
        obj.pos.x += speed;
    }
    if (CheckHitKey(KEY_INPUT_D))
    {
        obj.pos.x -= speed;
    }
    if (CheckHitKey(KEY_INPUT_T))
    {
        obj.pos.y += speed;
    }
    if (CheckHitKey(KEY_INPUT_G))
    {
        obj.pos.y -= speed;
    }

    if (CheckHitKey(KEY_INPUT_S))
    {
        obj.pos.z += speed;
    }
    if (CheckHitKey(KEY_INPUT_W))
    {
        obj.pos.z -= speed;
    }

    if (CheckHitKey(KEY_INPUT_1))
    {
        speed += 10;
    }
    if (CheckHitKey(KEY_INPUT_2))
    {
        speed -= 10;
    }

    if (CheckHitKey(KEY_INPUT_F))
    {
       speed /= speed;
    }*/

    if (p_zmoveflg == true) {
        switch (Input_PlayerMoveDir())
        {
        case Left:
            st_model_hit.movepos = st_model_hit.leftvec; st_model_hit.moveflag = 1;
            break;
        case Right:
            st_model_hit.movepos = st_model_hit.rightvec; st_model_hit.moveflag = 1;
            break;
        }
    
    }
   Accl();//accelerator����
   P_rotate();//��]����
   //P_Direction();
}

//�����܂�
//�v���C���[��HP�Ǘ�����
void P_hp(int obssize) {
    //�v���C���[�̓����������̃X�s�[�h�Ə�Q���̎�ނ�HP�����炷�B
    sph[0].hp -= Hit_player_speed(sph, obssize);
    rock[0].handle_num = P_rest_hp_handle(sph[0].hp);
    //HP��0��艺����Ȃ�
    if (sph[0].hp <= 0) {
        //WaitTimer(10000);
        sph[0].hp = 0;
    }
}

int  P_rest_hp_handle(int hp) {
    //HP�̎c��Q�[�W�����ĐF��Ԃ��B
    int handle_num = 0;//�F�̓Y����

    if (300 >= hp && 151 <= hp) { //300�`151
        handle_num = 0;
    }
    else if (150 >= hp && 76 <= hp) { //151�`76
        handle_num = 1;
    }
    else if (75 >= hp && 0 <= hp) { //75�`0
        handle_num = 2;
    }
    else if (0 > hp) { //0�ȉ�
        handle_num = 2;
    }
    return handle_num;
}


//�v���C���[��]
void P_rotate() {
    const int rotate_amount = 15;//��]��
    g_p_rotate_amount = sph[0].zmove / rotate_amount;//��]�ʐ���
    g_p_Rotate += g_p_rotate_amount;//��]�ʂ���]�ɔ��f������B
   /* DrawFormatString(500, 160, GetColor(0, 255, 255), " �v���C���[�̉�]�� %.0f ",g_p_rotate_amount);*/
    if (g_p_Rotate >= 360) {
        g_p_Rotate = 0;
    }
    //��]���Z�b�g
    MV1SetRotationXYZ(rock[rock[0].handle_num].handle, VGet(g_p_Rotate * DX_PI_F / 180.0f, -g_p_direct * DX_PI_F / 180.0f, 0.0f));
}

//�v���C���[���͎�t
void P_input_move() {
    //�X�y�[�X����������O�i

    if (g_KeyFlg & PAD_INPUT_2) {  //B�L�[�ŃX�^�[�g
        p_zmoveflg = true;
    }
    switch (Input_PlayerMoveDir())
    {
    case Left:st_model_hit.movepos = st_model_hit.leftvec; st_model_hit.moveflag = 1; 
        break;
    case Right:st_model_hit.movepos = st_model_hit.rightvec; st_model_hit.moveflag = 1;
        break;
    }
}
//�v���C���[�������Ă��������Ԃ��֐�
int Input_PlayerMoveDir() {

    int input_dir = -1;

    if (htdrow.hitflg == false) {
        if (g_KeyFlg & PAD_INPUT_8) {  //�X�^�[�g�{�^���Ń��X�^�[�g
            All_Init();

        }
    }

    if (g_goalflag == 0) {
        if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) != 0)
        {
            input_dir = Left;
        }
        if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) != 0)
        {
            input_dir = Right;
        }
    }

    if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) != 0)
    {
        input_dir = Down;
    }
    if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) != 0)
    {
        input_dir = Up;
    }
    return input_dir;
}

//void P_debug() {
//    if (CheckHitKey(KEY_INPUT_A))
//    {
//        sph[0].pos.x -= 10;
//    }
//
//    if (CheckHitKey(KEY_INPUT_D))
//    {
//        sph[0].pos.x += 10;
//    }
//
//    if (CheckHitKey(KEY_INPUT_W))
//    {
//        sph[0].pos.z += 10;
//    }
//
//    if (CheckHitKey(KEY_INPUT_S))
//    {
//        sph[0].pos.z -= 10;
//    }
//}