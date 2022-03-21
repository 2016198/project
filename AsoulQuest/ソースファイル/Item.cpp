#include "Item.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "GameScene.h"

bool Item::Init(GameScene* parent)	//インスタンスの初期化
{
	mSize.x = 16;
	mSize.y = 16;
	mParent = parent;
	mAnimCnt = 0;
	mPos = { 0,0 };
	mAlive = false;
	mSizeOffset.x = mSize.x / 2;
	mSizeOffset.y = mSize.y / 2;
	return true;
}

void Item::UpDate(Vector2 pos)	//インスタンスの更新
{
	mOffset = pos;
	mAnimCnt++;
}

void Item::Draw(void)	//インスタンスの描画
{
	if (mAlive == true)
	{
		DrawGraph(mPos.x - mSizeOffset.x - mOffset.x, mPos.y - mSizeOffset.y - mOffset.y, mParent->mItemImage[3], true);
		DrawCircle(mPos.x - mOffset.x, mPos.y - mOffset.y, 9, GetColor(rand() % 256, rand() % 256, rand() % 256), false);
	}
}

bool Item::Release(void) //インスタンスの開放
{
	return true;
}

void Item::SetItem(Vector2 targetPos) //アイテムのセット
{
	mPos = targetPos;
	mAlive = true;
}

bool Item::IsAlive(void) //アイテムが出現してるかどうか
{
	return mAlive;
}

Vector2 Item::GetSize(void) //画像のサイズを返す
{
	return mSizeOffset;
}

Vector2 Item::GetPos(void)//座標を返す
{
	return mPos;
}

void Item::Destroy(void) //弾を消す
{
	mAlive = false;
}