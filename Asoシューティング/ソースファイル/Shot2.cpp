#include "Shot2.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool Shot2::Init(void) //����������
{
	Image = LoadGraph("image/shot.png");
	if (Image == -1)
	{
		TRACE("�e�̉摜�̓ǂݍ��݂Ɏ��s���܂����B");
		return false;
	}
	pos.x = 0;
	pos.y = 0;
	Speed = 10;
	Alive = false;

	return true;
}

void Shot2::Setup(Vector2 pPos) //���@�̍��W�ɃZ�b�g����
{
	if (Alive == false)
	{
		Alive = true;
		pos.x = pPos.x;
		pos.y = pPos.y;
		//PlaySoundMem(se, DX_PLAYTYPE_BACK);
	}
}

void Shot2::UpDate(int i)  //�X�V����  ("i"�͂RWAY�V���b�g�p�̕ϐ�)
{
	if (pos.y >= -P_SHOT_SIZE_Y && Alive == true)          //���˂��Ă���Ƃ�
	{
		pos.y -= Speed;
		pos.x += i;
	}
	else    //��ʊO�ɏo�����̏���
	{
		Alive = false;          //���˂��Ă��Ȃ��Ƃ�
	}
}

void Shot2::Draw(void)//�`�揈��
{
	if (Alive == true)
	{
		DrawGraph(pos.x, pos.y, Image, true);                     //�e�̕`��
	}
}

Vector2 Shot2::GetPos(void)   //���W������^����
{
	return pos;
}

bool Shot2::GetAlive(void)   //�e�������Ă邩�ǂ���
{
	return Alive;
}

void Shot2::DeleteShot(void) //�e������
{
	Alive = false;
}

bool Shot2::Release(void) //�C���X�^���X�̉��
{
	DeleteGraph(Image);
	return true;
}

bool Shot2::GameInit(void)//�Q�[���I�[�o�[��̏���������
{
	pos.x = 0;
	pos.y = 0;
	Speed = 10;
	Alive = false;

	return true;
}