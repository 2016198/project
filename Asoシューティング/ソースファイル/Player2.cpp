#include "Player2.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "main.h"

bool Player2::Init(Vector2 Init)  //Player�N���X��Init�֐��̒��g
{
	Image = LoadGraph("image/player.png");
	if (Image == -1)
	{
		TRACE("�v���C���[�摜�̓ǂݍ��݂Ɏ��s���܂����B");
		return false;
	}
	life = PLAYER_LIFE;
	pos.x = Init.x;
	pos.y = Init.y;
	/*pos_x = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
	pos_y = SCREEN_SIZE_Y - PLAYER_SIZE_Y;*/
	Speed = 4;
	Alive = true;
	shotFlag = false;
	return true;
}

void Player2::Update(void)   //Player�N���X��UpDate�֐��̒��g
{
	if (Alive == false)
	{
		pos.x = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
		pos.y = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
		life--;
		Alive = true;
		//enemyAlive = false;
	}

	if (Alive == true)
	{
		if (CheckHitKey(KEY_INPUT_LEFT) && pos.x >= 0)   //���@�̈ړ�����
		{
			pos.x = pos.x - Speed;  //��
		}
		if (pos.x < 0)
		{
			pos.x = 0;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) && pos.x <= SCREEN_SIZE_X - PLAYER_SIZE_X)
		{
			pos.x = pos.x + Speed;  //�E
		}
		if (pos.x > SCREEN_SIZE_X - PLAYER_SIZE_X)
		{
			pos.x = SCREEN_SIZE_X - PLAYER_SIZE_X;
		}
		if (CheckHitKey(KEY_INPUT_UP) && pos.y >= 0)
		{
			pos.y = pos.y -Speed;  //��
		}
		if (pos.y < 0)
		{
			pos.y = 0;
		}
		if (CheckHitKey(KEY_INPUT_DOWN) && pos.y <= SCREEN_SIZE_Y - PLAYER_SIZE_Y)
		{
			pos.y = pos.y + Speed;  //��
		}
		if (pos.y > SCREEN_SIZE_Y - PLAYER_SIZE_Y)
		{
			pos.y = SCREEN_SIZE_Y - PLAYER_SIZE_Y;
		}
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		shotFlag = true;
	}
	else
	{
		shotFlag = false;
	}
}

void Player2::Draw(void)//�`�揈��
{
	DrawGraph(pos.x, pos.y, Image, true);   //���@
}

void Player2::Drawen(void)//�~�̕`�揈��
{
	DrawCircle(pos.x + PLAYER_SIZE_X / 2, pos.y + PLAYER_SIZE_Y / 2, PLAYER_SIZE_X / 2 + 10, GetColor(255, 255, 255), 0);
}

//�e�𔭎˂��Ă����true��Ԃ��B
bool Player2::IsShot(void)
{
	return shotFlag;
}

//�v���C���[�̍��W��Ԃ�
Vector2 Player2::GetPos(void)
{
	return pos;
}

void Player2::DeletePlayer(void) //�v���C���[������
{
	 Alive = false;
}

//�v���C���[�̐����Ă邩
bool Player2::GetAlive(void)
{
	return Alive;
}

bool Player2::Release(void) //�C���X�^���X�̉������
{
	DeleteGraph(Image);
	return true;
}

bool Player2::Death(void) //�v���C���[�S�ŏ���
{
	if (life <= 0)
	{
		return true;
	}
	return false;
}

int Player2::GetLife(void) //�c�@��Ԃ�
{
	return life;
}

bool Player2::GameInit(Vector2 Init)  //Player�N���X��Init�֐��̒��g
{
	life = 3;
	pos.x = Init.x;
	pos.y = Init.y;
	/*pos_x = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
	pos_y = SCREEN_SIZE_Y - PLAYER_SIZE_Y;*/
	Speed = 4;
	Alive = true;
	shotFlag = false;
	return true;
}
