#include "Item.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "GameScene.h"

bool Item::Init(GameScene* parent)	//�C���X�^���X�̏�����
{
	mSize.x = 16;
	mSize.y = 16;
	mParent = parent;
	mAnimCnt = 0;
	mPos = { 0,0 };
	mAlive = false;
	mSizeOffset.x = mSize.x / 2;
	mSizeOffset.y = mSize.y / 2;
	return true;
}

void Item::UpDate(Vector2 pos)	//�C���X�^���X�̍X�V
{
	mOffset = pos;
	mAnimCnt++;
}

void Item::Draw(void)	//�C���X�^���X�̕`��
{
	if (mAlive == true)
	{
		DrawGraph(mPos.x - mSizeOffset.x - mOffset.x, mPos.y - mSizeOffset.y - mOffset.y, mParent->mItemImage[3], true);
		DrawCircle(mPos.x - mOffset.x, mPos.y - mOffset.y, 9, GetColor(rand() % 256, rand() % 256, rand() % 256), false);
	}
}

bool Item::Release(void) //�C���X�^���X�̊J��
{
	return true;
}

void Item::SetItem(Vector2 targetPos) //�A�C�e���̃Z�b�g
{
	mPos = targetPos;
	mAlive = true;
}

bool Item::IsAlive(void) //�A�C�e�����o�����Ă邩�ǂ���
{
	return mAlive;
}

Vector2 Item::GetSize(void) //�摜�̃T�C�Y��Ԃ�
{
	return mSizeOffset;
}

Vector2 Item::GetPos(void)//���W��Ԃ�
{
	return mPos;
}

void Item::Destroy(void) //�e������
{
	mAlive = false;
}