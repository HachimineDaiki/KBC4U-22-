#pragma once




void UIinit();//UIの初期化

void UIdraw();//UIの表示

void Distance_Calculation();//距離の計算

void Judgement();//成功大成功の判定

extern VECTOR g_Ill_dump1;//不法投棄物の初期値を入れる
extern int g_goalflag;//ゴールしたかどうか　0ゴールしてない　1ゴールした
extern float g_GoalFullScore;//ゴールの最大得点の格納
extern float g_dist;//ゴールの最大得点の計算に使う速度格納
