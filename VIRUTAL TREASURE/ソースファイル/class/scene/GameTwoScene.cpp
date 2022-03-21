#include <DxLib.h>
#include "../manager/MaterialManager.h"
#include "../game/text/TextPool.h"
#include "../game/item/ItemBoxPool.h"
#include "../Input/P1Input.h"
#include "../Input/P2Input.h"
#include "GameTwoScene.h"

GameTwoScene::GameTwoScene(INPUT_TYPE type) :
	BaseScene(type)
{
	Init();
}

GameTwoScene::~GameTwoScene()
{
}

bool GameTwoScene::Init(void)
{
	lpItemBoxPool.Init();
	image_ = lpMaterialMng.LoadGraphHandle("image/back/GameScene.jpg");
	if (image_ == -1)
	{
		return false;
	}
	screenP_ = lpMaterialMng.LoadScreenic("player", SCREEN_SIZE_X, SCREEN_SIZE_Y);
	screen_ = lpMaterialMng.LoadScreenic("game_two", SCREEN_SIZE_X, SCREEN_SIZE_Y);
	color_.clear();
	winPlayer_ = 0;
	selectNum_ = SCENE_ID::RESULT;	//ゲーム終了したらリザルトシーンへ
	rock[0] = false;
	rock[1] = false;

	//アイテムボックスを設置：6個くらい
	for (int y = 0; y < 6; y++)
	{
		lpItemBoxPool.Generate(rand() % POINT_SIZE, static_cast<ITEM>(rand() % static_cast<int>(ITEM::NONE)), GREEN.GetColorCode());
	}

	playerPtr_.reserve(2);
	itemPtr_.reserve(2);

	//各インスタンス生成
	mapPtr_ = std::make_unique<Map>();

	playerPtr_.emplace_back(std::make_unique<Player>(
		"image/player/player1.png",
		"image/player/shadow1.png"));
	playerPtr_.emplace_back(std::make_unique<Player>(
		"image/player/player2.png",
		"image/player/shadow2.png"));

	itemPtr_.emplace_back(std::make_unique<Item>());
	itemPtr_.emplace_back(std::make_unique<Item>());

	int point1 = rand() % POINT_SIZE;
	int point2 = rand() % POINT_SIZE;

	if (point1 == point2)	//目的地がもし重なっていたら
	{
		point2 += 1;
		point2 = point2 % POINT_SIZE;
	}

	//各初期化処理
	if (!mapPtr_->Init(point1, point2)) 
	{
		return false;
	}
	if (!playerPtr_[0]->Init(0, point1, BLUE))
	{
		return false;
	}
	if (!playerPtr_[1]->Init(35, point2, RED))
	{
		return false;
	}
	if (!itemPtr_[0]->Init()) 
	{
		return false;
	}
	if (!itemPtr_[1]->Init())
	{
		return false;
	}

	return true;
}

SCENE_ID GameTwoScene::Update(double delta)
{
	delta_ = delta;

	//入力情報の取得
	for (int t = 0; t < 2; t++)
	{
		ptr_[t]->SetKeyList(inputType_);
		input_[t] = ptr_[t]->GetCntData();
	}

	bool player[2];	
	player[0] = playerPtr_[0]->Update(input_[0], delta);
	player[1] = playerPtr_[1]->Update(input_[1], delta);

	if (player[0] == true && player[1] == true)//各プレイヤーの移動が終了したか
	{
		if (playerPtr_[0]->CheckHap())	//間違えたところをかこんでるか
		{
			winPlayer_ = 1;
			return selectNum_;
		}

		if(playerPtr_[1]->CheckHap())
		{
			winPlayer_ = 2;
			return selectNum_;
		}
		lpItemBoxPool.Get(playerPtr_[0]->GetDrawPos(), playerPtr_[1]->GetDrawPos(), playerPtr_[0]->IsFull(), playerPtr_[1]->IsFull());
		playerPtr_[0]->ResetMove();	//動いたのをリセット
		playerPtr_[1]->ResetMove();
		rock[0] = false;
		rock[1] = false;
	}

	itemPtr_[0]->SetInfo(playerPtr_[0]->GetDrawPos(), playerPtr_[0]->GetSelectItem(), playerPtr_[0]->GetUseItem(), playerPtr_[0]->GetInfoDrawPos(1));
	itemPtr_[1]->SetInfo(playerPtr_[1]->GetDrawPos(), playerPtr_[1]->GetSelectItem(), playerPtr_[1]->GetUseItem(), playerPtr_[0]->GetInfoDrawPos(2));

	itemPtr_[0]->Update(delta, playerPtr_[0]->GetAngle(), playerPtr_[0]->GetDisVec2());
	itemPtr_[1]->Update(delta, playerPtr_[1]->GetAngle(), playerPtr_[1]->GetDisVec2());

	if (rock[0] == false && itemPtr_[0]->candle != CANDLE::NO_USE)
	{
		rock[0] = true;
		playerPtr_[0]->Candle(itemPtr_[0]->candle);
	}

	if (rock[1] == false && itemPtr_[1]->candle != CANDLE::NO_USE)
	{
		rock[1] = true;
		playerPtr_[1]->Candle(itemPtr_[1]->candle);
	}

	if (playerPtr_[0]->IsChange_ == true || playerPtr_[1]->IsChange_ == true)
	{
		int index = playerPtr_[0]->GetPoint();
		playerPtr_[0]->SetPos(playerPtr_[1]->GetPoint());
		playerPtr_[1]->SetPos(index);
	}

	if (playerPtr_[0]->IsHere_ == true)
	{
		playerPtr_[1]->SetPos(playerPtr_[0]->GetPoint());
	}

	if (playerPtr_[1]->IsHere_ == true)
	{
		playerPtr_[0]->SetPos(playerPtr_[1]->GetPoint());
	}

	return SCENE_ID::CONTINUE;
}

int GameTwoScene::Draw(void)
{
	SetDrawScreen(screen_);
	ClsDrawScreen();
	bool over = playerPtr_[0]->GetDrawPos() == playerPtr_[1]->GetDrawPos();

	DrawGraph(0, 0, image_, true);
	//DrawBox(0, 0, screen_sizeX, screen_sizeY, 0x115415, true);

	mapPtr_->Draw(playerPtr_[0]->GetMap(), playerPtr_[1]->GetMap());

	playerPtr_[0]->Draw(0);
	playerPtr_[1]->Draw(50);

	SetDrawScreen(screenP_);
	ClsDrawScreen();

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	playerPtr_[0]->DrawMoveLine();
	playerPtr_[1]->DrawMoveLine();

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 1);

	SetDrawScreen(screen_);

	DrawGraph(0, 0, screenP_, true);

	lpItemBoxPool.Draw(delta_);

	playerPtr_[0]->DrawPlayer(over, -8);
	playerPtr_[1]->DrawPlayer(over, 8);

	itemPtr_[0]->Draw(0);
	itemPtr_[1]->Draw(1);

	playerPtr_[0]->DrawInfo(1);
	playerPtr_[1]->DrawInfo(2);

	lpTextPool.Draw(delta_);
	
	return screen_;
}

void GameTwoScene::Release(void)
{
	itemPtr_[1]->Release();
	itemPtr_[0]->Release();
	itemPtr_[1].release();
	itemPtr_[0].release();
	itemPtr_.clear();

	playerPtr_[1]->Release();
	playerPtr_[0]->Release();
	playerPtr_[1].release();
	playerPtr_[0].release();
	playerPtr_.clear();

	mapPtr_->Release();
	mapPtr_.release();

	lpItemBoxPool.Release();
	lpMaterialMng.DeleteGraphHandle("player");
	lpMaterialMng.DeleteGraphHandle("game_two");
	lpMaterialMng.DeleteGraphHandle("image/back/GameScene.jpg");
}

const int GameTwoScene::GetNum(void)
{
	return winPlayer_;
}

const SCENE_ID GameTwoScene::GetScene(void)
{
	return SCENE_ID::GAME_TWO;
}


