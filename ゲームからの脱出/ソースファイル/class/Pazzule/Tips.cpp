#include <DxLib.h>
#include "Tips.h"
#include "../KeyCheck.h"

bool Tips::Init(void)
{
	slideTips = LoadGraph("image/passTips_left.png");
	lightTips = LoadGraph("image/passTips_right.png");
	matchTips = LoadGraph("image/passTips.png");

	slideFlag = false;
	lightFlag = false;
	matchFlag = false;

	count = 0;
	font = CreateFontToHandle(NULL, 32, -1, -1);
	return true;
}

bool Tips::Update(void)
{
	count++;
	return true;
}

void Tips::SlideDraw(void)
{

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (keyTrgUp[KEY_P1_X])
	{
		slideFlag = true;
	}
	if (slideFlag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	}
	DrawBox(0, 0, 640, 480, 0x222222, true);
	DrawGraph(150, 100, slideTips, true);
	DrawStringToHandle(150, 350, "切れ端１を入手した", 0xffffff,font);
	if (count / 30 % 2)
	{
		DrawStringToHandle(200, 400, "Xキーで戻る", 0xffffff,font);
	}
}

void Tips::LightDraw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

	if (keyTrgUp[KEY_P1_X])
	{
		lightFlag = true;
	}
	if (lightFlag)
	{
		SetDrawBlendMode(DX_BLENDMODE_SUB, 0);
	}
	DrawBox(0, 0, 640, 480, 0x222222, true);
	DrawGraph(150, 100, lightTips, true);
	DrawStringToHandle(150, 350, "切れ端２を入手した", 0xffffff, font);
	if (count / 30 % 2)
	{
		DrawStringToHandle(200, 400, "Xキーで戻る", 0xffffff, font);
	}

}

void Tips::MatchDraw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	if (keyTrgDown[KEY_P1_X])
	{
		matchFlag = true;
	}
	if (matchFlag)
	{
		SetDrawBlendMode(DX_BLENDMODE_SUB, 0);
	}
	DrawBox(0, 0, 640, 480, 0x222222, true);
	DrawGraph(150, 100, matchTips, true);
	DrawStringToHandle(100, 350, "金庫のパスワードを入手した", 0xffffff, font);
	if (count / 30 % 2)
	{
		DrawStringToHandle(200, 400, "Xキーで戻る", 0xffffff, font);
	}
	if (CheckHitKey(KEY_INPUT_F))
	{
		matchFlag = false;
	}

}

bool Tips::Release(void)
{
	return true;
}

bool Tips::MatchFlag(void)
{
	if (slideFlag == true && lightFlag == true)
	{
		return true;
	}
	return false;
}

void Tips::InventoryDraw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (matchFlag)
	{
		DrawString(470, 480 - 16, "Fキーで持ち物を見る", 0xffffff, true);
	}
}

bool Tips::ReturnFlag(void)
{
	return matchFlag;
}
