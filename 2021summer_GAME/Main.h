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
#include <math.h>
#include "Effect.h"
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
VECTOR g_rightVector;
VECTOR g_leftVector;
VECTOR g_cameraPosition;//�J�����̍��W
VECTOR g_Ill_dump1;//�s�@�������̏����l������
Decel decel;//����
Title title;//�^�C�g��
Gameover gameover;//�Q�[���I�[�o�[
Damege obs_damege;//��Q���̃_���[�W��
Model wall[WALL_MAX];
HITRESULT_LINE g_frontpos2;
Model gensoku[DECELE_ARIA_MAX];//�����G���A(�ʂ����)���f��
Model e_rock[DAMEGE_ARIA_MAX]; //��Q��(��)���f��

DrawStr speed_draw_str; //�����`��
Title_Slect title_slect[2];
Title_Slect title_slectfream[2];
Time_  effect_time;
FileData f_damege_aria;//�_���[�W�G���A�t�@�C�����
//DebugObj d_obj[MAXOBJ]; //�f�o�b�O�I�u�W�F�N�g
Camera camera;//�J����
VECTOR obj_cameraPosition;//�I�u�W�F�N�g�J����
bool obj_switchflg;
Sph planet[5];
Time_ effect_exit_time;
GoolObj goal_obj;

Effect e_move;
Effect e_orbit;
Effect e_bom;

bool gameexit;//�Q�[���I���t���O
bool goal_input_space;//�S�[���������ɃX�y�[�X�������邩�t���O
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
int g_rightflg;//0�@�E�΂ߑO�ɍ�i�V�@1�@�E�΂ߑO�ɍ�A��
int g_leftflg;//0�@���΂ߑO�ɍ�i�V�@1�@���΂ߑO�ɍ�A��
int g_CollisionReflectionFlag;//0 �Փ˂��Ĕ��˂��Ă��Ȃ� 1 �Փ˂��Ĕ��˂��Ă���
int g_goalflag;//�S�[���������ǂ����@0�S�[�����ĂȂ��@1�S�[������
float g_GoalFullScore;//�S�[���̍ő哾�_�̊i�[
float g_dist;//�S�[���̍ő哾�_�̌v�Z�Ɏg�����x�i�[
float distance;
int g_WallHitFlag;

int CheckKey;


int g_OldKey;
int g_NowKey;
int g_KeyFlg;

int gameMode;//�Q�[�����[�h

bool haikeiflg;

float  CameraVAngle;
float  CameraHAngle;

bool obj_move;//�I�u�W�F�N�g����
float earth_pos_z;




