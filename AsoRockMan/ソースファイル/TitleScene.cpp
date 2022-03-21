#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "KeyCheck.h"

bool TitleScene::Init(void)   //�C���X�^���X�̐�������
{
	if ((mImage = LoadGraph("Image/Title.png")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	if ((mStartImage = LoadGraph("Image/hitstartkey.png")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	mCounter = 0;
	return true;
}

bool TitleScene::UpDate(void)   //�C���X�^���X�̍X�V����
{
	mCounter++;
	return KeyTrgDown[KEY_SYS_START];
}

void TitleScene::Draw(void)      //�C���X�^���X�̕`�揈��
{
	SetDrawScreen(DX_SCREEN_BACK);                  //�o�b�N�o�b�t�@�ɐݒ�
	ClsDrawScreen();                                //��ʏ���
	DrawGraph(0, 0, mImage, true);
	if ((mCounter / 30) % 2 == 0)
	{
		DrawGraph(210, 400, mStartImage, true);
	}
}

bool TitleScene::Release(void)   //�C���X�^���X�̊J������
{
	DeleteGraph(mImage);
	DeleteGraph(mStartImage);
	return true;
}

bool TitleScene::GameInit(void)
{
	mCounter = 0;
	return true;
}