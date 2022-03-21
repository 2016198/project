#pragma once
#include <memory>
#include <list>
#include "TextData.h"

#define lpTextPool TextPool::GetInstance()//シングルトーン

class TextPool
{
public:
	static TextPool& GetInstance()	//インスタンスの入手
	{
		static TextPool s_Instance;
		return s_Instance;
	}

	std::list<TextData*> textList_;		//使う分の要素
	std::list<TextData*> textPool_;		//予備の要素

	void Init(void);					//初期化処理
	void Generate(std::string str,
		Vector2 pos,
		double lifeTime,
		unsigned int color);			//Poolから使用分だけもって来る
	void Draw(double delta);			//描画処理
	void Release(void);					//解放処理

	int font_ = -1;						//フォントハンドル

private:

	static const int pool_count_ = 20;	//文字貯蔵庫の数
};
