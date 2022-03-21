#include "Bg2.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool Bg2::Init(void)//����������
{
	PosY1 = 0;
	PosY2 = -BG_SIZE_Y;
	Speed = 2;
	Image = LoadGraph("image/haikei.png");
	if (Image == -1)
	{
		TRACE("�w�i�̓ǂݍ��݂Ɏ��s���܂����B");
		return false;
	}
	return true;
}
void Bg2::UpDate(void)//�X�V����
{
	//TRACE("Y=%d  ", playerPosY);  //�f�o�b�O�p
	//TRACE("X=%d\n", playerPosX);  //�f�o�b�O�p

	PosY1 += Speed;      //�w�i�̈ړ�
	PosY2 += Speed;      //�w�i�̈ړ�

	if (PosY1 >= SCREEN_SIZE_Y)
	{
		PosY1 -= BG_SIZE_Y * 2;
		TRACE("�w�i1��߂��܂����B\n");
	}

	if (PosY2 >= SCREEN_SIZE_Y)
	{
		PosY2 -= BG_SIZE_Y * 2;
		TRACE("�w�i2��߂��܂����B\n");
	}
}

void Bg2::Draw(void)//�`�揈��
{
	DrawGraph(0, PosY1, Image, true);														         //�w�i�P
	DrawGraph(0, PosY2, Image, true);			                                                     //�w�i�Q
}

bool Bg2::Release(void)//�������
{
	DeleteGraph(Image);
	return true;
}

bool Bg2::GameInit(void)//�Q�[���I�[�o�[�̏���������
{
	PosY1 = 0;
	PosY2 = -BG_SIZE_Y;
	Speed = 2;

	return true;
}