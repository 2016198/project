#include <DxLib.h>
#include "../game/item/ItemBoxPool.h"
#include "../game/text/TextPool.h"
#include "../manager/MaterialManager.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene(INPUT_TYPE type):
	BaseScene(type)
{
	Init();
}

TutorialScene::~TutorialScene()
{

}

bool TutorialScene::Init(void)
{
	tipsTime_ = TIP_TIME;
	progressNum_ = 0;
	delta_[0] = delta_[1] = 0.0;
	bright_ = 125;
	textPtr_ = std::make_unique<Text>();
	screen_ = lpMaterialMng.LoadScreenic("tutorial", SCREEN_SIZE_X, SCREEN_SIZE_Y);
	fadeOut_ = fadeIn_ = false;
	player_[0] = player_[1] = false;
	alpha_ = 0;

	lpItemBoxPool.Init();
	image_ = lpMaterialMng.LoadGraphHandle("image/back/GameScene.jpg");
	if (image_ == -1)
	{
		return false;
	}
	screenP_ = lpMaterialMng.LoadScreenic("player", SCREEN_SIZE_X, SCREEN_SIZE_Y);
	screenM_ = lpMaterialMng.LoadScreenic("manual", SCREEN_SIZE_X, SCREEN_SIZE_Y);
	color_.clear();
	selectNum_ = SCENE_ID::RESULT;	//ゲーム終了したらリザルトシーンへ
	rock[0] = rock[1] = false;

	//アイテムボックスを設置
	
	lpItemBoxPool.Generate(
		5, static_cast<ITEM>(rand() % static_cast<int>(ITEM::NONE)),
		GREEN.GetColorCode());

	//各インスタンス生成
	mapPtr_ = std::make_unique<Map>();

	playerPtr_.emplace_back(std::make_unique<Player>(
		"image/player/player1.png",
		"image/player/shadow1.png"));

	itemPtr_.emplace_back(std::make_unique<Item>());

	int point = rand() % POINT_SIZE;

	//各初期化処理
	if (!mapPtr_->Init(point))
	{
		return false;
	}

	if (!playerPtr_[0]->Init(30, point, MAGENTA))
	{
		return false;
	}

	if (!itemPtr_[0]->Init())
	{
		return false;
	}

	return true;
}

SCENE_ID TutorialScene::Update(double delta)
{
	delta_[0] = delta;
	delta_[1] += delta_[0] / 100.0;

	//入力情報の取得
	for (int t = 0; t < 2; t++)
	{
		ptr_[t]->SetKeyList(inputType_);
		input_[t] = ptr_[t]->GetCntData();
	}

	//テキストモードのチェック
	if (fadeIn_ == false && fadeOut_ == false)
	{
		ChackTextMode(textPtr_->Update(input_[0], input_[1], CheckProgress(progressNum_)));
	}

	//チュートリアルを切り替えます。
	if (fadeIn_ == true || fadeOut_ == true)
	{
		FadeCommand();
	}

	//ゲームの処理
	if (bright_ == 255)
	{
		player_[0] = playerPtr_[0]->Update(input_[0], delta);

		if (player_[0] == true)
		{
			if (playerPtr_[0]->CheckHap())	//間違えたところをかこんでるか
			{
				return selectNum_;
			}
			lpItemBoxPool.Get(playerPtr_[0]->GetDrawPos(), playerPtr_[0]->IsFull());
			playerPtr_[0]->ResetMove();	//動いたのをリセット
			rock[0] = false;
		}

		itemPtr_[0]->SetInfo(playerPtr_[0]->GetDrawPos(), playerPtr_[0]->GetSelectItem(), playerPtr_[0]->GetUseItem(), playerPtr_[0]->GetInfoDrawPos(1));

		itemPtr_[0]->Update(delta, playerPtr_[0]->GetAngle(), playerPtr_[0]->GetDisVec2());

		if (rock[0] == false && itemPtr_[0]->candle != CANDLE::NO_USE)
		{
			rock[0] = true;
			playerPtr_[0]->Candle(CANDLE::MOVE_PLAS);
		}
	}

	//各進捗ごとの更新処理
	ProgressUpdate();

	return SCENE_ID::CONTINUE;
}

int TutorialScene::Draw(void)
{
	SetDrawScreen(screenM_);
	ClsDrawScreen();

	//ゲーム画面の描画
	DrawGraph(0, 0, image_, true);

	mapPtr_->Draw(playerPtr_[0]->GetMap());

	playerPtr_[0]->Draw(0);

	SetDrawScreen(screenP_);
	ClsDrawScreen();

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	playerPtr_[0]->DrawMoveLine();

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 1);

	SetDrawScreen(screenM_);

	DrawGraph(0, 0, screenP_, true);

	lpItemBoxPool.Draw(delta_[0]);

	playerPtr_[0]->DrawPlayer(false, -8);

	itemPtr_[0]->Draw(0);

	playerPtr_[0]->DrawInfo(1);

	lpTextPool.Draw(delta_[0]);

	//チュートリアルシーンの描画
	SetDrawScreen(screen_);
	ClsDrawScreen();
	SetDrawBright(bright_, bright_, bright_);
	DrawGraph(0, 0, screenM_, true);
	SetDrawBright(255, 255, 255);

	//各進捗の描画処理
	ProgressDraw();

	//テキストの描画
	if (fadeIn_ == false && fadeOut_ == false)
	{
		textPtr_->Draw(delta_[0]);
	}

	//DrawFormatString(0, 200, 0xffffff, "%.3lf", tipsTime_);
	//DrawFormatString(0, 220, 0xffffff, "%d", progressNum_);
	return screen_;
}

void TutorialScene::Release(void)
{
	textPtr_->Release();
	lpMaterialMng.DeleteGraphHandle("tutorial");

	itemPtr_[0]->Release();
	itemPtr_.clear();

	playerPtr_[0]->Release();
	playerPtr_.clear();

	mapPtr_->Release();
	mapPtr_.release();

	lpItemBoxPool.Release();
	lpMaterialMng.DeleteGraphHandle("player");
	lpMaterialMng.DeleteGraphHandle("manual");
	lpMaterialMng.DeleteGraphHandle("image/back/GameScene.jpg");
	lpMaterialMng.DeleteSoundHandle("sound/DB.wav");
}

const int TutorialScene::GetNum(void)
{
	return 0;
}

const SCENE_ID TutorialScene::GetScene(void)
{
	return SCENE_ID::TUTORIAL;
}

void TutorialScene::ChackTextMode(TEXT_MODE textMode)
{
	switch (textMode)
	{
	case TEXT_MODE::OPERATION:
		bright_ = 255;
		break;
	case TEXT_MODE::MANUAL:
		bright_ = 125;
		break;
	case TEXT_MODE::CHANGE:
		fadeOut_ = true;
		break;
	}
}

void TutorialScene::FadeCommand(void)
{
	if (fadeOut_ == true)
	{
		bright_ -= static_cast<int>(delta_[0]);
		if (bright_ <= 0)
		{
			fadeOut_ = false;
			fadeIn_ = true;
			bright_ = 0;
			textPtr_->SetText("two");
		}
	}
	else if (fadeIn_ == true)
	{
		bright_ += static_cast<int>(delta_[0]);
		if (bright_ >= 255)
		{
			fadeIn_ = false;
			bright_ = 255;
		}
	}
}

bool TutorialScene::CheckProgress(int num)
{
	switch (num)
	{
	case 0:
		if (playerPtr_[0]->GetMode() == MODE::MOVE)
		{
			progressNum_++;
			return true;
		}
		break;
	case 1:
		if (playerPtr_[0]->GetDrawPos() == Vector2{275, 270})
		{
			progressNum_++;
			return true;
		}
		break;
	case 2:
		if (player_[0] == true)
		{
			progressNum_++;
			return true;
		}
		break;
	case 3:
		if (playerPtr_[0]->GetMode() == MODE::ITEM)
		{
			progressNum_++;
			return true;
		}
		break;
	case 4:
		if (playerPtr_[0]->GetMode() == MODE::MOVE)
		{
			progressNum_++;
			return true;
		}
		break;
	case 5:
		if (playerPtr_[0]->GetMode() == MODE::SELECT)
		{
			if (playerPtr_[0]->GetPoint() == 5)
			{
				progressNum_++;
				return true;
			}
		}
		break;
	case 6:
		if (textPtr_->GetChildItr() == textPtr_->GetParentItr()->end())
		{
			progressNum_++;
			return true;
		}
		break;
	}
	return false;
}

void TutorialScene::ProgressUpdate(void)
{

	if (bright_ == 255)
	{
		tipsTime_ -= delta_[0];
	}
	else
	{
		tipsTime_ = TIP_TIME;
	}

	switch (progressNum_)
	{
	case 1:
		alpha_ = sin(delta_[1]) * 125 + 125;
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	}
}

void TutorialScene::ProgressDraw(void)
{
	switch (progressNum_)
	{
	case 1:
		DrawCircle(
			(OFFSET_X - POINT_SIZE) + ((20 % 6) * OFFSET_SIZE),
			(OFFSET_Y - POINT_SIZE) + ((20 / 6) * OFFSET_SIZE),
			11, GetColor(255, static_cast<int>(alpha_), static_cast<int>(alpha_)));
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	}
}

void TutorialScene::TipDraw(void)
{

}
