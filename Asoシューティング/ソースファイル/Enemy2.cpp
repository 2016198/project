#include "Enemy2.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool Enemy2::Init(void)//����������
{
	//�O���t�B�b�N�̓ǂݍ���
	Image = LoadGraph("image/enemy.png");
	if (Image == -1)
	{                               //����@=
		TRACE("�G�摜�̓ǂݍ��݂Ɏ��s���܂����B");
		return false;
	}
	shotFlag = false;
	Pos.x = rand() % (SCREEN_SIZE_X - ENEMY_SIZE_X);
	Pos.y = -ENEMY_SIZE_Y;
	Pos.X = Pos.x;
	Pos.Y = Pos.y;
	Speed = 3;
	gamecounter = 0;
	Alive = true;
	TRACE("�G�̈ʒu��������");
	TRACE("���W%d\n", Pos.x);
	return true;
}

void Enemy2::UpDate(bool bossMode, bool bossHunt)//�X�V����
{
	gamecounter++;
	Pos.X = Pos.x;
	Pos.Y = Pos.y;
	if (bossMode == false && bossHunt == false)  //boss���o�ꂵ�ĂȂ��Ƃ�
	{
		if (Alive == true)
		{
			Pos.y = Speed + Pos.y;      //�G�̈ړ�����
			if (gamecounter % 100 == 0) //��P�D�T�b���Ƃɒe������
			{
				shotFlag = true;
			}
			else
			{
				shotFlag = false;
			}
		}
		else
		{
			Pos.x = rand() % (SCREEN_SIZE_X - ENEMY_SIZE_X);
			Pos.y = -ENEMY_SIZE_Y;
			Alive = true;
			TRACE("�G�̈ʒu��������");
			TRACE("���W%d\n", Pos.x);
		}
		if (Pos.y >= SCREEN_SIZE_Y)
		{
			Pos.y = 0 - ENEMY_SIZE_Y;
			Pos.x = rand() % (SCREEN_SIZE_X - ENEMY_SIZE_X);                //rand()����
			TRACE("�G�̈ʒu��������");
			TRACE("���W%d\n", Pos.x);
		}
	}
	else
	{
		if (Alive == true)
		{
			Pos.y = Speed + Pos.y;        //�G�̈ړ�����
			if (gamecounter % 100 == 0) //��P�D�T�b���Ƃɒe������
			{
				shotFlag = true;
			}
			else
			{
				shotFlag = false;
			}
		}
	}
}

void Enemy2::Draw(void)//�`�揈��
{
	if (Alive == true)
	{
		DrawGraph(Pos.x, Pos.y, Image, true);                     //�`��
	}
}

//�G�̍��W��Ԃ�
Vector2 Enemy2::GetPos(void)
{
	return Pos;
}

void Enemy2::DeleteEnemy(void)//�G������
{
	Alive = false;
}

//�G�������Ă邩
bool Enemy2::GetAlive(void)
{
	return Alive;
}

bool Enemy2::IsShot(void)//�e��������Ă邩�ǂ����̃`�F�b�N
{
	return shotFlag;
}

bool Enemy2::Release(void)//�������
{
	DeleteGraph(Image);
	return true;
}

bool Enemy2::GameInit(void)//�Q�[���I�[�o�[�̏���������
{
	gamecounter = 0;
	shotFlag = false;
	Pos.x = rand() % (SCREEN_SIZE_X - ENEMY_SIZE_X);
	Pos.y = -ENEMY_SIZE_Y;
	Speed = 3;
	Alive = true;
	TRACE("�G�̈ʒu��������");
	TRACE("���W%d\n", Pos.x);
	return true;
}