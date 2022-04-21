#include <DxLib.h>
#include <time.h>
#include "class/Select.h"
#include "class/Cash.h"
#include "class/EleMoney.h"
#include "resource.h"

constexpr int SCREEN_SIZE_X = 640;		//画面のサイズ：横
constexpr int SCREEN_SIZE_Y = 480;		//画面のサイズ：縦

Ticket* SceneChange(SCENE_ID nextScene) //シーン切り替え
{
	Ticket* ticket = nullptr;
	switch (nextScene)
	{
	case SCENE_ID::SELECT:
		ticket = new Select();
		break;
	case SCENE_ID::CASH:
		ticket = new Cash();
		break;
	case SCENE_ID::ELEMONEY:
		ticket = new EleMoney();
		break;
	default:
		//なし
		break;
	}
	return ticket;
};

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(true);
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	SetMainWindowText("切符販売");
	SetWindowIconID(IDI_ICON1);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//生成処理
	Ticket* ticket_;
	SCENE_ID beforeScene_, afterScene_;

	//金の金種と枚数: 10 円玉 15 枚、50 円玉 3 枚、100 円玉 2 枚、500 円玉 1 枚、1000 円札 1 枚、
	//5000 円札 1 枚、10000 円札 1枚
	//現金の場合は130円電子マネーの場合は124円となる

	//初期化処理
	ticket_ = new Select();
	beforeScene_ = afterScene_ = ticket_->GetScene();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//更新処理
		ticket_->UpDate();
		afterScene_ = ticket_->GetScene();

		if (afterScene_ != beforeScene_) //シーンの切り替え
		{
			delete ticket_;
			ticket_ = nullptr;
			ticket_ = SceneChange(afterScene_);
		}

		beforeScene_ = afterScene_;

		//描画処理
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		ticket_->Draw();
		ticket_->DrawBack();

		ScreenFlip();
	}

	//解放処理
	delete ticket_;
	ticket_ = nullptr;

	DxLib_End();
	return 0;
}