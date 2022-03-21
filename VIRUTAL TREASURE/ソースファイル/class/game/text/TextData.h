#pragma once
#include <string>
#include "../../Vector2.h"

class TextData
{
public:

	void Generate(std::string text, Vector2 pos, double life, unsigned int color);			//生成して使用処理
	void Draw(double delta, int fontID);													//描画処理

	TextData();			//コンストラクタ
	~TextData();		//デストラクタ

	bool IsAlive();		//表示されてる？

private:

	std::string text_;			//テキストデータ
	double life_ = -1.0;		//テキスト表示時間
	Vector2 pos_;				//座標
	unsigned int color_;		//色コード
};

