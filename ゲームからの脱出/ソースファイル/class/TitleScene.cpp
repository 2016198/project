#include <DxLib.h>			
#include "KeyCheck.h"
#include "TitleScene.h"

bool TitleScene::Init(void)
{
	image_ = LoadGraph("image/title.png");
	font_ = CreateFontToHandle("HGS∫ﬁºØ∏E", 60, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 4);
	count_ = 0;
	KeyInit();

	return true;

}
bool TitleScene::Update(void)
{
	CheckKeyList();

	if (keyTrgUp[KEY_SYS_ENTER])
	{
		return false;
	}

	count_++;

	return true;
}
void TitleScene::Draw(void)
{
	DrawGraph(0, 0, image_, true);
	DrawStringToHandle(50, 100, "ÉQÅ[ÉÄÇ©ÇÁÇÃíEèo", 0xffffff,font_);

	if (count_ / 30 % 2)
	{
		DrawString(250, 400, "Press To Enter", 0xffffff);
		DrawString(250+8, 416, "[Game Start]", 0xff0000);
	}
}
bool TitleScene::Release(void)
{
	DeleteGraph(image_);
	return true;
}
