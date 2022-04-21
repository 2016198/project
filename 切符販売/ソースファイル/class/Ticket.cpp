#include <DxLib.h>
#include "Ticket.h"

Ticket::Ticket()//コンストラクタ
{
	GetMousePoint(&x_, &y_);
	mouse_[0] = false;
	mouse_[1] = false;
	scene_ = SCENE_ID::MAX;
	width_ = 0;
	IsBuy_ = false;
	ticketPrice_ = 0;
	ticketNum_ = 0;
	colorB_ = WHITE;
}

Ticket::~Ticket()//デストラクタ
{
}

SCENE_ID Ticket::GetScene(void)	//現在のシーンを入手
{
	return scene_;
}

bool Ticket::MouseOneInput(void)//マウスの入力
{
	return mouse_[0] && !mouse_[1];
}

bool Ticket::HitBack(void)//1つ戻るボタン
{
	return x_ > 10 && y_ > 436 && x_ < 130 && y_ < 470;
}

void Ticket::DrawBack(void)//戻るボタン描画
{
	DrawExtendString(10, 438, 2.0, 2.0, "1つ戻る", colorB_.GetColorCode());
	DrawBox(8, 436, 130, 470, colorB_.GetColorCode(), false);
}
