#include "SceneManager.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"

bool SceneManager::Init(int ScreenSizeX, int ScreenSizeY)  //インスタンスの生成
{
	//各種初期化処理
	mScreenSizeX = ScreenSizeX;
	mScreenSizeY = ScreenSizeY;
	mSceneID = SCENE_ID::TITLE_SCENE;
	mColor = 0;
	mFadeOut = false;
	mFadeIn = true;
	//インスタンスの初期化
	if (!mGamescene.Init(mScreenSizeX, mScreenSizeY, this)) return false;
	if (!mTitlescene.Init(mScreenSizeX, mScreenSizeY, this)) return false;
	if (!mGameover.Init(mScreenSizeX, mScreenSizeY)) return false;
	//if (!gameclear.Init()) return false;
	return true;
}
 
void SceneManager::Run(void)   //インスタンスの実行処理
{
	//if (gamescene.GameOver())
	//{
	//	sceneID = GAME_OVER_SCENE;
	//	if (!gamescene.GameInit()) return -1;           //ゲームオーバー後の処理
	//	if (!titlescene.GameInit()) return -1;
	//}
	switch (mSceneID)
	{
	case  SCENE_ID::TITLE_SCENE:
		if (ScreenEffect(SCENE_ID::GAME_SCENE))
		{
			if (mTitlescene.UpDate() && mFadeIn == false && mFadeOut == false)                        //タイトルシーン更新処理
			{
				mColor = 255;
				mGameover.GameInit();
				mFadeOut = true;
			}
		}
		mTitlescene.Draw();                              //タイトルシーン描画処理
		break;
	case  SCENE_ID::GAME_SCENE:
		if (ScreenEffect(SCENE_ID::GAME_OVER_SCENE))
		{
			if (mGamescene.UpDate() && mFadeIn == false && mFadeOut == false)                         //ゲームシーン更新処理
			{
				mColor = 255;
				mTitlescene.GameInit();
				mFadeOut = true;
			}
		}
		mGamescene.Draw();                  //ゲームシーン描画処理
		break;
	case  SCENE_ID::GAME_OVER_SCENE:
		if (ScreenEffect(SCENE_ID::TITLE_SCENE))
		{
			if (mGameover.UpDate() && mFadeIn == false && mFadeOut == false)                          //ゲームオーバーシーン更新処理
			{
				mColor = 255;
				mGamescene.GameInit();
				mFadeOut = true;
			}
		}
		mGameover.Draw(mGamescene.GetScore());                                //ゲームオーバーシーン描画処理
		break;
		//case GAME_CLEAR_SCENE:
		//	gameclear.UpDate();
		//	gameclear.Draw(gamescene.Score());
		//	if (gameclear.SceneChenge())
		//	{
		//		gameclear.Reset();
		//		if (!gamescene.GameInit()) return -1;           //ゲームクリアー後の処理
		//		if (!titlescene.GameInit()) return -1;
		//		sceneID = TITLE_SCENE;
		//	}
		//	break;
	default:
		break;
	}
}

bool SceneManager::Release(void)  //インスタンスの開放処理
{
	//if (!gameclear.Release()) return false;
	if (!mGameover.Release()) return false;
	if (!mTitlescene.Release())return false;
	if (!mGamescene.Release()) return false;
	return true;
}

bool SceneManager::ScreenEffect(SCENE_ID nextSceneID)   //画面切り替え時にエフェクトを行う
{                                                       //エフェクト実行中：戻り値 = true
	SetDrawBright(mColor, mColor, mColor);              //引数  nextSceneID：次のシーンＩＤ
	if (mFadeOut == false && mFadeIn == false)
	{
		return true;
	}
	if (mFadeIn == true)
	{
		mColor += 5;
	}
	if (mFadeOut == true)
	{
		mColor -= 5;
	}
	if (mColor <= 0)
	{
		mFadeOut = false;
		mFadeIn = true;
		mSceneID = nextSceneID;
	}
	if (mColor >= 255)
	{
		mFadeIn = false;
	}
	return false;
}

bool SceneManager::ScoreReset(void)
{
	if (!mGamescene.ScoreSet()) return false;
	return true;
}
