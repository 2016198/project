#pragma once
#include "BaseScene.h"
class ResultScene : 
	public BaseScene
{

public:
	ResultScene(INPUT_TYPE type, const int num, const SCENE_ID beforeScene);	//コンストラクタ
	~ResultScene() override;													//デストラクタ

	bool Init(void) override;					//初期化処理
	SCENE_ID Update(double delta) override;		//更新処理
	int Draw(void) override;					//描画処理
	void Release(void) override;				//解放処理
	const int GetNum(void) override;			//値わたし
	const SCENE_ID GetScene(void) override;		//自分のシーンを渡す

private:
	int winPlayer_;								//勝利したプレイヤーの番号
	SCENE_ID beforeScene_;						//前のゲームシーン
	const char* str_[2] =						//表示するフォント君
	{ 
		"もう一度やる" ,
		"TitleScene"
	};
	int offsetFont_;							//フォントのオフセット
};

