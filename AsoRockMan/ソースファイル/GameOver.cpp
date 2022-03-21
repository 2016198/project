#include "GameOver.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"

bool GameOver::Init(void)  //�C���X�^���X�̐�������
{
	mCounter = 0;
	if ((mImage = LoadGraph("Image/gameover.png")) == -1)
	{
		return false;
	}
	return true;
}

bool GameOver::UpDate(void)  //�C���X�^���X�̍X�V����
{
	mCounter++;
	return KeyTrgDown[KEY_SYS_START];
}

void GameOver::Draw(void)  //�C���X�^���X�̕`�揈��
{
	SetDrawScreen(DX_SCREEN_BACK);                  //�o�b�N�o�b�t�@�ɐݒ�
	ClsDrawScreen();                                //��ʏ���
	DrawBox(50, 50, 700, 440, GetColor(0, 255, 255), 1);
	DrawGraph((SCREEN_SIZE_X - GAME_OVER_SIZE_X) / 2, (SCREEN_SIZE_Y - GAME_OVER_SIZE_Y) / 2, mImage, true);
	if ((mCounter / 30) % 2 == 0)
	{
		DrawString(300, 370, "space : �^�C�g����ʂ�", GetColor(2, 2, 2));
		DrawString(300, 370, "\n\nEsc   :   �I���", GetColor(5, 5, 5));
	}
}

bool GameOver::Release(void)  //�C���X�^���X�̊J������
{
	DeleteGraph(mImage);
	return true;
}

bool GameOver::GameInit(void)
{
	mCounter = 0;
	return true;
}