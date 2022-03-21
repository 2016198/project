#include <DxLib.h>
#include "../../manager/MaterialManager.h"
#include "../text/TextPool.h"
#include "ItemBoxPool.h"

void ItemBoxPool::Init(void)
{
	std::vector<int> imageVec = lpMaterialMng.LoadDivGraphic(
		"image/item/itembox.png",
		{ 1, ItemBox::ANIM_COUNT });

	sound_ = lpMaterialMng.LoadSoundHandle("sound/pod.wav");
	for (int y = 0; y < pool_count_; y++)
	{
		itemBoxPool_.emplace_back(new ItemBox(imageVec));
	}
}

void ItemBoxPool::Generate(int pos, ITEM type, unsigned int color)
{
	if (itemBoxPool_.size() > 0)
	{
		(*itemBoxPool_.begin())->Generate(pos, type, color);
		itemBoxList_.splice(itemBoxList_.end(), std::move(itemBoxPool_), itemBoxPool_.begin());
		//splice:List�̗v�f�̈ړ���[�ړ���].splice([�ړ���̂ǂ��Ɉړ����邩],[std::move([�ړ���])],[�ړ�������v�f�ԍ�],[���ǂ�������v�f�ԍ��̍Ō�])
		//�ŏ����ɂ������[�v���Ȃ��Ȃ�
	}
}

void ItemBoxPool::Get(Vector2 pos1, Vector2 pos2, bool full1, bool full2)
{
	int who;
	int color;
	//�\�����Ԃ��߂����猳�ɖ߂�
	for (std::list<ItemBox*>::iterator itr = itemBoxList_.begin(); itr != itemBoxList_.end();)
	{
		if ((*itr)->IsGetItem(pos1, pos2) != 0)
		{
			PlaySoundMem(sound_, DX_PLAYTYPE_BACK);
			who = (*itr)->IsGetItem(pos1, pos2);
			if (who == 1)
			{
				color = 0x0000ff;
			}

			else
			{
				color = 0xff0000;
			}

			lpTextPool.Generate(item_name[static_cast<int>((*itr)->GetItemInfo())], (*itr)->GetDrawPos(), 300.0, color);
			itemBoxPool_.splice(itemBoxPool_.end(), std::move(itemBoxList_), itr++);
			//itr++���Ȃ���itr���g�p�s�ɂȂ�
			//move�Ŏg�p�s�ɂȂ邪itr++�Ŏ���itr���g�p�\�Ȃ̂Ŏg�����Ƃ��ł���
		}
		else
		{
			++itr;
			//++itr�̕���itr++��������������
			//����������?
		}
	}

}

void ItemBoxPool::Get(Vector2 pos, bool full)
{
	//�\�����Ԃ��߂����猳�ɖ߂�
	for (std::list<ItemBox*>::iterator itr = itemBoxList_.begin(); itr != itemBoxList_.end();)
	{
		if ((*itr)->IsGetItem(pos) != 0)
		{
			PlaySoundMem(sound_, DX_PLAYTYPE_BACK);
			lpTextPool.Generate(item_name[static_cast<int>((*itr)->GetItemInfo())], (*itr)->GetDrawPos(), 300.0, 0xff00ff);
			itemBoxPool_.splice(itemBoxPool_.end(), std::move(itemBoxList_), itr++);
			//itr++���Ȃ���itr���g�p�s�ɂȂ�
			//move�Ŏg�p�s�ɂȂ邪itr++�Ŏ���itr���g�p�\�Ȃ̂Ŏg�����Ƃ��ł���
		}
		else
		{
			++itr;
			//++itr�̕���itr++��������������
			//����������?
		}
	}

}

void ItemBoxPool::Draw(double delta)
{
	for (const auto item : itemBoxList_)
	{
		item->Draw(delta);
	}
}

void ItemBoxPool::Release(void)
{
	if (itemBoxList_.size() > 0)
	{
		itemBoxList_.erase(itemBoxList_.begin(), itemBoxList_.end());
	}

	if (itemBoxPool_.size() > 0)
	{
		itemBoxPool_.erase(itemBoxPool_.begin(), itemBoxPool_.end());
	}
	lpMaterialMng.DeleteGraphHandle("image/item/itembox.png");
	lpMaterialMng.DeleteSoundHandle("sound/pod.wav");
}

