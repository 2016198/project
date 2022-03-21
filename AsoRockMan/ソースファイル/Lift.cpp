#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include "Lift.h"

bool Lift::Init(void)//インスタンスの初期化
{
	mAnimCount = 0;
	mPos = Vector2(110, 120);
	mMoveSpeed = LIFT_MAX_SPEED;
	mAlive = false;
	return true;
}

void Lift::UpDate(void)//インスタンスの更新
{
	//リフトが表示されていたらtrueを返す
	if (mAnimCount > 0)
	{
		mAlive = true;
	}
	else
	{
		mAlive = false;
	}
	//mAlive = true;
	//リフトの上下運動
	if (mPos.y < 120)
	{
		mMoveSpeed = LIFT_MAX_SPEED;
	}
	else
	{
		if (mPos.y > 300)
		{
			mMoveSpeed = -LIFT_MAX_SPEED;
		}
	}
	if (CheckHitKey(KEY_INPUT_0))
	{
		mAnimCount = LIFT_ALIVE_TIME;
	}
	mAnimCount--;
	mPos.y += mMoveSpeed;
}

void Lift::Draw(void)//インスタンスの描画
{
	if (mAnimCount > 0)
	{
		DrawGraph(mPos.x - LIFT_SIZE_X / 2, mPos.y, mImage[static_cast<int>(LIST_STYLE::YES)], true);
	}
	else
	{
		DrawGraph(mPos.x - LIFT_SIZE_X / 2, mPos.y, mImage[static_cast<int>(LIST_STYLE::NO)], true);
	}
	
	//DrawFormatString(0, 0, GetColor(0, 0, 0), "\n%d %d", mPos.x, mPos.y);
}

bool Lift::Release(void)//インスタンスの開放
{
	DeleteGraph(mImage[static_cast<int>(LIST_STYLE::YES)]);
	DeleteGraph(mImage[static_cast<int>(LIST_STYLE::NO)]);
	return true;
}

bool Lift::IsAlive(void)//リフトが表示されているか
{
	return mAlive;
}

Vector2 Lift::GetPos(void)//座標を返す。
{
	return mPos;
}

Lift::Lift(void)//コンストラスタ
{
	LoadDivGraph("Image/Lift.png",
		static_cast<int>(LIST_STYLE::MAX),
		1,
		static_cast<int>(LIST_STYLE::MAX),
		LIFT_SIZE_X,
		LIFT_SIZE_Y,
		&mImage[0]);
}

Lift::~Lift(void)//デストラスタ
{

}
