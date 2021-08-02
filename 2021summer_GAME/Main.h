#pragma once
#include <Dxlib.h>
#include "Init.h"
#include "Hit_check.h"
#include "Player.h"
#include "Camera.h"
#include "3Dmodel.h"
#include "Param_Info.h"
#include "Title.h"

enum GAMEMODE { TITLE, GAME, GAMEOVER};//ゲームモード

MV1_COLL_RESULT_POLY_DIM HitPolyDim[TREE_NUM];
Sph sph[2];
Sph obj;
Sph decelearia[DECELEARIA_NUM];
Model ground;
Model rock;
StageModelHit st_model_hit;
HitDrow htdrow;
VECTOR TempMoveVector;
Decel decel;
Title title;
Branch branch;

void Gamemain();
//int tree_handle[TREE_NUM];
float s_dis;
bool p_zmoveflg;

float g_sinParam;
float g_cosParam;
float g_cameraHAngle;
float g_cameraVAngle;

float g_p_direct; // プレイヤーの向き
float g_p_Rotate; // プレイヤーの回転

float merikomi;

int gameMode;
