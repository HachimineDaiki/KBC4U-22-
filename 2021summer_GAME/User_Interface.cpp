#include <DxLib.h>
#include "User_Interface.h"
#include "player.h"

VECTOR Ill_dump2;//移動している不法投棄物の位置を入れる

int judgement = 0;//1成功　2大成功　のフラグ

//UIに使用する情報の初期化
void UIinit() {
	g_Ill_dump1 = obj.pos;
	Ill_dump2 = VGet(0.0f, 0.0f, 0.0f);
	g_goalflag = 0;//ゴールしたかどうか　0ゴールしてない　1ゴールした
	g_dist = 150 * (300 * 3.33);//ゴールの最大得点の格納
	g_GoalFullScore = 0;
}

void Judgement() {
	if ((0.8 * g_GoalFullScore) <= distance) {//最大の80%以上 80% => 0.8
		judgement = 1;
	}
	else if ((0.6 * g_GoalFullScore) <= distance) {//最大の60%以上 60% => 0.6
		judgement = 2;
	}
	else if ((0.5 * g_GoalFullScore) <= distance) {//最大の50%以上 50% => 0.5
		judgement = 3;
	}
	else{//最大の50%よりも小さいとき
		judgement = 4;
	}
}

//不法投棄物の飛んだ距離を計算
void Distance_Calculation() {
	float x, y, z;

	Ill_dump2 = obj.pos;

	x = Ill_dump2.x - g_Ill_dump1.x;
	y = Ill_dump2.y - g_Ill_dump1.y;
	z = Ill_dump2.z - g_Ill_dump1.z;
	distance = VSize(VGet(x, y, z));
	 
}


//UIの表示
void UIdraw() {
	
	//SetFontSize(100);//文字サイズを変更
//	DrawFormatString(341, 334, GetColor(255, 255, 0), " GOAL "); 
	//if (g_dist >= 1) {
	//	//DrawFormatString(341, 140, GetColor(0, 255, 255), " GOAL ");
	//	DrawFormatString(291, 140, GetColor(0, 255, 255), " ゴール ");
	//}
	//if (g_dist < 1) {
	//	if (judgement == 1) {
	//		SetFontSize(50);
	//		DrawFormatString(300, 170, GetColor(255, 255, 0), " 太陽まで飛んだよ！ ");
	//		SetFontSize(10);
	//	}
	//	else if (judgement == 2) {
	//		SetFontSize(50);
	//		DrawFormatString(300, 170, GetColor(255, 255, 0), " 水星まで飛んだよ！ ");
	//		SetFontSize(10);
	//	}
	//	else if (judgement == 3) {
	//		SetFontSize(50);
	//		DrawFormatString(300, 170, GetColor(255, 255, 0), " 金星まで飛んだよ！ ");
	//		SetFontSize(10);
	//	}
	//	else if (judgement == 4) {
	//		SetFontSize(50);
	//		DrawFormatString(300, 170, GetColor(255, 255, 0), " 月まで飛んだよ！ ");
	//		SetFontSize(10);

	//	}
	//}
	//DrawFormatString(341, 20, GetColor(0, 255, 255), " GOAL ");
	//SetFontSize(50);
	//DrawFormatString(341, 120, GetColor(0, 0, 0), "%.0f", distance);//真ん中
	//DrawFormatString(341, 241, GetColor(255, 255, 255), "   飛距離 ", distance);//真ん中 下の数字が何の意味を示すか
	//DrawFormatString(341, 290, GetColor(255, 255, 255), "  %8.0fkm", distance);//真ん中 飛距離

	//DrawFormatString(0, 0, GetColor(0, 0, 0), "%.0f", distance);//左上
	//DrawFormatString(341, 0, GetColor(0, 0, 0), "%.0f", distance);//上
	//DrawFormatString(682, 0, GetColor(0, 0, 0), "%.0f", distance);//右上
	//DrawFormatString(0, 256, GetColor(0, 0, 0), "%.0f", distance);//左
	//DrawFormatString(682, 434, GetColor(0, 0, 0), "%.0f", distance);//右
	//DrawFormatString(0, 512, GetColor(0, 0, 0), "%.0f", distance);//左下
	//DrawFormatString(341, 512, GetColor(0, 0, 0), "%.0f", distance);//下
	//DrawFormatString(682, 512, GetColor(0, 0, 0), "%.0f", distance);//右下

	//DrawFormatString(341, 484, GetColor(0, 0, 0), "%.5f", obj.zmove);//不法投棄物のzmoveの表示確認用
	//DrawFormatString(341, 584, GetColor(0, 0, 0), "%.5f", g_dist);//g_distの表示確認用
	SetFontSize(20);//文字サイズを変更
}