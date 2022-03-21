#include "DxLib.h"
#include "Blast2.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool Blast2::Init(void)//����������
{
	if (LoadDivGraph("image/blast.png",
		BLAST_COUNT_X * BLAST_COUNT_Y,
		BLAST_COUNT_X,
		BLAST_COUNT_Y,
		BLAST_SIZE_X,
		BLAST_SIZE_Y,
		&Image[0]) == -1)
	{
		TRACE("�ǂݍ��ݎ��s�B");
		return false;
	}
	PosX = 0;
	PosY = 0;
	No = 0;
	Alive = false;
	return true;
}

void Blast2::UpDate(void)//�X�V����
{
	if (Alive == true)    //�����A�j���[�V�����̏���
	{
		No++;
		if (No / 2 > (BLAST_COUNT_X * BLAST_COUNT_Y) - 1)
		{
			Alive = false;              //�A�j���[�V�����̏I���
		}
	}
}

void Blast2::Setup(Vector2 Pos)//���W�̎󂯎�菈��
{
	PosX = Pos.x;
	PosY = Pos.y;
	No = 0;
	Alive = true;
}

void Blast2::Draw(void)//�`�揈��
{
	if (Alive == true)
	{
		DrawGraph(PosX - 16, PosY - 16, Image[No / 2], true);     //�����̃A�j���[�V�����̃X�^�[�g�ݒ菈��
	}
}

bool Blast2::GetAlive(void)//�\������Ă邩�̃`�F�b�N
{
	return Alive;
}

bool Blast2::Release(void)//�������
{
	for (int g = 0; g < BLAST_COUNT_X * BLAST_COUNT_Y; g++)
	{
		DeleteGraph(Image[g]);
	}
	return true;
}

bool Blast2::GameInit(void)//�Q�[���I�[�o�[�̏���������
{
	PosX = 0;
	PosY = 0;
	No = 0;
	Alive = false;
	return true;
}