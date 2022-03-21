#pragma once
#include <vector>
#include <string>
#include "../Input/BaseInput.h"
#include "../../tmx/TmxObj.h"

enum class TEXT_MODE
{
	OPERATION,			//操作モード
	MANUAL,				//説明モード
	CHANGE				//画面の切り替え
};

class Text
{

public:

	Text();			//コンストラスタ
	~Text();		//デストラクタ

	bool Init(void);													//初期化処理
	void SetText(std::string key);										//テキストをセットする
	TEXT_MODE Update(const InputList input1, const InputList input2, bool progress);	//更新処理
	void Draw(double delta);											//描画処理
	void Release(void);													//解放処理

	std::vector<std::string>::iterator GetChildItr(void);				//子のイテレーターを入手
	std::vector<std::vector<std::string>>::iterator GetParentItr(void);	//親のイテレーターを入手

private:
	int sound_;							//サウンドハンドル

	std::array<InputList, 2U> input_;	//入力情報
	int pos_;							//スライド座標
	int font_;							//フォントハンドル
	TextMap text_;						//フォント

	std::vector<std::string>::iterator childItr_;				//子のイテレーター
	std::vector<std::vector<std::string>>::iterator parentItr_;	//親のイテレーター
	std::string type_;											//説明するモード
};