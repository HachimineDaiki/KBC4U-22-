#pragma once
#include<DxLib.h>
#include"User_Interface.h"
#include "Player.h"
#include "Param_Info.h"
extern bool goal_input_space;
void PlanetMove();

void MonthMove();//��
void VenusMove();//����
void MercuryMove();//����
void SunMove();//���z
void InitGoalStr();

int CheckPlanet(float speed, int hp);
void DrawPlanet();
extern bool haikeiflg;

struct GoolObj
{
	float speed;
};

extern GoolObj goal_obj;
//
//int MapLoad();
//void InitMap();
//void MoveMap();
////2D
//struct Map {
//	float x;
//	float y;
//	int width;
//	int height;
//	float speed;
//};
//
//extern Map goal_scene;