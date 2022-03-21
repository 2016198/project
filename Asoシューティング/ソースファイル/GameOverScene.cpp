#include "GameOverScene.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool GameOverScene::Init(void)//����������
{
	if ((image = LoadGraph("image/gameover.png")) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	PosX = SCREEN_SIZE_X / 2;
	PosY = 0;
	en = PAI / 180;
	counter = 0;
	return true;
}

void GameOverScene::UpDate(void)//�X�V����
{
	counter++;
}

void GameOverScene::Draw(void)//�`�揈��
{
	DrawGraph((SCREEN_SIZE_X - TITLE_SIZE_X) / 2, (SCREEN_SIZE_Y - TITLE_SIZE_Y) / 2, image, true);
	if ((counter / 50) % 2 == 0)
	{
		SetFontSize(30);
		DrawString(150, 0, "��߂�   Esc�L�[", GetColor(0, 255, 255));
		DrawString(150, 0, "\n������   Enter�L�[", GetColor(25, 255, 0));
	}
}

bool GameOverScene::Release(void)//�������
{
	DeleteGraph(image);
	return true;
}