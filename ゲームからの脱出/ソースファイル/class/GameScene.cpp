#include <DxLib.h>			
#include "KeyCheck.h"
#include "GameScene.h"

bool GameScene::Init(void)
{
	KeyInit();	//キー情報管理関数の初期化

	//各シーンの初期化
	if (!mStage.Init())
	{
		return false;
	}
	if (!mPlayer.Init(this))
	{
		return false;
	}
	if (!mSlide.Init())
	{
		return false;
	}
	if (!mLight.Init())
	{
		return false;
	}
	if (!mBucket.Init())
	{
		return false;
	}
	if (!mSafe.Init())
	{
		return false;
	}
	if (!mTips.Init())
	{
		return false;
	}

	//フラグの初期化
	escapeFlag = false;

	mSflag.slide = false;
	mSflag.light = false;
	mSflag.bucket = false;
	mSflag.safe = false;

	flag.slide = false;
	flag.light = false;
	flag.bucket = false;
	flag.safe = false;

	count = 0;

	safeCheck = false;

	return true;

}
bool GameScene::Update(void)
{
	CheckKeyList();
	mStage.Update();
	mPlayer.Update();

	//スライドパズル
	if (mSflag.slide)
	{
		mSlide.Update();
	}

	//ライトブロック
	if (mSflag.light)
	{
		mLight.Update();
	}

	//バケツゲーム
	if (mSflag.bucket)
	{
		mBucket.Update();
	}

	//金庫
	if (mSflag.safe)
	{
		mSafe.Update();
	}

	//金庫を開くためのヒント
	mTips.Update();

	//クリア条件が整ったらクリア
	if (mPlayer.ClearFlag() == true && escapeFlag == true)
	{
		return false;
	}

	return true;
}
void GameScene::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);					//描画する画面を裏の画面に設定
	ClearDrawScreen();								//描画する画面の内容を消去
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);	//描画する画面のブレンドモードの設定

	mStage.PassDraw();

	if (!mPlayer.back)
	{
		mPlayer.Draw();
	}

	mStage.NotPassDraw();

	if (!mSlide.ReturnFlag())
	{
		mStage.EventDraw({ 32 * 3,32 * 2 });
	}

	if (!mLight.ReturnFlag())
	{
		mStage.EventDraw({ 32*13,32*9 });
	}

	if (!mBucket.ReturnFlag())
	{
		mStage.EventDraw({ 32*16,32*2 });
	}

	if (!mSafe.ReturnFlag() && mTips.MatchFlag())
	{
		mStage.EventDraw({ 32*14,32 });
	}

	if (!mPlayer.back)
	{
		mPlayer.Draw();
	}

	if (mSafe.ReturnFlag())
	{
		escapeFlag = true;
		mStage.EscapeDraw({ 32 * 8 + 16,32 * 5 - 8 });
	}

	//スライドパズル
	if (mSflag.slide)
	{
		if (!mSlide.Back())
		{
			mSlide.Draw();
		}
		else
		{
			mSflag.slide = false;
		}
	}

	//ライトブロック
	if (mSflag.light)
	{
		if (!mLight.Back())
		{
			mLight.Draw();
		}
		else
		{
			mSflag.light = false;
		}
	}
	
	//バケツゲーム
	if (mSflag.bucket)
	{
		if (!mBucket.Back())
		{
			mBucket.Draw();
		}
		else
		{
			mSflag.bucket = false;
		}

	}

	//金庫
	if (mSflag.safe)
	{
		DrawBox(0, 0, 640, 480, 0x000000, true);//画面の点滅防止

		if (!mSafe.Back())
		{
			mSafe.Draw();
		}
		else 
		{
			if (mTips.ReturnFlag())
			{
				mSflag.safe = false;
			}
		}
	}

	//パスワードのヒント描画
	if (mSlide.ReturnFlag() && mSflag.slide == false)
	{
		mTips.SlideDraw();
	}

	if (mLight.ReturnFlag() && mSflag.light == false)
	{
		mTips.LightDraw();
	}

	if (mTips.MatchFlag()&&!mSflag.bucket)
	{
		mTips.MatchDraw();
	}

	//バケツゲームで表示させない
	if (!mSflag.bucket)	
	{
		//パスワード入手後に表示
		mTips.InventoryDraw();	
	}

	//鍵を取ってないと開けられなくする為の処理
	if (!mBucket.ReturnFlag() && mPlayer.CheckSafe())
	{
		safeCheck = true;
		DrawString(0, 0, "鍵がない", 0xffffff);
	}

	//ステージデバッグ用のグリッド表示
	//for (int y = 0; y < 14; y++)
	//{
	//	for (int x = 0; x < 19; x++)
	//	{
	//		DrawLine(32+x * 32, 0, 32+x * 32, 480, 0x00ff00);
	//		DrawLine(0, 32+y*32, 640, 32+y*32, 0x00ff00);
	//	}
	//}
}
bool GameScene::Release(void)
{
	mStage.Release();
	mPlayer.Release();
	return true;

}

int GameScene::GetEvent(Vector2 pos)
{
	int mapChipID;	//マップチップIDを格納する変数
	mapChipID = mStage.GetEventChip(pos);	//イベントを発生させるマップチップを格納する

	//プレイヤー側で調べて、且つそのパズルをクリアしていなかったら開始する
	if (mPlayer.CheckSlide() && !mSlide.ReturnFlag())
	{
		mSflag.slide = true;//スライドパズル
	}

	if (mPlayer.CheckLight() && !mLight.ReturnFlag())
	{
		mSflag.light = true;//ライトブロック
	}

	if (mPlayer.CheckBucket() && !mBucket.ReturnFlag())
	{
		mSflag.bucket = true;//バケツゲーム
	}

	if (mPlayer.CheckSafe() && !mSafe.ReturnFlag())
	{
		//バケツゲームクリア済み且つ、全ヒント収集済みで開始できる
		if (mBucket.ReturnFlag() && mTips.MatchFlag())
		{
			mSflag.safe = true;//金庫
		}
	}

	//各パズルクリア後の処理
	if (CheckHitKey(KEY_INPUT_SPACE) && mSlide.ReturnFlag())
	{
		mSflag.slide = false;
		flag.light = true;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) && mLight.ReturnFlag())
	{
		mSflag.light = false;
		flag.light = true;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) && mBucket.ReturnFlag())
	{
		mSflag.bucket = false;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) && mSafe.ReturnFlag())
	{
		mSflag.safe = false;
		escapeFlag = true;
	}
	return 	mapChipID;
}

int GameScene::GetCol(Vector2 pos)
{
	int mapChipID;	//マップチップIDを格納する変数
	mapChipID = mStage.GetMapChip(pos);

	return mapChipID;
}

bool GameScene::SafeCheck(void)
{
	if (safeCheck)
	{
		safeCheck = false;
		return true;
	}
	return false;
}

bool GameScene::ClearCheck(void)
{
	if (flag.slide)
	{
		flag.slide = false;
		return true;
	}
	if (flag.light)
	{
		flag.light = false;
		return true;
	}
	if (flag.bucket)
	{
		flag.bucket = false;
		return true;
	}
	if (flag.safe)
	{
		flag.safe = false;
		return true;
	}
	return false;
}
