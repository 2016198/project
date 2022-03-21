#pragma once
#include <array>
#include <vector>
#include <memory>
#include <type_traits>
#include <string>
#include "../Input/BaseInput.h"

enum class SCENE_ID		//ゲームシーン
{
	CONTINUE,		//続ける
	RESULT,			//リザルトシーン
	TITLE,			//タイトルシーン
	TUTORIAL,		//チュートリアルシーン
	GAME_ONE,		//ゲームシーン：一人
	GAME_TWO,		//ゲームシーン：二人
	OPTION,			//オプションシーン
	END,			//おしまい
	MAX
};

class BaseScene
{
public:
	BaseScene(INPUT_TYPE type);			//コンストラクタ
	virtual ~BaseScene() {};			//デストラクタ

	virtual bool Init(void) = 0;					//初期化処理
	virtual SCENE_ID Update(double delta) = 0;		//更新処理
	virtual int Draw(void) = 0;						//描画処理
	virtual void Release(void) = 0;					//解放処理
	virtual const int GetNum(void) = 0;				//値わたし
	virtual const SCENE_ID GetScene(void) = 0;		//前回のシーンを渡す

private:

protected:
	std::array<std::unique_ptr<BaseInput>, 2U> ptr_;	//ポインタ
	std::array<InputList, 2U> input_;					//入力情報

	static constexpr int BOX_SIZE = 100;		//ボックスのサイズ
	static constexpr int OFFSET_POS_X = 170;	//オフセット座標

	//スクリーンサイズ
	static constexpr int SCREEN_SIZE_X = 640;
	static constexpr int SCREEN_SIZE_Y = 480;

	INPUT_TYPE inputType_;					//入力情報

	int screen_ = 0;						//スクリーンハンドル
	SCENE_ID selectNum_;					//どこのシーンへ移動するか
	std::vector<unsigned int> color_;		//色コード
	int select_ = 0;						//シーン移動の選択カーソル

	int image_;								//グラフィックハンドル(背景)
	int font_;								//フォントハンドル
};

static SCENE_ID operator++(SCENE_ID& state)
{
	state = static_cast<SCENE_ID>(std::underlying_type<SCENE_ID>::type(state) + 1);
	return state;
};

static SCENE_ID operator--(SCENE_ID& state)
{
	state = static_cast<SCENE_ID>(std::underlying_type<SCENE_ID>::type(state) - 1);
	return state;
}

static bool operator<(const SCENE_ID stateA, const SCENE_ID stateB)
{
	int a = std::underlying_type<SCENE_ID>::type(stateA);
	int b = std::underlying_type<SCENE_ID>::type(stateB);

	return a < b;
}

static bool operator>(const SCENE_ID stateA, const SCENE_ID stateB)
{
	int a = std::underlying_type<SCENE_ID>::type(stateA);
	int b = std::underlying_type<SCENE_ID>::type(stateB);

	return a > b;
}

