#pragma once
#include <memory>
#include "../Vector2.h"
#include "BaseScene.h"

#define lpSceneMng SceneManager::GetInstance()	//シングルトーン

class SceneManager
{
public:
	static SceneManager& GetInstance()			//インスタンスの入手
	{
		static SceneManager s_Instance;
		return s_Instance;
	}

	bool Init(void);		//初期化処理
	void Run(void);			//実行処理
	void Release(void);		//解放処理

private:

	static constexpr double deltaTime = 500.0;		//フェイドの長さ
	double delta_ = deltaTime;						//フェイド用の変数
	static constexpr int fadeSpeed_ = 3;			//フェイドの速さ
	bool fadeIn_ = false;							//フェードイン
	bool fadeOut_ = false;							//フェードアウト
	bool gameEnd_ = false;							//ゲームおしまい

	std::unique_ptr<BaseScene> uniqueScene_;	//シーンのユニークポインタ

	SCENE_ID nextScene_;						//次のシーン
	int image_;									//グラフィックハンドル
	double angle_;								//画像の角度
	double num_;								//回転用変数
	bool clear_;								//チュートリアルモードをクリアしたかどうか

	void FadeCommand(SCENE_ID nextScene, double chor);	//fadeの実行

	//スクリーンサイズ
	static constexpr int SCREEN_SIZE_X = 640;
	static constexpr int SCREEN_SIZE_Y = 480;

	//スクリーンID
	int screen_;

	//シーン切り替えの効果音
	int sound_;									//効果音ハンドル

	//エフェクト系
	Vector2 mousePos_[2];						//マウスの座標
	int effect_[2];								//エフェクトハンドル：１=ノーマル；２=再生中
	double animCnt;								//アニメーションリセット変数

	//自分以外のシ－ンに値を渡す変数
	int sceneNum_;								//次のシーンに渡す値
	SCENE_ID sceneID_;							//次のシーンのID
	INPUT_TYPE inputType_;						//入力の種類

	//フォントハンドル
	std::string fontFile_[5] = {			//フォントのファイルパス
		"font/font1.dft",
		"font/font2.dft",
		"font/font3.dft",
		"font/font4.dft",
		"font/font5.dft"
	};
};

