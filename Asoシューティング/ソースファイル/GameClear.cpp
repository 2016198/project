#include "GameClear.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool GameClear::Init(void)//初期化処理
{
	if ((se = LoadSoundMem("se/Win.wav")) == -1)
	{
		TRACE("読み込み失敗");
		return -1;
	}
	if ((image = LoadGraph("image/gameclear.png")) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	if ((LoadDivGraph("image/tete.png", 2, 2, 1, 16, 16, &te[0])) == -1)
	{
		TRACE("読み込み失敗");
		return false;
	}
	for (int e = 0; e < 4; e++)
	{
		x = 50;
		y = 400;
	}
	counter = 0;
	return true;
}

void GameClear::UpDate(void)//更新処理
{
	counter++;
}

void GameClear::Draw(int score)//描画処理
{
	if (counter == 1)
	{
		PlaySoundMem(se, DX_PLAYTYPE_BACK);
	}
	DrawGraph((SCREEN_SIZE_X - TITLE_CLEAR_SIZE_X) / 2, (SCREEN_SIZE_Y - TITLE_CLEAR_SIZE_Y) / 2, image, true);
	if ((counter / 50) % 2 == 0)
	{
		SetFontSize(30);
		DrawString(150, 0, "やめる   Escキー", GetColor(0, 255, 255));
		DrawString(150, 0, "\n続ける   Enterキー", GetColor(25, 255, 0));
	}
	for (int d = 0; d < 7; d++)
	{
		DrawGraph(x + (TETE_SIZE_X * 6 * d), y, te[(counter / 5) % 2], true);
	}
	DrawFormatString(150, 320, GetColor(200, 0, 200), "スコア    %d", score);
}

bool GameClear::Release(void)//解放処理
{
	DeleteSoundMem(se);
	for (int t = 0; t < 2; t++)
	{
		DeleteGraph(te[t]);
	}
	DeleteGraph(image);
	return true;
}

void GameClear::Reset()
{
	counter = 0;
}