#include "LifeP.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "main.h"

bool LifeP::Init(void)
{
	if ((image = LoadGraph("image/Heart.png")) == -1)
	{
		TRACE("ì«Ç›çûÇ›é∏îs");
		return false;
	}
	posx = SCREEN_SIZE_X - HEART_SIZE_X;
	posy = 0;
	return true;
}

void LifeP::Update(void)
{

}

void LifeP::Draw(int lifeP)
{
	SetFontSize(20);
	DrawString(posx - 50, posy, "écã@", GetColor(255, 255, 255));
	for (int h = 0; h < lifeP; h++)
	{
		DrawGraph(posx, posy + (HEART_SIZE_Y * h) + (h * 10), image, true);
	}
}

bool LifeP::Release(void)
{
	DeleteGraph(image);
	return true;
}

bool LifeP::GameInit(void)
{
	posx = SCREEN_SIZE_X - HEART_SIZE_X;
	posy = HEART_SIZE_Y;
	return true;
}