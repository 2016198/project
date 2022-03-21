#pragma once
#include "BaseScene.h"

class OptionScene :
    public BaseScene
{

public:
	OptionScene(INPUT_TYPE type, bool clear);	//コンストラクタ
	~OptionScene() override;		//デストラクタ

	bool Init(void) override;					//初期化処理
	SCENE_ID Update(double delta) override;		//更新処理
	int Draw(void) override;					//描画処理
	void Release(void) override;				//解放処理
	const int GetNum(void) override;			//値わたし
	const SCENE_ID GetScene(void) override;		//自分のシーンを渡す

private:
	void ImgMove(void);							//画像の移動処理
	bool CheckMoveEnd(void);					//画像の移動処理が終了したか

	bool zoom_[2];								//表示系の選択がされたか
	int optionScreen_;							//オプションのスクリーン
	int helpImage_;								//グラフィックハンドル
	const char* message_[2] = {					//表示する文字
		"ゲームパッド",
		"キーボード"};

	static constexpr int HALF_SCREEN_X = SCREEN_SIZE_X / 2;		//スクリーンサイズXの半分
	static constexpr int HALF_SCREEN_Y = SCREEN_SIZE_Y / 2;		//スクリーンサイズYの半分
	static constexpr int OFFSET = 100;							//文字をずらす値
	double size[2];												//スクリーンのサイズ
	double delta_;												//デルタタイム
	int imageOpt_;												//グラフィックハンドル
	bool clear_;												//チュートリアルモードを開放したか

	bool isSelect_;												//項目を選択したかどうか
	Color3 lineColor_;											//選択している枠の外線の色コード
	int selectOption_;											//オプションの選択
	int soundNum_;												//音量調整
	int sound_[2];												//サウンド
	void ZoomCommand(double delta);								//zoom処理
	void UpdateOption(void);									//オプションの更新
	void DrawOption(void);										//オプションの描画

	std::array<int, 3U> img_;									//グラフィックハンドル
	std::array<Vector2, 4U> offset_;							//各画像のオフセット
};

