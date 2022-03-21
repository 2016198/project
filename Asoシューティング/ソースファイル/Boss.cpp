#include "Boss.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool Boss::Init(void)                     //�C���X�^���X�̐������̏���
{
	life = 100;
	Pos.x = (SCREEN_SIZE_X - BOSS_SIZE_X) / 2;
	Pos.y = -BOSS_SIZE_Y - 10;
	Alive = false;
	gamecounter = 0;
	stayTime = 180;
	huntTime = 100;
	shotFlag = false;
	hunt = false;
	bossLR = rand() % 2;
	if (bossLR == 0)
	{
		xSpeed = 4;
		ySpeed = (rand() % 5) + 1;
	}
	else
	{
		xSpeed = -4;
		ySpeed = (rand() % 5) + 1;
	}
	if (LoadDivGraph("image/boss.png", 3, 3, 1, 64, 64, &Image[0]) == -1)
	{
		TRACE("�ǂݍ��ݎ��s");
		return false;
	}
	return true;
}

void Boss::UpDate(void)                   //�C���X�^���X�̍X�V����
{
	if (Alive == true)
	{
		if (Pos.y < 0)
		{
			Pos.y += 1;
		}
		if (stayTime == 0)
		{
			gamecounter++;
			Pos.y -= ySpeed;
			Pos.x += xSpeed;
			if (Pos.x < 0)
			{
				xSpeed = 4;
			}
			if (Pos.x > SCREEN_SIZE_X - BOSS_SIZE_X)
			{
				xSpeed = -4;
			}
			if (Pos.y < 0)
			{
				ySpeed = -ySpeed;
			}
			if (Pos.y > SCREEN_SIZE_Y - BOSS_SIZE_X)
			{
				ySpeed = -ySpeed;
			}
			if (gamecounter == 180)
			{
				gamecounter = 0;
				shotFlag = true;
			}
			else
			{
				shotFlag = false;
			}
		}
		else
		{
			stayTime--;
		}
	}
}

void Boss::Draw(void)                     //�C���X�^���X�̕`�揈��
{
	if (Alive == true)
	{
		if (life >= 50)
		{
			DrawGraph(Pos.x, Pos.y, Image[0], true);
		}
		else if (life >= 20)
		{
			DrawGraph(Pos.x, Pos.y, Image[1], true);
		}
		else
		{
			DrawGraph(Pos.x, Pos.y, Image[2], true);
		}
			
		if (!stayTime == 0)
		{
			DrawCircle(Pos.x + BOSS_SIZE_X / 2, Pos.y + BOSS_SIZE_Y / 2, 50, GetColor(100, 100, 100), 0);
		}
	}
}

bool Boss::Release(void)                  //�C���X�^���X�̊J������
{
	for (int o = 0; o < 3; o++)
	{
		DeleteGraph(Image[o]);
	}
	return true;
}

void Boss::InBoss(void)                  //Boss��o�ꂳ����
{
	Alive = true;
}

void Boss::DeleteBoss(void)              //boss������
{
	Alive = false;
	hunt = true;
}

bool Boss::IsHunt(void)                  //boss���|���ꂽ��
{
	return hunt;
}

bool Boss::IsHit(void)                   //boss�̓�����������
{
	life--;
	if (life <= 0)       //���C�t��0�̂Ȃ�����
	{
		return true;
	}
	return false;
}

bool Boss::Death(void)
{
	if (hunt == true)
	{
		if (huntTime > 0)
		{
			huntTime--;
		}
		else
		{
			return true;
		}
	}
	return false;
}

int Boss::IsStay(void)
{
	return stayTime;
}

bool Boss::GetAlive(void)                 //boss�������Ă�؋�����
{
	return Alive;
}

Vector2 Boss::GetPos(void)               //boss�̍��W��Ԃ�
{
	return Pos;
}

bool Boss::GameInit(void)                 //boss�̏���������
{
	life = 100;
	Pos.x = (SCREEN_SIZE_X - BOSS_SIZE_X) / 2;
	Pos.y = -BOSS_SIZE_Y;
	Alive = false;
	hunt = false;
	gamecounter = 0;
	stayTime = 180;
	huntTime = 180;
	shotFlag = false;
	bossLR = rand() % 2;
	xSpeed = 4;
	if (bossLR == 0)
	{
		xSpeed = 4;
		ySpeed = (rand() % 5) + 1;
	}
	else
	{
		xSpeed = -4;
		ySpeed = (rand() % 5) + 1;
	}
	return true;
}