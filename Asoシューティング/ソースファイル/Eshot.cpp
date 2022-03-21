#include "Eshot.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool Eshot::Init(void)//����������
{
	Image = LoadGraph("image/eshot.png");
	if (Image == -1)
	{
		TRACE("�e�̉摜�̓ǂݍ��݂Ɏ��s���܂����B");
		return false;
	}
	pos.X = 0;
	pos.Y = 0;
	Alive = false;
	speed = 5;

	return true;
}

void Eshot::Setup(Vector2 ePos)//���W��^����
{
	if (Alive == false)
	{
		Alive = true;
		pos.X = ePos.X;
		pos.Y = ePos.Y;
		//PlaySoundMem(se, DX_PLAYTYPE_BACK);
	}
}

void Eshot::UpDate(Vector2 Pos)//�X�V����
{
	if (pos.Y >= -E_SHOT_SIZE_Y &&  //�X�N���[���̒��ɂ���Ƃ�
		pos.X >= -E_SHOT_SIZE_X &&
		pos.X <= SCREEN_SIZE_X &&
		pos.Y <= SCREEN_SIZE_Y &&
		Alive == true)          //���˂��Ă���Ƃ�
	{
		pos.Y += Pos.Yy * speed;
		pos.X += Pos.Xx * speed;
	}
	else    //��ʊO�ɏo�����̏���
	{
		Alive = false;          //���˂��Ă��Ȃ��Ƃ�
	}
}

void Eshot::Draw(void)//�`�揈��
{
	if (Alive == true)
	{
		DrawGraph(pos.X, pos.Y, Image, true);                     //�e�̕`��
	}
}

Vector2 Eshot::GetPos(void)   //���W������^����
{
	return pos;
}

bool Eshot::GetAlive(void)  //�����Ă邩�ǂ����̏�Ԃ�Ԃ�
{
	return Alive;
}

void Eshot::DeleteShot(void) //�e����������
{
	Alive = false;
}

bool Eshot::Release(void)  //�������
{
	DeleteGraph(Image);
	return true;
}

bool Eshot::GameInit(void)  //�Q�[���I�[�o�[�̌�̏���������
{
	pos.x = 0;
	pos.y = 0;
	Alive = false;

	return true;
}