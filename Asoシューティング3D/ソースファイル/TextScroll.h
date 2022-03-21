#pragma once
#include <string>
#include <vector>
#include <map>
#include <DxLib.h>

class SceneManager;

class TextScroll
{

public:

	static constexpr int NUM_X_IMAGE = 10;
	static constexpr int NUM_Y_IMAGE = 6;
	static constexpr int NUM_IMAGE = NUM_X_IMAGE * NUM_Y_IMAGE;

	static constexpr int CHIP_SIZE = 32;

	enum class TYPE
	{
		TITLE,
		ENDLE
	};

	struct MsgInfo
	{
		VECTOR pos;
		std::vector<int> messages;	//要素番号
	};

	TextScroll(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	SceneManager* mSceneManager;

	//画像
	int mImages[NUM_IMAGE];

	//再生するテキストスクロール
	TYPE mType;

	//文字を発見したらロックする
	bool mFinded;

	//テキスト管理
	std::map<TYPE, std::vector<MsgInfo>> mTextMap;

	//テキストのスクロール処理
	float mScroll;

	//stringの文字列のを画像配列の要素番号の変換
	TextScroll::MsgInfo MakeMsgInfo(std::string msg, int mapCount);
};

