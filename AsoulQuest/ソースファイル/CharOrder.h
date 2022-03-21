#pragma once

//キャラクターの種類
enum class CHAR_TYPE
{
	PLAYER,
	ENEMY
};

class CharOrder
{
public:						//メンバー変数
	CHAR_TYPE mCharType;	//キャラクターの種類
	int mPosBottom;			//キャラクターの足元座標
	int mCharIndex;			//キャラクターの添え字
};
