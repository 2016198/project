#pragma once
#include <memory>
#include <list>
#include "../Vector2.h"
#include "../Color3.h"
#include "BaseScene.h"
#include "../title/bug.h"

class TitleScene:
	public BaseScene
{	

public:
	TitleScene(INPUT_TYPE type);	//コンストラクタ
	~TitleScene() override;			//デストラクタ

	bool Init(void) override;					//初期化処理
	SCENE_ID Update(double delta) override;		//更新処理
	int Draw(void) override;					//描画処理
	void Release(void) override;				//解放処理
	const int GetNum(void) override;			//値わたし
	const SCENE_ID GetScene(void) override;		//自分のシーンを渡す

private:

	void ImgMove(void);							//画像の移動処理
	bool CheckMoveEnd(void);					//画像の移動処理が終了したか
	void SpeechBalloon(double num);				//セリフの拡大縮小

	void MessageDraw(void);						//選択した時のメッセージ描画

	static constexpr size_t IMG_COUNT = 6U;		//titleで使う背景以外の画像の数
	static constexpr int OFFSET = 95;			//文字をずらす

	static constexpr int GEAR_SIZE_X = 76;						//歯車画像のサイズX
	static constexpr int GEAR_SIZE_Y = 76;						//歯車画像のサイズY
	static constexpr int GEAR_SIZE_HALF_X = GEAR_SIZE_X / 2;	//歯車画像の半分サイズX
	static constexpr int GEAR_SIZE_HALF_Y = GEAR_SIZE_Y / 2;	//歯車画像の半分サイズY

	static constexpr Vector2 PATTERN_COUNT = { 4, 2 };			//芝模様の数
	static constexpr int PATTERN_TYPE = 8;						//芝模様の合計値
	static constexpr size_t PATTERN_NUM = 100U;					//芝模様の生成数

	const char* imgFile_[IMG_COUNT] =	//ファイルパス
	{
		"image/title/single.png",
		"image/title/double.png",
		"image/title/title.png",
		"image/title/gear.png",
		"image/title/end.png",
		"image/title/gameend.png"
	};

	static constexpr double BUG_TIME = 50.0;		//虫たちが出てくる時間
	static constexpr size_t BUG_COUNT = 20U;		//最大の虫の数

	std::list<std::unique_ptr<Bug>> bugPool_;		//虫の予備のポインタ
	std::list<std::unique_ptr<Bug>> bugList_;		//虫の使用するポインタ

	std::array<Vector2, IMG_COUNT> pos_;			//各画像の座標
	std::array<Vector2, IMG_COUNT - 1U> offset_;	//四角の目的地からの距離
	int offsetFont_;								//フォントを中心よせにする変数
	std::vector<int> titleImg_;						//グラフィックハンドル(選択項目系)
	Color3 lineColor_;								//外枠の色コード
	int sound_[2];									//サウンドハンドル
	bool isSelect_;									//選択したか
	int alpha_;										//アルファ値(タイトル)
	double scale_;									//セリフの大きさ
	Vector2 speechSize_;							//セリフ画像の大きさ

	int msgScreen_;									//メッセージの表示スクリーン
	int msgGrassImg_;								//グラフィックハンドル
	std::vector<int> msgPatternImg_;				//グラフィックハンドル
	std::vector<Vector2> patternPos_;				//模様の座標
	double zoom_;									//表示の大きさ
};

