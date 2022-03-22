#include <DxLib.h>
#include "Player.h"
#include "State.h"
#include "Bullet.h"
#include "../common/input/KeyInput.h"
#include "../common/input/PadInput.h"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

Player::Player()
{

}

Player::Player(CntType cntType, Vector2 pos)
{
	Init(cntType, pos);
}

Player::~Player()
{

}

bool Player::Init(CntType cntType, Vector2 pos)
{
	lpListMng.LoadAnime("./tmx/list.tmx", Obj_ID);
	state_ = "idle";
	turn_ = false;
	jump_ = false;
	pos_ = pos;
	if (cntType == CntType::Key)
	{
		controller_ = std::make_unique<KeyInput>();
	}
	if (cntType == CntType::Pad)
	{
		controller_ = std::make_unique<PadInput>();
	}
	lpListMng.SetAnime(Obj_ID, state_, &animeData_);
	collisionSize = lpListMng.GetColSize(Obj_ID);
	rapidxml::file<> moduleFileName = "./tmx/playerModuleList.tmx";
	stateVec_ = moduleFileName.vecData();
	stateDoc_.parse<0>(stateVec_.data());
	stateNode_ = stateDoc_.first_node("modulelist");

	moduleNode_ = new ModuleNode();

	return true;
}

void Player::UpDate(ColList colList)
{
	bPos_ = pos_;
	bState_ = state_;
	colList_ = colList;
	//colList_ = colList;
	if (!controller_)
	{
		return;
	}
	controller_ = controller_->UpDate(std::move(controller_));
	cntData_ = controller_->GetCntData();
	cmd = controller_->cmd;
	//TRACE("%s\n", cmd.c_str());

	for (auto node = stateNode_->first_node();
		node != nullptr;
		node = node->next_sibling())
	{
		moduleNode_->operator()(this, node);
	}

	if (state_ != bState_)
	{
		lpListMng.SetAnime(Obj_ID, state_, &animeData_);
	}
	lpListMng.UpDateAnime(Obj_ID, state_, &animeData_);

	if (cmd == "邪剣夜")
	{
		bulletList_.emplace_back(std::make_unique<Bullet>(pos_, turn_));
	}

	if (bulletList_.size())
	{
		for (const auto& bullet : bulletList_)
		{
			bullet->UpDate();
		}
	}
	/*for (auto col : colList)
	{
		_dbgDrawBox(
			col.first.x_ - 1, col.first.y_ - 1,
			col.first.x_ + col.second.x_ + 1, col.first.y_ + col.second.y_ + 1,
			0xff00ff, 0);
	}
	_dbgDrawCircle(pos_.x_ + collisionSize.x_, (pos_.y_ + collisionSize.y_ * 2) - 5, 4, 0xffffff, true);
	_dbgDrawBox(pos_.x_, pos_.y_, pos_.x_ + (collisionSize.x_ * 2), pos_.y_ + (collisionSize.y_ * 2), 0xffffff, true);
	_dbgDrawFormatString(0, 30, 0xffffff, "%d", pos_.y_ + collisionSize.y_ * 2);*/
	//speed_.y_ += gravity;
	//double yobiPos = (double)(pos_.y_);

	//ラムダ式 [キャプチャー部](引数部){式本体};
	//checkNum_ = [&](int num) {return num % 2 == 0; };

	////auto data = cntData[InputID::Left][static_cast<int>(Trg::Now)];
	//if (cntData[InputID::Left][static_cast<int>(Trg::Now)])
	//{
	//	if (checkMove(Vector2{ -((int)(speed_.x_) + collisionSize.x_), 0 }))
	//	{
	//		turn_ = true;
	//		state_[0] = "run";
	//		pos_.x_ -= (int)(speed_.x_);
	//	}
	//}
	//if (cntData[InputID::Right][static_cast<int>(Trg::Now)])
	//{
	//	if (checkMove(Vector2{ (int)(speed_.x_) + collisionSize.x_, 0}))
	//	{
	//		turn_ = false;
	//		state_[0] = "run";
	//		pos_.x_ += (int)(speed_.x_);
	//	}
	//}
	//if (cntData[InputID::ButtonD][static_cast<int>(Trg::Now)] && !cntData[InputID::ButtonD][static_cast<int>(Trg::Old)])
	//{
	//	speed_.y_ = -10.10;
	//}

	//if (speed_.y_ >= 0.0)
	//{
	//	if (checkMove(Vector2{ 0, (int)(speed_.y_) + collisionSize.y_ }))
	//	{
	//		yobiPos += (int)(speed_.y_);
	//		pos_.y_ = (int)yobiPos;
	//	}
	//	else
	//	{
	//		speed_.y_ = 0.0;
	//	}
	//}
	//if (speed_.y_ < 0.0)
	//{
	//	if (checkMove(Vector2{ 0, -((int)(speed_.y_) + collisionSize.y_) }))
	//	{
	//		yobiPos += (int)(speed_.y_);
	//		pos_.y_ = (int)yobiPos;
	//	}
	//	else
	//	{
	//		speed_.y_ = 3.0;
	//	}
	//}

	/*if (state_[0] != state_[1])
	{
		lpListMng.SetAnime(Obj_ID, state_[0], &animeData_);
	}*/
}

void Player::Draw()
{
	//DrawOval(pos_.x_ + Senter.x_, pos_.y_ + Senter.y_, 14, 24, 0xffffff, 1);
	//DrawExtendGraph(pos_.x_, pos_.y_, pos_.x_ + Size.x_ * 2, pos_.y_ + Size.y_ * 2, lpImageMng.GetID(Obj_ID + state_[0])[(*animeData_.animItr_)[GraphHD]], true);
	DrawRotaGraph(pos_.x_ + collisionSize.x_, pos_.y_ + collisionSize.y_ - 5, animeData_.exRate, 0.0, lpImageMng.GetID(Obj_ID + state_)[(*animeData_.animItr_)[GraphHD]], true, turn_);
	if (bulletList_.size())
	{
		for (const auto& bullet : bulletList_)
		{
			bullet->Draw();
		}
	}
	//DrawCircle(pos_.x_, pos_.y_, 6, 0xffff00);
}
