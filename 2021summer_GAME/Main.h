#pragma once
#include <Dxlib.h>
#include "Init.h"
#include "Hit_check.h"
#include "Player.h"
#include "Camera.h"
#include "3Dmodel.h"
#include "Param_Info.h"
#include "Title.h"

enum GAMEMODE { TITLE, GAME, GAMEOVER};//�Q�[�����[�h
//�\����
Sph sph[2];//�v���C���[
Sph obj;//�s�@����
Sph damege_aria[DAMEGE_ARIA_MAX];//��Q��
Sph decele_aria[DECELE_ARIA_MAX];//�����G���A
Model ground;//�n��
Model rock;//��
StageModelHit st_model_hit;//���f���q�b�g
HitDrow htdrow;//�q�b�g�`��
VECTOR TempMoveVector;
Decel decel;//����
Title title;//�^�C�g��
Branch branch;
Damege obs_damege;//��Q���̃_���[�W��
//�񋓑�

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

int gameMode;//�Q�[�����[�h
