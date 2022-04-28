//#pragma once
#include "GameScene.h"
#include "GameClearScene.h"
#include "TitleScene.h"

#define lpSceneManager SceneManager::GetInstance()	//シングルトーン

enum class SCENE_ID
{
	TITLE,
	GAME,
	CLEAR,
	MAX
};

class SceneManager
{
public:
	bool Init(void);			//初期化処理
	bool Run(void);				//実行処理
	bool Release(void);			//解放処理

	bool FadeInOut(SCENE_ID next);

	static SceneManager& GetInstance()	//シングルトーン
	{
		static SceneManager mSceneManger;
		return mSceneManger;
	}

private:
	SCENE_ID now;	//現在のシーン

	TitleScene mTitleScene;
	GameScene mGameScene;
	GameClearScene mClearScene;
	Stage mStage;

	int brightValue_;	//輝度値の格納領域
	bool fadeOut_;		//true:フェードアウト中
	bool fadeIn_;		//true:フェードイン中

	double count;

	//音楽格納用変数
	int title;
	int clear;
	int escapeSE;
	int notSafeKey;
	int solveSE;

	void SoundInit(void);			//サウンドのロード＆初期化
	void ReleaseSound(void);		//サウンドハンドルの開放
};