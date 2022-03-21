//#pragma once
#include "GameScene.h"
#include "TitleScene.h"
#include "GameOver.h"
//#include "GameClear.h"

enum class SCENE_ID {
	TITLE_SCENE,           //0：タイトルシーン
	GAME_SCENE,            //1：ゲームシーン
	GAME_OVER_SCENE,       //2：ゲームオーバーシーン
	GAME_CLEAR_SCENE,      //3：ゲームクリアーシーン
	MAX_SCENE              //4：シーンの最大値
};

class SceneManager
{
private:                           //メンバー変数
	int mScreenSizeX;              //画面のXサイズ
	int mScreenSizeY;              //画面のYサイズ
	int mColor;                    //色の明るさ
	bool mFadeOut;                 //true：fadeOut中
	bool mFadeIn;                  //true：fadeIn中
	SCENE_ID mSceneID;             //シーンの宣伝
	                               //インスタンスの生成
	GameScene mGamescene;
	TitleScene mTitlescene;
	GameOver mGameover;
	//GameClear gameclear;
	//メンバー関数(シーンマネージャーだけが使える)
	bool ScreenEffect(SCENE_ID nextSceneID);      //画面切り替え時にエフェクトを行う

public:                                                       //メンバー関数
	bool ScoreReset(void);								      //スコアのリセット
	int mHighScore;		                                      //ハイスコア
	bool Init(int ScreenSizeX, int ScreenSizeY);              //インスタンスの生成時処理
	void Run(void);                                           //インスタンスの実行処理
	bool Release(void);                                       //インスタンスの開放処理
};