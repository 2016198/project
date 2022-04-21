#pragma once
#include <vector>
#include <array>
#include <string>
#include "Color3.h"

enum class SCENE_ID
{
	SELECT,
	CASH,
	ELEMONEY,
	MAX
};

class Ticket
{
public:
	Ticket();							//コンストラクタ
	~Ticket();							//デストラクタ

	virtual bool Init(void) = 0;		//初期化処理
	virtual void UpDate(void) = 0;		//更新処理
	virtual void Draw(void) = 0;		//描画処理

	SCENE_ID GetScene(void);			//シーンを入手
	void DrawBack(void);				//戻るボタン描画

protected:

	bool MouseOneInput(void);								//1フレームの入力
	bool HitBack(void);										//戻るボタンにふれたか

	const  std::array<std::string, 4U> BUY_TICKET = {		//購入するチケットの枚数
	"+1",
	"+10",
	"-1",
	"-10"
	};
	const char* MSG_BUY = "購入";					//購入の文字

	int width_;										//文字の横幅
	bool IsBuy_;									//購入したか
	std::vector<Color3> color_;						//カラーコード
	Color3 colorB_;									//カラーコード
	int ticketPrice_;								//切符の値段
	int ticketNum_;									//切符の枚数

	int x_, y_;										//マウスの座標
	std::array<bool, 2U> mouse_;					//マウスの入力

	SCENE_ID scene_;								//現在のシーン
};

