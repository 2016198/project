#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "KeyCheck.h"
#include "SceneManager.h"

bool TitleScene::Init(int ScreenSizeX, int ScreenSizeY, SceneManager* parent)   //�C���X�^���X�̐�������
{
	mParent = parent;
	mScreenSizeX = ScreenSizeX;
	mScreenSizeY = ScreenSizeY;
	if ((mImage = LoadGraph("image/title.bmp")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	mCounter = 0;
	return true;
}

bool TitleScene::UpDate(void)   //�C���X�^���X�̍X�V����
{
	if (KeyTrgDown[KEY_SYS_RESET] && mReset == false)
	{
		mParent->ScoreReset();
		mReset = true;
	}
	mCounter++;
	return KeyTrgDown[KEY_SYS_START];
}

void TitleScene::Draw(void)      //�C���X�^���X�̕`�揈��
{
	SetDrawScreen(DX_SCREEN_BACK);                  //�o�b�N�o�b�t�@�ɐݒ�
	ClsDrawScreen();                                //��ʏ���
	DrawBox(50, 50, 600, 440, GetColor(255, 0, 255), 1);
	DrawGraph((mScreenSizeX - TITLE_SIZE_X) / 2, (mScreenSizeY - TITLE_SIZE_Y) / 2, mImage, 0);
	if ((mCounter / 30) % 2 == 0)
	{
		DrawString(250, 370, "space : �X�^�[�g", GetColor(255, 255, 255));
		DrawString(250, 370, "\n\nEsc   :   �I���", GetColor(255, 255, 255));
	}
	DrawString(210, 100, "z�L�[�Ńn�C�X�R�A�̃��Z�b�g",GetColor(0,0,0));
	if (mReset == true)
	{
		DrawString(200, 370, "�n�C�X�R�A�����Z�b�g���܂����B", GetColor(255, 255, 0));
	}
}

bool TitleScene::Release(void)   //�C���X�^���X�̊J������
{
	DeleteGraph(mImage);
	return true;
}

bool TitleScene::GameInit(void)
{
	mReset = false;
	mCounter = 0;
	return true;
}