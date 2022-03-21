#include <DxLib.h>
#include "../../manager/MaterialManager.h"
#include "TextPool.h"

void TextPool::Init(void)
{
	font_ = lpMaterialMng.LoadFontHandle("font/font1.dft");

	for (int y = 0; y < pool_count_; y++)
	{
		textPool_.emplace_back(new TextData());
	}
}

void TextPool::Generate(std::string str, Vector2 pos, double lifeTime, unsigned int color)
{
	if (textPool_.size() > 0)
	{
		(*textPool_.begin())->Generate(str, pos, lifeTime, color);
		textList_.splice(textList_.end(), std::move(textPool_), textPool_.begin());
		//splice:Listの要素の移動※[移動先].splice([移動先のどこに移動するか],[std::move([移動元])],[移動させる要素番号],[いどうさせる要素番号の最後])
		//最小限にしかループしなくなる
	}
}

void TextPool::Draw(double delta)
{
	//表示時間が過ぎたら元に戻す
	for (std::list<TextData*>::iterator itr = textList_.begin(); itr != textList_.end();)
	{
		(*itr)->Draw(delta, font_);
		if (!(*itr)->IsAlive())
		{
			textPool_.splice(textPool_.end(), std::move(textList_), itr++);
			//itr++しないとitrが使用不可になる
			//moveで使用不可になるがitr++で次のitrが使用可能なので使うことができる
		}
		else
		{
			++itr;
			//++itrの方がitr++よりも処理が早い
		}
	}

}

void TextPool::Release(void)
{
	if (textList_.size() > 0)
	{
		textList_.erase(textList_.begin(), textList_.end());
	}

	if (textPool_.size() > 0)
	{
		textPool_.erase(textPool_.begin(), textPool_.end());
	}
}
