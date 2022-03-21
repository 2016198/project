#include "GameOver.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"

bool GameOver::Init(int ScreenSizeX, int ScreenSizeY)  //�C���X�^���X�̐�������
{
	mScreenSizeX = ScreenSizeX;
	mScreenSizeY = ScreenSizeY;
	mCounter = 0;
	if ((mImage = LoadGraph("image/gameover.png")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	if ((LoadDivGraph("image/bakuha.bmp", 3, 3, 1, 24, 32, &mPlayer[0])) == -1)
	{
		return false;
	}
	if ((mSe = LoadSoundMem("sound/gameover.wav")) == -1)
	{
		return false;
	}
	return true;
}

bool GameOver::UpDate(void)  //�C���X�^���X�̍X�V����
{
	return KeyTrgDown[KEY_SYS_START];
}

void GameOver::Draw(int score)  //�C���X�^���X�̕`�揈��
{
	mCounter++;
	if (mCounter == 1)
	{
		PlaySoundMem(mSe, DX_PLAYTYPE_BACK);
	}
	if (mInput == false)
	{
		mScore = score;
		mInput = true;
	}
	SetDrawScreen(DX_SCREEN_BACK);                  //�o�b�N�o�b�t�@�ɐݒ�
	ClsDrawScreen();                                //��ʏ���
	DrawBox(50, 50, 600, 440, GetColor(0, 255, 255), 1);
	DrawGraph((mScreenSizeX - GAME_OVER_SIZE_X) / 2, (mScreenSizeY - GAME_OVER_SIZE_Y) / 2, mImage, true);
	DrawFormatString(100, 100, GetColor(0, 0, 255), "���Ȃ��̃X�R�A  =  %d", mScore);
	DrawGraph(318, 350, mPlayer[mCounter / 15 % 3], true);
	if ((mCounter / 30) % 2 == 0)
	{
		DrawString(250, 400, "Hit-----SpaceKey", GetColor(255, 255, 0));
	}
}

bool GameOver::Release(void)  //�C���X�^���X�̊J������
{
	DeleteSoundMem(mSe);
	DeleteGraph(mImage);
	DeleteGraph(mPlayer[0]);
	DeleteGraph(mPlayer[1]);
	DeleteGraph(mPlayer[2]);
	return true;
}

bool GameOver::GameInit(void)
{
	mInput = false;
	mCounter = 0;
	return true;
}