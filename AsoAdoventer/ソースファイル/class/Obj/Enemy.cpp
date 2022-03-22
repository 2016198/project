#include <DxLib.h>
#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(CntType cntType, Vector2 pos)
{
	Init(cntType, pos);
}

Enemy::~Enemy()
{

}

bool Enemy::Init(CntType cntType, Vector2 pos)
{
	//lpListMng.LoadAnime("./tmx/list.tmx", Obj_ID);
	state_ = "move";
	turn_ = false;
	pos_ = pos;
	return true;
}

void Enemy::UpDate(ColList colList)
{
	colList_ = colList;

	auto checkMove = [&](Vector2 moveVec) {
		Raycast::Ray ray = { pos_ + Vector2{3,3}, moveVec };
		//_dbgDrawLine(ray.point.x_, ray.point.y_, ray.point.x_ + ray.vec.x_, ray.point.y_ + ray.vec.y_,0xff00ff);
		for (auto col : colList_)
		{
			/*_dbgDrawBox(
				col.first.x_ - 1, col.first.y_ - 1,
				col.first.x_ + col.second.x_ + 1, col.first.y_ + col.second.y_ + 1,
				0xff00ff, 0);*/
			if (raycast_.CheckCollision(ray, col))//ìÆÇ©Ç»Ç¢(ëŒè€ï®Ç‘Ç¬Ç©Ç¡ÇƒÇ¢ÇÈ)ÇÃÇ≈fasle
			{
				return false;
			}
		}
		return true;
	};

	
	if (checkMove(Vector2{ -(3 + collisionSize.x_), 0 }))
	{
		pos_.x_ -= 3;
	}
}

void Enemy::Draw()
{
	//DrawCircle(pos_.x_, pos_.y_, 10, 0xffffff);
}
