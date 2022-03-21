#include <DxLib.h>
#include <string.h>
#include "../ChangeNum.h"
#include "../manager/MaterialManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(INPUT_TYPE type):
	BaseScene(type)
{
	Init();
}

TitleScene::~TitleScene()
{

}

bool TitleScene::Init(void)
{
	offset_ = {};
	pos_ = {};
	image_ = lpMaterialMng.LoadGraphHandle("image/back/TitleScene.jpg");
	if (image_ == -1)
	{
		return false;
	}
	sound_[0] = lpMaterialMng.LoadSoundHandle("sound/DB.wav");
	sound_[1] = lpMaterialMng.LoadSoundHandle("sound/frog.wav");
	if (sound_[0] == -1 || sound_[1] == -1)
	{
		return false;
	}
	titleImg_.resize(IMG_COUNT);

	for (int i = 0; i < IMG_COUNT; i++)
	{
		titleImg_[i] = lpMaterialMng.LoadGraphHandle(imgFile_[i]);
		if (titleImg_[i] == -1)
		{
			return false;
		}
	}

	msgGrassImg_ = lpMaterialMng.LoadGraphHandle("image/title/grass.png");
	msgPatternImg_ = lpMaterialMng.LoadDivGraphic("image/title/pattern.png", PATTERN_COUNT);
	zoom_ = 0.0;

	GetGraphSize(titleImg_[5], &speechSize_.x, &speechSize_.y);
	lineColor_.Color3Code(0x777777);
	screen_ = lpMaterialMng.LoadScreenic("title", SCREEN_SIZE_X, SCREEN_SIZE_Y);
	msgScreen_ = lpMaterialMng.LoadScreenic("message", SCREEN_SIZE_X, SCREEN_SIZE_Y);
	selectNum_ = SCENE_ID::GAME_ONE;
	isSelect_ = false;
	alpha_ = 0;

	color_.resize(5U);
	color_[0] = 0xffffff;
	color_[1] = 0xffffff;
	color_[2] = 0xffffff;
	color_[3] = 0xffffff;
	color_[4] = 0xffffff;

	pos_[0].x = 650;
	pos_[0].y = 50;
	pos_[1].x = SCREEN_SIZE_X / 2 + 600;
	pos_[1].y = 189;
	pos_[2].x = SCREEN_SIZE_X / 2 + 700;
	pos_[2].y = 190 + OFFSET;
	pos_[3].x = SCREEN_SIZE_X / 2 - 38 + GEAR_SIZE_HALF_X;
	pos_[3].y = 270 + OFFSET + GEAR_SIZE_HALF_Y;
	pos_[4].x = 580 + 25;
	pos_[4].y = 440 + 15;

	offset_[0].x = 600;
	offset_[0].y = 0;
	offset_[1].x = 700;
	offset_[1].y = 0;
	offset_[2].x = 0;
	offset_[2].y = 1400;
	offset_[3].x = 1600;

	patternPos_.resize(PATTERN_NUM);
	for (auto& p : patternPos_)
	{
		p.x = rand() % 38 + 1;
		p.y = rand() % 28 + 1;
		p.num = rand() % PATTERN_TYPE;
	}

	int bugImg[4];
	bugImg[0]= lpMaterialMng.LoadGraphHandle("image/bug/bug1.png");
	bugImg[1]= lpMaterialMng.LoadGraphHandle("image/bug/bug2.png");
	bugImg[2]= lpMaterialMng.LoadGraphHandle("image/bug/bug3.png");
	bugImg[3]= lpMaterialMng.LoadGraphHandle("image/bug/bug4.png");

	for (int b = 0; b < BUG_COUNT; b++)
	{
		bugPool_.emplace_back(std::make_unique<Bug>(bugImg[rand() % 4]));
	}
	
	return true;
}

SCENE_ID TitleScene::Update(double delta)
{
	//デバック：模様の変更
	/*if (input_[0][INPUT_LIST::MOUSE_LEFT][KEY::TRG_DOWN])
	{
		for (auto& p : patternPos_)
		{
			p.x = rand() % 38 + 1;
			p.y = rand() % 28 + 1;
			p.num = rand() % PATTERN_TYPE;
		}
	}*/

	if (CheckHitKey(KEY_INPUT_B))
	{
		if (bugPool_.size() > 0)
		{
			(*bugPool_.begin())->Generate({ rand() % 600 + 20, rand() % 300 + 20 }, 1.0, 100.0);
			bugList_.splice(bugList_.end(), std::move(bugPool_), bugPool_.begin());
			//splice:Listの要素の移動※[移動先].splice([移動先のどこに移動するか],[std::move([移動元])],[移動させる要素番号],[いどうさせる要素番号の最後])
			//最小限にしかループしなくなる
		}
	}

	if (CheckMoveEnd())
	{
		//入力情報の取得
		for (int t = 0; t < 2; t++)
		{
			ptr_[t]->SetKeyList(inputType_);
			input_[t] = ptr_[t]->GetCntData();
		}

		//次のシーン選択
		if ((input_[0][INPUT_LIST::DOWN][KEY::TRG_DOWN] || input_[1][INPUT_LIST::DOWN][KEY::TRG_DOWN])
			&& selectNum_ < SCENE_ID::END)
		{
			++selectNum_;
			++select_;
			PlaySoundMem(sound_[0], DX_PLAYTYPE_BACK);
		}
		if ((input_[0][INPUT_LIST::UP][KEY::TRG_DOWN] || input_[1][INPUT_LIST::UP][KEY::TRG_DOWN])
			&& selectNum_ > SCENE_ID::GAME_ONE)
		{
			--selectNum_;
			--select_;
			PlaySoundMem(sound_[0], DX_PLAYTYPE_BACK);
		}

		for (auto& c : color_)
		{
			c = 0xffffff;
		}

		color_[select_] = 0x888888;
		lineColor_.Color3Code(0x777777);

		if (input_[0][INPUT_LIST::A][KEY::TRG_DOWN] || input_[1][INPUT_LIST::A][KEY::TRG_DOWN])
		{
			isSelect_ = true;
			return selectNum_;	//キーを押したら選択したシーンへ移動
		}
	}
	else
	{
		//画像の移動処理
		ImgMove();
	}

	//虫の更新処理
	for (const auto& bug : bugList_)
	{
		bug->Update(delta);
	}

	return SCENE_ID::CONTINUE; 
}

int TitleScene::Draw(void)
{
	//描画処理
	SetDrawScreen(screen_);
	ClsDrawScreen();
	DrawGraph(0, 0, image_, true);

	//VIRUTAL TREASURE(タイトル)
	SetDrawBright(UpDown(&alpha_, 7), 255, 255);
	DrawGraph(pos_[0].x, pos_[0].y, titleImg_[2], true);		//50 50
	SetDrawBright(255, 255, 255);

	//シングルプレイ
	DrawBox(150 + offset_[0].x, 150, 490 + offset_[0].x, 225, color_[0], true);
	DrawBox(150 + offset_[0].x, 150, 490 + offset_[0].x, 225, 0x777777, false);
	DrawRotaGraph(pos_[1].x, pos_[1].y, 0.8, 0.0, titleImg_[0], true);

	//ダブルプレイ
	DrawBox(150 + offset_[1].x, 150 + OFFSET, 490 + offset_[1].x, 225 + OFFSET, color_[1], true);
	DrawBox(150 + offset_[1].x, 150 + OFFSET, 490 + offset_[1].x, 225 + OFFSET, 0x777777, false);
	DrawRotaGraph(pos_[2].x, pos_[2].y, 0.8, 0.0, titleImg_[1], true);

	//オプション
	DrawBox(SCREEN_SIZE_X / 2 - 38,
		270 + OFFSET + offset_[2].y,
		SCREEN_SIZE_X / 2 + 38,
		346 + OFFSET + offset_[2].y,
		color_[2], true);
	DrawBox(SCREEN_SIZE_X / 2 - 38,
		270 + OFFSET + offset_[2].y,
		SCREEN_SIZE_X / 2 + 38,
		346 + OFFSET + offset_[2].y,
		0x777777, false);
	DrawRotaGraph(pos_[3].x, pos_[3].y + offset_[2].y, 0.3, 0.0, titleImg_[3], true);

	//ゲーム終了
	DrawBox(580 + offset_[3].x, 440, 630 + offset_[3].x, 470, color_[3], true);
	DrawBox(580 + offset_[3].x, 440, 630 + offset_[3].x, 470, 0x777777, false);
	DrawRotaGraph(pos_[4].x + offset_[3].x, pos_[4].y, 0.08, 0.0, titleImg_[4], true);
	if (selectNum_ == SCENE_ID::END)
	{
		SpeechBalloon(0.08);
	}
	else
	{
		SpeechBalloon(-0.2);
	}
	DrawRotaGraph2(600, 440, speechSize_.x, speechSize_.y, scale_, 0.0, titleImg_[5], true);

	if (!isSelect_)
	{
		lineColor_.Color3Code(0x777777);
	}

	if (CheckMoveEnd())
	{
		for (int l = 0; l < 5; l++)
		{
			if (isSelect_)
			{
				lineColor_ = YELLOW;
			}
			switch (select_)
			{
			case 0:
			case 1:
				DrawBox(149 - l,
					149 + OFFSET * select_ - l,
					491 + l,
					226 + OFFSET * select_ + l,
					lineColor_.GetColorCode(), false);
				break;
			case 2:
				DrawBox(SCREEN_SIZE_X / 2 - 39 - l,
					269 + OFFSET - l,
					SCREEN_SIZE_X / 2 + 39 + l,
					347 + OFFSET + l,
					lineColor_.GetColorCode(), false);
			default:
				//なし
				break;
			}
			
			lineColor_ -= 20;
		}
	}

	//虫の描画
	//表示時間が過ぎたら元に戻す
	for (std::list<std::unique_ptr<Bug>>::iterator itr = bugList_.begin(); itr != bugList_.end();)
	{
		(*itr)->Draw();
		if (!(*itr)->IsAlive())
		{
			bugPool_.splice(bugPool_.end(), std::move(bugList_), itr++);
			//itr++しないとitrが使用不可になる
			//moveで使用不可になるがitr++で次のitrが使用可能なので使うことができる
		}
		else
		{
			++itr;
			//++itrの方がitr++よりも処理が早い
		}
	}

	MessageDraw();
	return screen_;
}

void TitleScene::Release(void)
{
	lpMaterialMng.DeleteGraphHandle("title");
	lpMaterialMng.DeleteGraphHandle("message");

	for (const auto key : imgFile_)
	{
		lpMaterialMng.DeleteGraphHandle(key);
	}

	lpMaterialMng.DeleteGraphHandle("image/back/TitleScene.jpg");
	lpMaterialMng.DeleteSoundHandle("sound/DB.wav");
	lpMaterialMng.DeleteGraphHandle("image/bug/bug1.png");
	lpMaterialMng.DeleteGraphHandle("image/bug/bug2.png");
	lpMaterialMng.DeleteGraphHandle("image/bug/bug3.png");
	lpMaterialMng.DeleteGraphHandle("image/bug/bug4.png");
	lpMaterialMng.DeleteGraphHandle("image/title/grass.png");
	lpMaterialMng.DeleteGraphHandle("image/title/pattern.png");

	bugPool_.clear();
	bugList_.clear();
}

const int TitleScene::GetNum(void)
{
	return 0;
}

const SCENE_ID TitleScene::GetScene(void)
{
	return SCENE_ID::TITLE;
}

void TitleScene::ImgMove(void)
{
	for (int e = 0; e < 3; e++)
	{
		pos_[e].x -= 10;
		offset_[e].x -= 10;
	}

	offset_[2].y -= 20;
	offset_[3].x -= 20;

	if (pos_[0].x < 50)
	{
		pos_[0].x = 50;
	}

	if (pos_[1].x < SCREEN_SIZE_X / 2)
	{
		pos_[1].x = SCREEN_SIZE_X / 2;
		offset_[0].x = 0;
	}

	if (pos_[2].x < SCREEN_SIZE_X / 2)
	{
		pos_[2].x = SCREEN_SIZE_X / 2;
		offset_[1].x = 0;
	}

	if (offset_[2].y < 0)
	{
		offset_[2].y = 0;
	}

	if (offset_[3].x < 0)
	{
		offset_[3].x = 0;
	}
}

bool TitleScene::CheckMoveEnd(void)
{
	if (offset_[0].x == 0 &&
		offset_[1].x == 0 &&
		offset_[2].y == 0 &&
		offset_[3].x == 0 &&
		pos_[1].x == SCREEN_SIZE_X / 2 &&
		pos_[2].x == SCREEN_SIZE_X / 2 &&
		pos_[0].x == 50)
	{
		return true;
	}
	return false;
}

void TitleScene::SpeechBalloon(double num)
{
	scale_ += num;
	if (scale_ > 0.7)
	{
		scale_ = 0.7;
	}
	if (scale_ < 0.0)
	{
		scale_ = 0.0;
	}
}

void TitleScene::MessageDraw(void)
{
	SetDrawScreen(msgScreen_);
	ClsDrawScreen();

	DrawGraph(0, 0, msgGrassImg_, true);
	for (const auto p : patternPos_)
	{
		DrawGraph(p.x * 16, p.y * 16, msgPatternImg_[p.num], false);
	}

	SetDrawScreen(screen_);

	DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, zoom_, 0.0, msgScreen_, true);
}
