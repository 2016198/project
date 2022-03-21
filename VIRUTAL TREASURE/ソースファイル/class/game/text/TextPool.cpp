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
		//splice:List�̗v�f�̈ړ���[�ړ���].splice([�ړ���̂ǂ��Ɉړ����邩],[std::move([�ړ���])],[�ړ�������v�f�ԍ�],[���ǂ�������v�f�ԍ��̍Ō�])
		//�ŏ����ɂ������[�v���Ȃ��Ȃ�
	}
}

void TextPool::Draw(double delta)
{
	//�\�����Ԃ��߂����猳�ɖ߂�
	for (std::list<TextData*>::iterator itr = textList_.begin(); itr != textList_.end();)
	{
		(*itr)->Draw(delta, font_);
		if (!(*itr)->IsAlive())
		{
			textPool_.splice(textPool_.end(), std::move(textList_), itr++);
			//itr++���Ȃ���itr���g�p�s�ɂȂ�
			//move�Ŏg�p�s�ɂȂ邪itr++�Ŏ���itr���g�p�\�Ȃ̂Ŏg�����Ƃ��ł���
		}
		else
		{
			++itr;
			//++itr�̕���itr++��������������
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
