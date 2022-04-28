#include <DxLib.h>			
#include "KeyCheck.h"
#include "GameClearScene.h"

bool GameClearScene::Init(void)
{
	image_ = LoadGraph("image/脱出成功.png");
	font_ = CreateFontToHandle("HGSｺﾞｼｯｸE", 30, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 4);
	count_ = 0;
	flag_ = false;

	return true;

}
bool GameClearScene::Update(void)
{
	CheckKeyList();
	if (keyTrgUp[KEY_SYS_ENTER] && flag_ == true)
	{
		count_ = 0;
		return false;
	}
	count_++;
	return true;

}
void GameClearScene::Draw(void)
{
	DrawGraph(0, 0, image_, true);

	if (count_ / 30 % 2)
	{
		DrawStringToHandle(320 - 130, 210, "ゲームクリア！", 0xffffff, font_);
	}

	if (count_ / 30 > 6)
	{
		DrawString(230, 300, "Back to Title [Enter]",0xffffff);
		flag_ = true;
	}
}
bool GameClearScene::Release(void)
{
	DeleteGraph(image_);
	return true;
}

