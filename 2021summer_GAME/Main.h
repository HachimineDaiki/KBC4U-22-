#pragma once
#include <Dxlib.h>
#include "Init.h"
#include "Hit_check.h"
#include "Player.h"
#include "Camera.h"
#include "3Dmodel.h"
#include "Param_Info.h"
#include "Title.h"
#include "Gameover.h"

enum GAMEMODE { TITLE, GAME, GAMEOVER};//�Q�[�����[�h
//�\����
Sph sph[2];//�v���C���[
Sph obj;//�s�@����
Sph damege_aria[DAMEGE_ARIA_MAX];//��Q��
Sph decele_aria[DECELE_ARIA_MAX];//�����G���A
Model ground;//�n��
Model rock[3];//��
StageModelHit st_model_hit;//���f���q�b�g
HitDrow htdrow;//�q�b�g�`��
VECTOR TempMoveVector;
VECTOR g_frontVector;//�v���C���[�̑O�������
VECTOR g_cameraPosition;//�J�����̍��W
Decel decel;//����
Title title;//�^�C�g��
Gameover gameover;//�Q�[���I�[�o�[
Branch branch;
Damege obs_damege;//��Q���̃_���[�W��

//�񋓑�

float g=9.81;//�d�͂���

void Gamemain();//�Q�[�����C���֐�
float s_dis;
float es_dis;
bool p_zmoveflg;

float g_sinParam;
float g_cosParam;
float g_cameraHAngle;
float g_cameraVAngle;

float g_p_direct; // �v���C���[�̌���
float g_p_Rotate; // �v���C���[�̉�]
float g_p_rotate_amount;//��]��

float merikomi;//�߂荞�ޗ�

int g_fronthit;//0�@�O�ɍ�i�V�@1�@�O�ɍ�A��

int gameMode;//�Q�[�����[�h
