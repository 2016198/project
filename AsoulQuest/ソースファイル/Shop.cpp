#include "Shop.h"
#include "_debug/_DebugConOut.h"
#include"_debug/_DebugDispOut.h"
#include "KeyCheck.h"
#include "DxLib.h"
#include "GameScene.h"

bool Shop::Init(GameScene* parent, int ScreenSizeX, int ScreenSizeY)//インスタンスの初期化
{
	if ((mImage = LoadGraph("image/tensyu.png")) == -1)
	{
		return false;
	}
	if ((mShopImage = LoadGraph("image/shop.png")) == -1)
	{
		return false;
	}
	mParent = parent;
	if ((mArrowImage = LoadGraph("image/arrow.png")) == -1)
	{
		return false;
	}
	mNoBuy = false;
	mBuy = false;
	mBack = false;
	mPosX = 0;
	mScreenSizeX = ScreenSizeX;
	mScreenSizeY = ScreenSizeY;
	mCnt = 300;
	return true;
}

bool Shop::UpDate(void)//インスタンスの更新
{
	mBack = false;
	if (mPosX < 400)
	{
		mPosX += 10;
	}
	if (KeyTrgDown[KEY_P1_LEFT] || KeyTrgDown[KEY_P1_RIGHT] || KeyTrgDown[KEY_SYS_START])
	{
		mPush = true;
		mPosX = 0;
	}
	if (KeyTrgDown[KEY_P1_LEFT])
	{
		mNoBuy = false;
		mBuy = false;
		mCnt--;
	}
	if (KeyTrgDown[KEY_P1_RIGHT])
	{
		mNoBuy = false;
		mBuy = false;
		mCnt++;
	}
	if (KeyTrgDown[KEY_SYS_START])
	{
		switch (mCnt % 4)
		{
		case 0://3way
			if (mParent->mCoin >= 1000)
			{
				PlaySoundMem(mParent->mSeBuy, DX_PLAYTYPE_BACK);
				mParent->mCoin -= 1000;
				mParent->BuyItem(ITEM_TYPE::WAY);
				mBuy = true;
			}
			else
			{
				mNoBuy = true;
			}
			break;
		case 1://回復
			if (mParent->mCoin >= 600)
			{
				PlaySoundMem(mParent->mSeBuy, DX_PLAYTYPE_BACK);
				mParent->mCoin -= 600;
				mParent->BuyItem(ITEM_TYPE::HEART);
				mBuy = true;
			}
			else
			{
				mNoBuy = true;
			}
			break;
		case 2://盾
			if (mParent->mCoin >= 900)
			{
				PlaySoundMem(mParent->mSeBuy, DX_PLAYTYPE_BACK);
				mParent->mCoin -= 900;
				mParent->BuyItem(ITEM_TYPE::SHIELD);
				mBuy = true;
			}
			else
			{
				mNoBuy = true;
			}
			break;
		case 3://back
			PlaySoundMem(mParent->mSeDoor, DX_PLAYTYPE_BACK);
			mBack = true;
			break;
		default:
			break;
		}
	}
	return mBack;
}

void Shop::Draw(void)//インスタンスの描画
{
	DrawExtendGraph(0, 0, 300, mScreenSizeY / 2, mImage, true);
	DrawBox(50, mScreenSizeY - 200, mScreenSizeX - 50, mScreenSizeY - 50, GetColor(100, 100, 100), true);
	if (mNoBuy == true)
	{
		DrawString(70, mScreenSizeY - 180, mSerihu[1], GetColor(255, 255, 255));
	}
	else if (mBuy == true)
	{
		DrawString(70, mScreenSizeY - 180, mSerihu[6], GetColor(255, 255, 255));
	}
	else
	{
		if (mPush == false)
		{
			DrawString(70, mScreenSizeY - 180, mSerihu[0], GetColor(255, 255, 255));
		}
		else
		{
			DrawString(70, mScreenSizeY - 180, mSerihu[mCnt % 4 + 2], GetColor(255, 255, 255));
		}
	}
	DrawBox(50 + mPosX, mScreenSizeY - 200, mScreenSizeX - 50, mScreenSizeY - 50, GetColor(100, 100, 100), true);
	switch (mCnt % 4)
	{
	case 0:
		DrawRotaGraph(440, 120, 10.0f, 0.0f, mParent->mItemImage[0], true);
		DrawString(410, 210, "1 0 0 0", GetColor(255, 255, 255));
		break;
	case 1:
		DrawRotaGraph(440, 120, 10.0f, 0.0f, mParent->mItemImage[1], true);
		DrawString(410, 210, "6 0 0", GetColor(255, 255, 255));
		break;
	case 2:
		DrawRotaGraph(440, 120, 10.0f, 0.0f, mParent->mItemImage[2], true);
		DrawString(410, 210, "9 0 0", GetColor(255, 255, 255));
		break;
	case 3:
		DrawRotaGraph(440, 120, 10.0f, 0.0f, mArrowImage, true);
		break;
	default:
		break;
	}
}

bool Shop::Release(void)//インスタンスの解放
{
	DeleteGraph(mArrowImage);
	DeleteGraph(mShopImage);
	DeleteGraph(mImage);
	return true;
}

bool Shop::GameInit(GameScene* parent)//ゲームの初期化
{
	mPush = false;
	mNoBuy = false;
	mBuy = false;
	mBack = false;
	mPosX = 0;
	mParent = parent;
	mCnt = 300;
	return true;
}