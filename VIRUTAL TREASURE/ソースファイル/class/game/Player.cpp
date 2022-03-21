#include <DxLib.h>
#include <cmath>
#include "../scene/GameTwoScene.h"
#include "Map.h"
#include "Player.h"
#include "text/TextPool.h"

bool Player::Init(int pos, int point, Color3 color)
{
	if (image_["dir"][0] == -1)
	{
		return false;
	}

	for (const auto& sound : sound_)
	{
		if (sound == -1)
		{
			return false;
		}
	}

	for (const int& img : image_["count"])
	{
		if (img == -1)
		{
			return false;
		}
	}

	for (const int& img : image_["normal"])
	{
		if (img == -1)
		{
			return false;
		}
	}

	for (const int& img : image_["shadow"])
	{
		if (img == -1)
		{
			return false;
		}
	}

	for (const int& img : image_["target"])
	{
		if (img == -1)
		{
			return false;
		}
	}

	if (font_ == -1)
	{
		return false;
	}

	target_ = targetSenter_ = 0.0;
	useMagnet_ = false;
	itemLife_ = 0.0;

	map_ = point;
	player_.pos[0] = respawn_ = pos;
	alpha_ = 0;
	color_ = color;
	defultColor_ = color_.GetColorCode();
	IsChange_ = false;
	IsHere_ = false;
	fullItem_ = true;

	select_ = MODE::MOVE;
	moveEnd_ = fadeIn_ = fadeOut_ = false;
	player_.item.resize(4U);
	selectInven_ = 0;
	for (auto& item : player_.item)
	{
		item = ITEM::CANDLE;
	}
	canMove_[DIR::UP].second = DX_PI / 180.0 * 270.0;
	canMove_[DIR::DOWN].second = DX_PI / 180.0 * 90.0;
	canMove_[DIR::LIFT].second = DX_PI / 180.0 * 180.0;
	canMove_[DIR::RIGHT].second = 0.0;
	for (int p = 1; p < 7; p++)
	{
		player_.pos[p] = player_.pos[0];
	}
	player_.move = 4;
	player_.dir = DIR::DOWN;
	useItem_ = ITEM::NONE;
	mode_ = MODE::SELECT;
	selectItem_ = ITEM::NONE;
	angle_ = 0.0;
	surround_ = -1;
	animCnt_[0].first = 0.0;
	animCnt_[0].second = 0;
	animCnt_[1].second = 0;
	animCnt_[1].second = 0;
	delta_ = 0.0;
	lock_ = false;
	player_.warp = player_.pos[0];
	player_.delta_ = 0.0;
	moveSpeed_ = 1.0;

	for (int draw = 0; draw < 7; draw++)
	{
		drawPos_[draw].x = (OFFSET_X - POINT_SIZE) + ((player_.pos[draw] % 6) * OFFSET_SIZE);
		drawPos_[draw].y = (OFFSET_Y - POINT_SIZE) + ((player_.pos[draw] / 6) * OFFSET_SIZE);
	}
	movePow_ = { 0, 0 };
	isMove_ = false;

	return true;
}

bool Player::Update(const InputList input, double delta)
{
	delta_ = delta;

	//入力情報の取得
	input_ = input;

	int itemSum = INVECTORY_MAX;

	for (const auto& item : player_.item)
	{
		if (item == ITEM::NONE)
		{
			itemSum--;
		}
	}

	angle_ = atan2(
		(OFFSET_Y + ((map_ / 5) * OFFSET_SIZE) + POINT_SIZE / 2) - ((OFFSET_Y - POINT_SIZE) + ((player_.pos[0] / 6) * OFFSET_SIZE)),
		(OFFSET_X + ((map_ % 5) * OFFSET_SIZE) + POINT_SIZE / 2) - ((OFFSET_X - POINT_SIZE) + ((player_.pos[0] % 6) * OFFSET_SIZE)));

	if (mode_ != MODE::SELECT && lock_ == false)
	{
		if (input_[INPUT_LIST::B][KEY::TRG_DOWN])
		{
			mode_ = MODE::SELECT;
			selectInven_ = 0;
			select_ = MODE::MOVE;
			SetSize(0);
			selectItem_ = ITEM::NONE;
		}
	}

	switch (mode_)
	{
	case MODE::SELECT:	//選択画面
		if (input_[INPUT_LIST::DOWN][KEY::TRG_DOWN] && select_ == MODE::MOVE)
		{
			if (itemSum != 0)
			{
				select_ = MODE::ITEM;
				SetSize(static_cast<int>(MODE::ITEM));
				selectItem_ = ITEM::NONE;
			}
			else
			{
				PlaySoundMem(sound_[6], DX_PLAYTYPE_BACK);
				lpTextPool.Generate("アイテムをもってないゾ！", drawPos_[0], 300.0, defultColor_);
			}
		}
		if (input_[INPUT_LIST::UP][KEY::TRG_DOWN] && select_ == MODE::ITEM)
		{
			select_ = MODE::MOVE;
			SetSize(static_cast<int>(MODE::MOVE));
		}
		if (input_[INPUT_LIST::A][KEY::TRG_DOWN])
		{
			mode_ = select_;
			SetSize(0);
			if (select_ == MODE::ITEM)
			{
				selectInven_ = 0;
			}

		}
		break;

	case MODE::MOVE:	//移動の時
		if (moveEnd_ == false && isMove_ == false)
		{
			if (input_[INPUT_LIST::LEFT][KEY::TRG_DOWN])
			{	//左移動
				if (player_.pos[0] % MAP_COUNT != 0)
				{
					lock_ = true;
					if (player_.pos[1] != player_.pos[0] - 1)
					{
						if (player_.move > 0)
						{
							Move();
							player_.pos[0] -= 1;
							player_.dir = DIR::LIFT;
						}
						else
						{
							PlaySoundMem(sound_[6], DX_PLAYTYPE_BACK);
							lpTextPool.Generate("Aボタンおして!", drawPos_[0], 400.0, defultColor_);
						}
					}
					else
					{
						Undo();
						player_.dir = DIR::LIFT;
					}
				}
				else
				{
					PlaySoundMem(sound_[6], DX_PLAYTYPE_BACK);
				}
			}

			if (input_[INPUT_LIST::RIGHT][KEY::TRG_DOWN])
			{	//右移動
				if (player_.pos[0] % MAP_COUNT != MAP_COUNT - 1)
				{
					lock_ = true;
					if (player_.pos[1] != player_.pos[0] + 1)
					{
						if (player_.move > 0)
						{
							Move();
							player_.pos[0] += 1;
							player_.dir = DIR::RIGHT;
						}
						else
						{
							PlaySoundMem(sound_[6], DX_PLAYTYPE_BACK);
							lpTextPool.Generate("Aボタンおして!", drawPos_[0], 400.0, defultColor_);
						}
					}
					else
					{
						Undo();
						player_.dir = DIR::RIGHT;
					}
				}
				else
				{
					PlaySoundMem(sound_[6], DX_PLAYTYPE_BACK);
				}
			}

			if (input_[INPUT_LIST::UP][KEY::TRG_DOWN])
			{	//上移動
				if (player_.pos[0] - MAP_COUNT >= 0)
				{
					lock_ = true;
					if (player_.pos[1] != player_.pos[0] - MAP_COUNT)
					{
						if (player_.move > 0)
						{
							Move();
							player_.pos[0] -= MAP_COUNT;
							player_.dir = DIR::UP;
						}
						else
						{
							PlaySoundMem(sound_[6], DX_PLAYTYPE_BACK);
							lpTextPool.Generate("Aボタンおして!", drawPos_[0], 400.0, defultColor_);
						}
					}
					else
					{
						Undo();
						player_.dir = DIR::UP;
					}
				}
				else
				{
					PlaySoundMem(sound_[6], DX_PLAYTYPE_BACK);
				}
			}

			if (input_[INPUT_LIST::DOWN][KEY::TRG_DOWN])
			{	//下移動
				if (player_.pos[0] + MAP_COUNT < MAP_COUNT * MAP_COUNT)
				{
					lock_ = true;
					if (player_.pos[1] != player_.pos[0] + MAP_COUNT)
					{
						if (player_.move > 0)
						{
							Move();
							player_.pos[0] += MAP_COUNT;
							player_.dir = DIR::DOWN;
						}
						else
						{
							PlaySoundMem(sound_[6], DX_PLAYTYPE_BACK);
							lpTextPool.Generate("Aボタンおして!", drawPos_[0], 400.0, defultColor_);
						}
					}
					else
					{
						Undo();
						player_.dir = DIR::DOWN;
					}
				}
				else
				{
					PlaySoundMem(sound_[6], DX_PLAYTYPE_BACK);
				}
			}
		}

		if (player_.move <= 0)//4回移動したら終わり
		{
			if (input_[INPUT_LIST::A][KEY::TRG_DOWN])
			{
				if (moveEnd_ == false)
				{
					if (player_.pos[4] == player_.pos[0] && useItem_ == ITEM::NONE)
					{
						surround_ = SetSurround();
						PlaySoundMem(sound_[0], DX_PLAYTYPE_BACK);
					}
					else
					{
						PlaySoundMem(sound_[1], DX_PLAYTYPE_BACK);
						surround_ = -1;
					}
					fadeIn_ = true;
				}
				moveEnd_ = true;
			}
		}
		break;
	case MODE::ITEM:
		switch (selectInven_)//選択しているアイテム
		{
		case 0:
			if (input_[INPUT_LIST::RIGHT][KEY::TRG_DOWN])
			{
				SetSize(1);
				selectInven_ = 1;
			}
			if (input_[INPUT_LIST::DOWN][KEY::TRG_DOWN])
			{
				SetSize(2);
				selectInven_ = 2;
			}
			break;
		case 1:
			if (input_[INPUT_LIST::LEFT][KEY::TRG_DOWN])
			{
				SetSize(0);
				selectInven_ = 0;
			}
			if (input_[INPUT_LIST::DOWN][KEY::TRG_DOWN])
			{
				SetSize(3);
				selectInven_ = 3;
			}
			break;
		case 2:
			if (input_[INPUT_LIST::RIGHT][KEY::TRG_DOWN])
			{
				SetSize(3);
				selectInven_ = 3;
			}
			if (input_[INPUT_LIST::UP][KEY::TRG_DOWN])
			{
				SetSize(0);
				selectInven_ = 0;
			}
			break;
		case 3:
			if (input_[INPUT_LIST::LEFT][KEY::TRG_DOWN])
			{
				SetSize(2);
				selectInven_ = 2;
			}
			if (input_[INPUT_LIST::UP][KEY::TRG_DOWN])
			{
				SetSize(1);
				selectInven_ = 1;
			}
			break;
		}
		selectItem_ = player_.item[selectInven_];
		if (input_[INPUT_LIST::A][KEY::TRG_DOWN])
		{
			if (player_.item[selectInven_] != ITEM::NONE)
			{
				useItem_ = selectItem_;
				player_.item[static_cast<int>(selectInven_)] = ITEM::NONE;
				PlaySoundMem(sound_[5], DX_PLAYTYPE_BACK);
				mode_ = MODE::MOVE;
				lock_ = true;
			}
			else
			{
				PlaySoundMem(sound_[6], DX_PLAYTYPE_BACK);
				lpTextPool.Generate("からっぽだゾ", drawPos_[0], 300.0, defultColor_);
			}
		}
		break;
	case MODE::WARP:	//ワープモード
		targetSenter_ -= 1.0;
		target_ += 1.0;
		if (player_.warp + MAP_COUNT < MAP_COUNT * MAP_COUNT)
		{
			if (input_[INPUT_LIST::DOWN][KEY::TRG_DOWN])
			{
				player_.warp += MAP_COUNT;
			}
		}

		if (player_.warp - MAP_COUNT >= 0)
		{
			if (input_[INPUT_LIST::UP][KEY::TRG_DOWN])
			{
				player_.warp -= MAP_COUNT;
			}
		}

		if (player_.warp % MAP_COUNT != 0)
		{
			if (input_[INPUT_LIST::LEFT][KEY::TRG_DOWN])
			{
				player_.warp -= 1;
			}
		}

		if (player_.warp % MAP_COUNT != MAP_COUNT - 1)
		{
			if (input_[INPUT_LIST::RIGHT][KEY::TRG_DOWN])
			{
				player_.warp += 1;
			}
		}

		if (input_[INPUT_LIST::A][KEY::TRG_DOWN] || itemLife_ <= 0.0)
		{
			useMagnet_ = true;
			moveSpeed_ = 3.0;
			player_.pos[0] = player_.warp;
			for (int p = 1; p < 7; p++)
			{
				player_.pos[p] = player_.pos[0];
			}
		}
		
		break;
	}
	if (mode_ == MODE::MOVE)
	{
		ChackDir();//向きの処理
	}
	else
	{
		for (auto i : DIR())
		{
			canMove_[i].first = false;
		}
	}

	//プレイヤー情報のアニメ処理
	SetAnim(10.0, 1);
	
	for (const auto& i : player_.item)
	{
		fullItem_ *= i != ITEM::NONE;
	}

	if (useMagnet_ == true)
	{
		Vector2 point = {
		(OFFSET_X - POINT_SIZE) + ((player_.pos[0] % 6) * OFFSET_SIZE),
		(OFFSET_Y - POINT_SIZE) + ((player_.pos[0] / 6) * OFFSET_SIZE) };
		if (drawPos_[0] == point)
		{
			moveEnd_ = true;
		}
	}

	MoveEnd();	//移動終了
	return moveEnd_;
}

void Player::Draw(int size)
{
	Vector2 point = { 
	(OFFSET_X - POINT_SIZE) + ((player_.pos[0] % 6) * OFFSET_SIZE),
	(OFFSET_Y - POINT_SIZE) + ((player_.pos[0] / 6) * OFFSET_SIZE) };

	movePow_ = { 0, 0 };
	int diff = 0;

	if (point.x > drawPos_[0].x)
	{
		movePow_.x = static_cast<int>(delta_ * moveSpeed_);
		if (drawPos_[0].x + movePow_.x > point.x)
		{
			diff = drawPos_[0].x + movePow_.x - point.x;
			movePow_.x -= diff;
		}
		isMove_ = true;
	}
	else if (point.x < drawPos_[0].x)
	{
		movePow_.x = static_cast<int>(-delta_ * moveSpeed_);
		if (drawPos_[0].x + movePow_.x < point.x)
		{
			diff = drawPos_[0].x + movePow_.x - point.x;
			movePow_.x -= diff;
		}
		isMove_ = true;
	}
	else if (point.y < drawPos_[0].y)
	{
		movePow_.y = static_cast<int>(-delta_ * moveSpeed_);
		if (drawPos_[0].y + movePow_.y < point.y)
		{
			diff = drawPos_[0].y + movePow_.y - point.y;
			movePow_.y -= diff;
		}
		isMove_ = true;
	}
	else if (point.y > drawPos_[0].y)
	{
		movePow_.y = static_cast<int>(delta_ * moveSpeed_);
		if (drawPos_[0].y + movePow_.y > point.y)
		{
			diff = drawPos_[0].y + movePow_.y - point.y;
			movePow_.y -= diff;
		}
		isMove_ = true;
	}

	drawPos_[0] += movePow_;

	if (point.y == drawPos_[0].y && point.x == drawPos_[0].x)
	{
		moveSpeed_ = 1.0;
		isMove_ = false;
		for (int draw = 1; draw < 7; draw++)
		{
			drawPos_[draw].x = (OFFSET_X - POINT_SIZE) + ((player_.pos[draw] % 6) * OFFSET_SIZE);
			drawPos_[draw].y = (OFFSET_Y - POINT_SIZE) + ((player_.pos[draw] / 6) * OFFSET_SIZE);
		}
	}

	switch (mode_)
	{
	case MODE::ITEM:
		DrawBox(
			drawPos_[0].x,
			drawPos_[0].y - size,
			drawPos_[0].x + 75,
			drawPos_[0].y + 50 - size,
			0xaaffaa, 1);
		DrawCircle(
			drawPos_[0].x + 25,
			drawPos_[0].y + 12 - size,
			8, 0, 0, offsetSize_[0]);
		DrawCircle(
			drawPos_[0].x + 50,
			drawPos_[0].y + 12 - size,
			8, 0, 0, offsetSize_[1]);
		DrawCircle(
			drawPos_[0].x + 25,
			drawPos_[0].y + 38 - size,
			8, 0, 0, offsetSize_[2]);
		DrawCircle(
			drawPos_[0].x + 50,
			drawPos_[0].y + 38 - size,
			8, 0, 0, offsetSize_[3]);
		player_.warp = player_.pos[0];
		break;
	case MODE::SELECT:
		DrawBox(
			drawPos_[0].x,
			drawPos_[0].y - size,
			drawPos_[0].x + 75,
			drawPos_[0].y + 50 - size,
			defultColor_, 1);
		DrawCircle(
			drawPos_[0].x + 20,
			drawPos_[0].y + 10 - size,
			6, 0, 0, offsetSize_[static_cast<int>(MODE::MOVE)]);
		DrawCircle(
			drawPos_[0].x + 20,
			drawPos_[0].y + 35 - size,
			6, 0, 0, offsetSize_[static_cast<int>(MODE::ITEM)]);
		DrawExtendString(
			drawPos_[0].x + 28,
			drawPos_[0].y + 4 - size,
			0.9, 1.0,
			"移動", 0xffffff);
		DrawExtendString(
			drawPos_[0].x + 28,
			drawPos_[0].y + 29 - size,
			0.7, 1.0,
			"アイテム", 0xffffff);
		break;
	case MODE::WARP:
		int x = (OFFSET_X - POINT_SIZE) + ((player_.warp % 6) * OFFSET_SIZE);
		int y = (OFFSET_Y - POINT_SIZE) + ((player_.warp / 6) * OFFSET_SIZE);
		Color3 color;
		color.Color3Code(defultColor_);
		SetDrawBright(color.red, color.green, color.blue);
		DrawRotaGraph(x, y, 2.0, Deg2Rad(target_), image_["target"][0], true);
		DrawRotaGraph(x, y, 2.0, Deg2Rad(target_ + 60.0), image_["target"][0], true);
		DrawRotaGraph(x, y, 2.0, Deg2Rad(target_ - 60.0), image_["target"][0], true);
		DrawRotaGraph(x, y, 2.0, Deg2Rad(target_ - 120.0), image_["target"][0], true);
		DrawRotaGraph(x, y, 2.0, Deg2Rad(target_ + 120.0), image_["target"][0], true);
		DrawRotaGraph(x, y, 2.0, Deg2Rad(target_ + 180.0), image_["target"][0], true);
		DrawRotaGraph(x, y, 2.0, Deg2Rad(targetSenter_), image_["target"][1], true);
		SetDrawBright(255, 255, 255);
		break;
	}
}

void Player::DrawMoveLine(void)
{
	if (mode_ == MODE::MOVE && moveEnd_ == false)
	{
		SetDrawBright(color_.red, color_.green, color_.blue);
		DrawRotaGraph(
			drawPos_[0].x + 24,
			drawPos_[0].y - 30,
			0.5, 0.0,
			image_["count"][player_.move],
			true);
		SetDrawBright(255, 255, 255);
	}
	if (useMagnet_ == false)
	{
		if (useItem_ == ITEM::NONE)
		{
			for (int g = 0; g < 6; g++)
			{
				DrawLine(
					drawPos_[g].x,
					drawPos_[g].y,
					drawPos_[g + 1].x,
					drawPos_[g + 1].y,
					color_.GetColorCode(), 7);
			}

			SetDrawBlendMode(DX_BLENDMODE_ADD, alpha_);

			for (int g = 0; g < 6; g++)
			{
				DrawLine(
					drawPos_[g].x,
					drawPos_[g].y,
					drawPos_[g + 1].x,
					drawPos_[g + 1].y,
					0xffffff, 7);
			}

			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		}
		else
		{
			for (int g = 0; g < 6; g++)
			{
				DrawLine(
					drawPos_[g].x,
					drawPos_[g].y,
					drawPos_[g + 1].x,
					drawPos_[g + 1].y,
					0x999999, 7);
			}
		}
	}
}

void Player::DrawPlayer(bool over, int size)
{
	//動いているときにしかアニメーションをしない
	if (isMove_ == true)
	{
		SetAnim(4.0, 0);
	}

	SetDrawBright(alpha_, alpha_, alpha_);
	auto num = (static_cast<int>(player_.dir) * 3) + animNum_[animCnt_[0].second];
	if (over == false)
	{
		//影描画
		DrawGraph(
			drawPos_[0].x - PLAYER_HAFE_SIZE.x,
			drawPos_[0].y - PLAYER_HAFE_SIZE.y,
			image_["shadow"][num], true);
	}
	else
	{
		//影描画
		DrawGraph(
			drawPos_[0].x - PLAYER_HAFE_SIZE.x - size,
			drawPos_[0].y - PLAYER_HAFE_SIZE.y - size,
			image_["shadow"][num], true);
	}
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	if (over == false)
	{
		//プレイヤー描画
		DrawGraph(
			drawPos_[0].x - PLAYER_HAFE_SIZE.x, 
			drawPos_[0].y - PLAYER_HAFE_SIZE.y,
			image_["normal"][num], true);
	}
	else
	{
		//プレイヤー描画
		DrawGraph(
			drawPos_[0].x - PLAYER_HAFE_SIZE.x - size,
			drawPos_[0].y - PLAYER_HAFE_SIZE.y - size,
			image_["normal"][num], true);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	for (auto id : DIR())
	{
		if (canMove_[id].first == true)
		{
			DrawRotaGraph(
				drawPos_[0].x, 
				drawPos_[0].y,
				1.0, canMove_[id].second, 
				image_["dir"][0], true);
		}
	}
}

void Player::DrawInfo(int num)
{
	Color3 c;
	c.Color3Code(defultColor_);
	SetDrawBright(c.red, c.green, c.blue);
	DrawRotaGraph(32, 32 * num, 1.5, 0.0, image_["shadow"][animNum_[animCnt_[1].second]], true);
	SetDrawBright(255, 255, 255);
	DrawRotaGraph(32, 32 * num, 1.4, 0.0, image_["normal"][animNum_[animCnt_[1].second]], true);
}

bool Player::Release(void)
{
	for (const auto& name : fileName_["sound"])
	{
		lpMaterialMng.DeleteSoundHandle(name);
	}

	for (const auto& key : fileName_["image"])
	{
		lpMaterialMng.DeleteGraphHandle(key);
	}

	return true;
}

Player::Player(const char* nameG, const char* nameS)
{
	//サウンドのロード
	fileName_["sound"].resize(SOUND_CNT);
	fileName_["sound"] = {
		"sound/virtual.wav",
		"sound/syamu.wav",
		"sound/DB.wav",
		"sound/TNOK.wav",
		"sound/33-4.wav",
		"sound/kbtit.wav",
		"sound/frog.wav",
		"sound/ppppp.wav",
		"sound/blast.wav",
		"sound/bee.wav",
		"sound/pod.wav",
		"sound/end.wav",
		"sound/pppp.wav"
	};
	sound_.resize(SOUND_CNT);
	for (size_t t = 0; t < SOUND_CNT; t++)
	{
		sound_[t] = lpMaterialMng.LoadSoundHandle(fileName_["sound"][t].c_str());
	}

	//グラフィックのロード
	fileName_["image"].resize(6U);
	fileName_["image"] = {
		"image/player/dir.png",
		nameG,
		nameS,
		"image/player/target1.png",
		"image/player/target2.png",
		"image/count.png"
	};

	image_["dir"].resize(1U);
	image_["dir"][0] = lpMaterialMng.LoadGraphHandle(fileName_["image"][0]);
	size_t size = ANIM_SIZE * static_cast<size_t>(DIR::MAX);

	image_["target"].resize(2U);
	image_["target"][0] = lpMaterialMng.LoadGraphHandle(fileName_["image"][3]);
	image_["target"][1] = lpMaterialMng.LoadGraphHandle(fileName_["image"][4]);

	image_["normal"].resize(size);
	image_["normal"] = lpMaterialMng.LoadDivGraphic(fileName_["image"][1], { ANIM_SIZE, static_cast<int>(DIR::MAX) });

	image_["shadow"].resize(size);
	image_["shadow"] = lpMaterialMng.LoadDivGraphic(fileName_["image"][2], { ANIM_SIZE, static_cast<int>(DIR::MAX) });

	size = 10U;
	image_["count"].resize(size);
	image_["count"] = lpMaterialMng.LoadDivGraphic(fileName_["image"][5], NUM_CNT);
}

Player::~Player()
{

}

void Player::SetAnim(double delta, int num)
{
	animCnt_[num].first += (delta_ / 8.0);
	if (animCnt_[num].first > delta)
	{
		animCnt_[num].first = 0.0;
		animCnt_[num].second++;
	}
	if (animNum_.size() <= animCnt_[num].second)
	{
		animCnt_[num].second = 0;
	}
}

double Player::Deg2Rad(double deg)
{
	return DX_PI * (deg / 180.0);
}

void Player::SetPos(int point)
{
	player_.pos[0] = point;
	IsChange_ = false;
	for (int p = 1; p < 7; p++)
	{
		player_.pos[p] = player_.pos[0];
	}
}

void Player::SetItemLife(double life)
{
	itemLife_ = life;
}

void Player::ResetMove(void)
{
	useMagnet_ = false;
	lock_ = false;
	moveEnd_ = false;
	player_.move = 4;
	for (int p = 1; p < 7; p++)
	{
		player_.pos[p] = player_.pos[0];
	}
	useItem_ = ITEM::NONE;
	selectItem_ = ITEM::NONE;
	select_ = MODE::MOVE;
	mode_ = MODE::SELECT;
	SetSize(0);
}

Vector2 Player::GetDrawPos(void)
{
	return drawPos_[0];
}

ITEM Player::GetSelectItem(void)
{
	return selectItem_;
}

ITEM Player::GetUseItem(void)
{
	return useItem_;
}

double Player::GetAngle(void)
{
	return angle_;
}

void Player::SetSize(int num)
{
	for (auto& s : offsetSize_)
	{
		s = 1;
	}
	offsetSize_[num] = 5;
}

void Player::Move(void)
{
	for (int s = 6; s > 0; s--)
	{
		player_.pos[s] = player_.pos[s - 1];
	}
	player_.move--;
	for (int draw = 1; draw < 7; draw++)
	{
		drawPos_[draw].x = (OFFSET_X - POINT_SIZE) + ((player_.pos[draw] % 6) * OFFSET_SIZE);
		drawPos_[draw].y = (OFFSET_Y - POINT_SIZE) + ((player_.pos[draw] / 6) * OFFSET_SIZE);
	}
}

void Player::MoveEnd(void)
{
	if (fadeIn_ == true)
	{
		alpha_ += static_cast<int>(delta_ * 3.0);
	}
	else if (fadeOut_ == true)
	{
		alpha_ -= static_cast<int>(delta_ * 3.0);
	}
	if (alpha_ >= 255)
	{
		fadeIn_ = false;
		fadeOut_ = true;
		alpha_ = 255;
	}
	if (alpha_ <= 0)
	{
		fadeOut_ = false;
		alpha_ = 0;
	}
}

int Player::SetSurround(void)
{
	int minNum;
	//囲んだところの左上を取得
	minNum = min(player_.pos[0], min(player_.pos[1],min(player_.pos[2],min(player_.pos[3],player_.pos[4]))));
	//一列を6で割る
	int num = minNum - minNum / MAP_COUNT;
	return num;
}

void Player::ChackDir(void)
{
	if (moveEnd_ == false)
	{
		//移動可能な向き
		if (player_.move > 0)
		{
			if (player_.pos[0] % MAP_COUNT != 0)//左
			{
				canMove_[DIR::LIFT].first = true;
			}
			else
			{
				canMove_[DIR::LIFT].first = false;
			}

			if (player_.pos[0] + MAP_COUNT < MAP_COUNT * MAP_COUNT) //下
			{
				canMove_[DIR::DOWN].first = true;
			}
			else
			{
				canMove_[DIR::DOWN].first = false;
			}

			if (player_.pos[0] % MAP_COUNT != MAP_COUNT - 1)//右
			{
				canMove_[DIR::RIGHT].first = true;
			}
			else
			{
				canMove_[DIR::RIGHT].first = false;
			}

			if (player_.pos[0] - MAP_COUNT >= 0)	//上
			{
				canMove_[DIR::UP].first = true;
			}
			else
			{
				canMove_[DIR::UP].first = false;
			}
		}
		else
		{
			for (auto i : DIR())
			{
				canMove_[i].first = false;
			}
			if (player_.pos[1] == player_.pos[0] - 1)//左へ戻る
			{
				canMove_[DIR::LIFT].first = true;
			}
			if (player_.pos[1] == player_.pos[0] + 1)//右へ戻る
			{
				canMove_[DIR::RIGHT].first = true;
			}
			if (player_.pos[1] == player_.pos[0] - MAP_COUNT)//上へ戻る
			{
				canMove_[DIR::UP].first = true;
			}
			if (player_.pos[1] == player_.pos[0] + MAP_COUNT)//下へ戻る
			{
				canMove_[DIR::DOWN].first = true;
			}
		}
	}
	else
	{
		for (auto i : DIR())
		{
			canMove_[i].first = false;
		}
	}
}

bool Player::CheckHap(void)
{
	if (player_.pos[0] == player_.pos[4]  && surround_ != -1)
	{
		int hap = rand() % static_cast<int>(HAPPENING::MAX);
		if (!(surround_ == map_))
		{
			//Happening(static_cast<HAPPENING>(hap));
			Happening(HAPPENING::GET_ITEM);
		}
		else
		{
			return true;
		}
	}
	return false;
}

int Player::GetMap(void)
{
	IsHere_ = false;
	return map_;
}

int Player::GetPoint(void)
{
	return player_.pos[0];
}

Vector2 Player::GetDisVec2(void)
{
	Vector2 myPos = GetDrawPos();
	Vector2 pointPos;
	pointPos.x = OFFSET_X + ((map_ % 5) * OFFSET_SIZE) + POINT_SIZE / 2;
	pointPos.y = OFFSET_Y + ((map_ / 5) * OFFSET_SIZE) + POINT_SIZE / 2;
	Vector2 disVec2 = pointPos - myPos;
	return disVec2;	//目的地までの距離
}

void Player::Undo(void)
{
	for (int p = 1; p < 7; p++)
	{
		player_.pos[p - 1] = player_.pos[p];
	}
	player_.move++;
}

void Player::Candle(CANDLE candle)
{
	int itemNum = 4;
	switch (candle)
	{
	case CANDLE::COME_HERE:
		IsHere_ = true;
		lpTextPool.Generate("ライバルを引き寄せた", drawPos_[0], 300.0, defultColor_);
		break;
	case CANDLE::RANDOM_POS:
		player_.pos[0] = rand() % POINT_SIZE;
		for (int p = 1; p < 7; p++)
		{
			player_.pos[p] = player_.pos[0];
		}
		lpTextPool.Generate("ワープしちゃった！", drawPos_[0], 300.0, defultColor_);
		break;
	case CANDLE::NONE:
		lpTextPool.Generate("何も起こらなかった！", drawPos_[0], 300.0, defultColor_);
		break;
	case CANDLE::CHANGE_POS:
		lpTextPool.Generate("ライバルとばしょが入れ替わった！", drawPos_[0], 300.0, defultColor_);
		IsChange_ = true;
		break;
	case CANDLE::ITEM_GET:
		for (auto& item : player_.item)
		{
			if (item == ITEM::NONE)
			{
				item = static_cast<ITEM>(rand() % static_cast<int>(ITEM::NONE));
				itemNum = static_cast<int>(item);
				break;
			}
		}
		lpTextPool.Generate(item_name_[itemNum], drawPos_[0], 300.0, defultColor_);
		break;
	case CANDLE::NO_ITEM:
		for (auto& item : player_.item)
		{
			item = ITEM::NONE;
		}
		lpTextPool.Generate("アイテムが消えてしまった！", drawPos_[0], 300.0, defultColor_);
		break;
	case CANDLE::MOVE_PLAS:
		lpTextPool.Generate("移動量が6になった！", drawPos_[0], 300.0, defultColor_);
		player_.move = 6;
		break;
	case CANDLE::MOVE_MINUS:
		lpTextPool.Generate("移動量が1になった！", drawPos_[0], 300.0, defultColor_);
		player_.move = 1;
		break;
	}
}

bool Player::IsFull(void)
{
	return static_cast<bool>(fullItem_);
}

int Player::GetMove(void)
{
	return player_.move;
}

void Player::SetMode(MODE mode)
{
	mode_ = mode;
}

MODE Player::GetMode(void)
{
	return mode_;
}

Vector2 Player::GetInfoDrawPos(int num)
{
	Vector2 pos;
	pos.x = 70;
	pos.y = 32 * num;
	return pos;
}

int Player::GetSurround(void)
{
	return surround_;
}

void Player::Happening(HAPPENING eve)
{
	int itemNum = 4;
	switch (eve)
	{
	case Player::HAPPENING::RANDOM_POS:
		player_.pos[0] = rand() % (MAP_COUNT * MAP_COUNT);
		lpTextPool.Generate("ワープしちゃった！", drawPos_[0], 300.0, defultColor_);
		break;
	case Player::HAPPENING::RESET_POS:
		player_.pos[0] = respawn_;
		lpTextPool.Generate("最初の位置に戻された！", drawPos_[0], 300.0, defultColor_);
		break;
	case Player::HAPPENING::GET_ITEM:
		for (auto& item : player_.item)
		{
			if (item == ITEM::NONE)
			{
				item = static_cast<ITEM>(rand() % static_cast<int>(ITEM::NONE));
				itemNum = static_cast<int>(item);
				break;
			}
		}
		lpTextPool.Generate(item_name_[itemNum], drawPos_[0], 300.0, defultColor_);
		break;
	case Player::HAPPENING::CHANGE_POS:
		IsChange_ = true;
		lpTextPool.Generate("ライバルとばしょが入れ替わった！", drawPos_[0], 300.0, defultColor_);
		break;
	case Player::HAPPENING::CHANGE_MAP:
		map_ = rand() % POINT_SIZE;
		lpTextPool.Generate("お宝が別の場所に移動した！", drawPos_[0], 300.0, defultColor_);
		break;
	case Player::HAPPENING::NONE:
		lpTextPool.Generate("ここには何もなかったゾ！", drawPos_[0], 300.0, defultColor_);
		break;
	}
}