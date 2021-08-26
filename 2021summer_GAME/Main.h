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
#include "Time.h"
#include "DebugMode.h"
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
VECTOR g_Ill_dump1;//�s�@�������̏����l������
Decel decel;//����
Title title;//�^�C�g��
Gameover gameover;//�Q�[���I�[�o�[
Branch branch;
Damege obs_damege;//��Q���̃_���[�W��
Model wall[WALL_MAX];
HITRESULT_LINE g_frontpos2;
Model gensoku[DECELE_ARIA_MAX];
Model e_rock[DAMEGE_ARIA_MAX];

DrawStr speed_draw_str; //�����`��
Title_Slect title_slect[2];
Title_Slect title_slectfream[2];
Time_  effect_time;
FileData f_damege_aria;//�_���[�W�G���A�t�@�C�����
DebugObj d_obj[MAXOBJ]; //�f�o�b�O�I�u�W�F�N�g
bool gameexit;
bool goal_input_space;
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

int g_frontflg;//0�@�O�ɐi��ł���@1�@���ɐi��ł���
int g_CollisionReflectionFlag;//0 �Փ˂��Ĕ��˂��Ă��Ȃ� 1 �Փ˂��Ĕ��˂��Ă���
int g_goalflag;//�S�[���������ǂ����@0�S�[�����ĂȂ��@1�S�[������
float g_GoalFullScore;//�S�[���̍ő哾�_�̊i�[
float g_dist;//�S�[���̍ő哾�_�̌v�Z�Ɏg�����x�i�[

int CheckKey;
int gameMode;//�Q�[�����[�h

