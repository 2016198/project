#pragma once
#include <type_traits>
#include <array>
#include <map>

//定義の宣言
enum class INPUT_LIST			//入力管理情報
{
	//システム関連のキー情報
	START,
	SELECT,

	//マウス
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,

	//入力情報
	UP,
	DOWN,
	LEFT,
	RIGHT,
	A,
	B,

	MAX
};

enum class KEY
{
	//キーの状態
	NOW,				//今のフレーム
	OLD,				//1フレーム前
	TRG_DOWN,			//押した瞬間
	TRG_UP				//離した瞬間
};

enum class INPUT_TYPE	//入力情報のタイプ
{
	KEY,
	PAD
};

using InputList = std::map<INPUT_LIST, std::map<KEY, bool>>;

class BaseInput
{
public:
	BaseInput() {};										//コンストラクタ
	virtual ~BaseInput() {};							//デストラクタ	
	virtual void SetKeyList(INPUT_TYPE type) = 0;		//キーの状態を変更

	void CheckInputList(void);							//キーの状態をチェック
	void CheckTrgList(void);							//キーの状態をチェック

	const InputList& GetCntData(void)					//キーの情報を与える
	{
		return input_;
	}

private:

protected:
	InputList input_ = {};
};

static INPUT_LIST begin(INPUT_LIST) { return INPUT_LIST::START; };
static INPUT_LIST end(INPUT_LIST) { return INPUT_LIST::MAX; };
static INPUT_LIST operator++(INPUT_LIST& state)
{
	state = static_cast<INPUT_LIST>(std::underlying_type<INPUT_LIST>::type(state) + 1);
	return state;
};
static INPUT_LIST operator*(const INPUT_LIST& state) { return state; };

