#include <DxLib.h>
#include "../manager/MaterialManager.h"
#include "../game/text/TextPool.h"
#include "../game/item/ItemBoxPool.h"
#include "../Input/P1Input.h"
#include "../Input/P2Input.h"
#include "GameSoloScene.h"

GameSoloScene::GameSoloScene(INPUT_TYPE type) :
	BaseScene(type)
{
	Init();
}

GameSoloScene::~GameSoloScene()
{
}

bool GameSoloScene::Init(void)
{
	lpItemBoxPool.Init();
	image_ = lpMaterialMng.LoadGraphHandle("image/back/GameScene.jpg");
	if (image_ == -1)
	{
		return false;
	}
	screenP_ = lpMaterialMng.LoadScreenic("player", SCREEN_SIZE_X, SCREEN_SIZE_Y);
	screen_ = lpMaterialMng.LoadScreenic("game_solo", SCREEN_SIZE_X, SCREEN_SIZE_Y);
	color_.clear();
	selectNum_ = SCENE_ID::RESULT;	//ゲーム終了したらリザルトシーンへ
	rock = false;
	makeFire_ = 0;

	//アイテムボックスを設置：6個くらい
	for (int y = 0; y < 6; y++)
	{
		lpItemBoxPool.Generate(
			rand() % POINT_SIZE,
			static_cast<ITEM>(rand() % static_cast<int>(ITEM::NONE)),
			GREEN.GetColorCode());
	}

	//各インスタンス生成
	mapPtr_ = std::make_unique<Map>();

	playerPtr_ = std::make_unique<Player>(
		"image/player/player1.png",
		"image/player/shadow1.png");

	itemPtr_ = std::make_unique<Item>();

	//敵のインスタンス生成処理
	std::vector<int> imageVec = lpMaterialMng.LoadDivGraphic(
		"image/enemy/fire.png", 
		{ Fire::ANIM_SIZE, static_cast<int>(MOVE_DIR::MAX) });
	for (int t = 0; t < 25; t++)
	{
		firePtrPool_.emplace_back(std::make_unique<Fire>(imageVec));
	}

	int point = rand() % POINT_SIZE;

	//各初期化処理
	if (!mapPtr_->Init(point))
	{
		return false;
	}

	if (!playerPtr_->Init(30, point, MAGENTA))
	{
		return false;
	}

	if (!itemPtr_->Init())
	{
		return false;
	}

	return true;
}

SCENE_ID GameSoloScene::Update(double delta)
{
	delta_ = delta;
	playerPtr_->SetItemLife(itemPtr_->GetLife());

	//入力情報の取得
	ptr_[0]->SetKeyList(inputType_);
	input_[0] = ptr_[0]->GetCntData();

	bool player;
	player = playerPtr_->Update(input_[0], delta);

	if (player == true)
	{
		if (playerPtr_->CheckHap())	//GameClear
		{
			return selectNum_;
		}
		lpItemBoxPool.Get(playerPtr_->GetDrawPos(), playerPtr_->IsFull());
		playerPtr_->ResetMove();	//動いたのをリセット
		rock = false;
		for (const auto& fire : firePtrList_)
		{
			fire->Check(playerPtr_->GetSurround());
		}

		//表示時間が過ぎたら元に戻す
		for (std::list<std::unique_ptr<Fire>>::iterator itr = firePtrList_.begin(); itr != firePtrList_.end();)
		{
			if (!(*itr)->IsAlive())
			{
				firePtrPool_.splice(firePtrPool_.end(), std::move(firePtrList_), itr++);
				//itr++しないとitrが使用不可になる
				//moveで使用不可になるがitr++で次のitrが使用可能なので使うことができる
			}
			else
			{
				++itr;
				//++itrの方がitr++よりも処理が早い
			}
		}

		makeFire_++;
		if (makeFire_ % 2 == 0) 
		{
			for (const auto& fire : firePtrList_)
			{
				fire->Move(
					static_cast<MOVE_DIR>(rand() % static_cast<int>(MOVE_DIR::MAX)));
			}
		}

		if (firePtrPool_.size() > 0 && makeFire_ % 5 == 0)
		{
			(*firePtrPool_.begin())->Create(rand() % 4);
			firePtrList_.splice(firePtrList_.end(), std::move(firePtrPool_), firePtrPool_.begin());
			//splice:Listの要素の移動※[移動先].splice([移動先のどこに移動するか],[std::move([移動元])],[移動させる要素番号],[移動させる要素番号の最後])
			//最小限にしかループしなくなる
		}
	}

	itemPtr_->SetInfo(playerPtr_->GetDrawPos(), playerPtr_->GetSelectItem(), playerPtr_->GetUseItem(), playerPtr_->GetInfoDrawPos(1));

	itemPtr_->Update(delta, playerPtr_->GetAngle(), playerPtr_->GetDisVec2());

	if (itemPtr_->setMode_ == true)
	{
		playerPtr_->SetMode(MODE::WARP);
	}

	if (rock == false && itemPtr_->candle != CANDLE::NO_USE)
	{
		rock = true;
		playerPtr_->Candle(itemPtr_->candle);
	}

	for (const auto& fire : firePtrList_)
	{
		fire->Update();
	}

	return SCENE_ID::CONTINUE;
}

int GameSoloScene::Draw(void)
{
	SetDrawScreen(screen_);
	ClsDrawScreen();

	DrawGraph(0, 0, image_, true);
	//DrawBox(0, 0, screen_sizeX, screen_sizeY, 0x115415, true);

	mapPtr_->Draw(playerPtr_->GetMap());

	playerPtr_->Draw(0);

	SetDrawScreen(screenP_);
	ClsDrawScreen();

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	playerPtr_->DrawMoveLine();

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 1);

	SetDrawScreen(screen_);

	DrawGraph(0, 0, screenP_, true);

	lpItemBoxPool.Draw(delta_);

	playerPtr_->DrawPlayer(false, -8);

	itemPtr_->Draw(0);

	for (const auto& fire : firePtrList_)
	{
		fire->Draw();
	}

	playerPtr_->DrawInfo(1);

	if (CheckHitKey(KEY_INPUT_B))
	{
		Vector2 oo;
		GetMousePoint(&oo.x, &oo.y);
		DrawFormatString(0, 0, 0xffffff, "%d  %d", firePtrList_.size(), firePtrPool_.size());
		DrawFormatString(0, 20, 0, "%d  %d", oo.x, oo.y);
	}

	lpTextPool.Draw(delta_);
	return screen_;
}

void GameSoloScene::Release(void)
{
	itemPtr_->Release();
	itemPtr_.release();

	playerPtr_->Release();
	playerPtr_.release();

	mapPtr_->Release();
	mapPtr_.release();

	if (firePtrList_.size() > 0)
	{
		firePtrList_.erase(firePtrList_.begin(), firePtrList_.end());
	}

	if (firePtrPool_.size() > 0)
	{
		firePtrPool_.erase(firePtrPool_.begin(), firePtrPool_.end());
	}

	lpItemBoxPool.Release();
	lpMaterialMng.DeleteGraphHandle("player");
	lpMaterialMng.DeleteGraphHandle("game_solo");
	lpMaterialMng.DeleteGraphHandle("image/back/GameScene.jpg");
	lpMaterialMng.DeleteGraphHandle("image/enemy/fire.png");
}

const int GameSoloScene::GetNum(void)
{
	return 0;
}

const SCENE_ID GameSoloScene::GetScene(void)
{
	return SCENE_ID::GAME_ONE;
}
