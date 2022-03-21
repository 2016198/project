#include "Score.h"
#include "DxLib.h"
#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

bool Score::Init(void)//����������
{
	score = 0;
	highscore = 500;
	posx = 0;
	posy = 0;
	fontCount = 0;
	alive = false;
	return true;
}

void Score::UpDate(void)//�X�V����
{
	if (alive == true)
	{
		if (posy > 0) //��ʊO�ɏo�Ȃ��悤�ɂ���
		{
			posy -= 2;
		}
		else
		{
			posy = 0;
		}

		if (fontCount <= 30)   //�G�����ꂽ�瓾�_�̕\��
		{
			fontCount++;
		}
		else
		{
			fontCount = 0;
			alive = false;
		}
	}
	if (score > highscore) //�n�C�X�R�A�X�V����
	{
		highscore = score;
	}
	if (score > SCORE_MAX)//�X�R�A�̍ő�l
	{
		highscore = SCORE_MAX;
		score = SCORE_MAX;
	}
}

void Score::PointDraw(int type)//�X�R�A�i��ʓ��j�̕`�揈��
{
	if (alive == true)
	{
		if (type == 0)
		{
			SetFontSize(20);
			DrawFormatString(posx + 15, posy + 15, GetColor(0, 0, 255), "%d", SCORE_POINT);
		}
		if (type == 1)
		{
			SetFontSize(20);
			DrawFormatString(posx + 15, posy + 15, GetColor(255, 0, 255), "%d", ITEM_POINT);
		}
		if (type == 2)
		{
			SetFontSize(30);
			DrawFormatString(posx + 15, posy + 15, GetColor(255, 255, 255), "%d", BOSS_POINT);
		}
		if (type == 3)
		{
			SetFontSize(20);
			DrawFormatString(posx + 15, posy + 15, GetColor(100, 0, 100), "%d", -1);
		}
	}
}

void Score::ScoreDraw(void)//�X�R�A�i��ʊO�j�̕`�揈��
{
	font = GetDrawFormatStringWidth("%d", score);
	fonthigh = GetDrawFormatStringWidth("%d", highscore);
	SetFontSize(20);
	DrawString(SCREEN_SIZE_X - 90, 150, "�X�R�A", GetColor(178, 0, 0));
	DrawFormatString(SCREEN_SIZE_X - font, 150, GetColor(178, 0, 0), "\n%d", score);
	DrawString(SCREEN_SIZE_X - 110, 200, "�n�C�X�R�A", GetColor(178, 0, 0));
	DrawFormatString(SCREEN_SIZE_X - fonthigh, 200, GetColor(178, 0, 0), "\n%d", highscore);
}

void Score::SetUp(Vector2 pos) //���W�����炤
{
	posx = pos.x;
	posy = pos.y;
	alive = true;
}

bool Score::GetAlive(void) //�X�R�A���\������Ă邩���Ȃ���
{
	return alive;
}

bool Score::GameInit(void)  //�Q�[���I�[�o�[�̌�̏���������
{
	score = 0;
	posx = 0;
	posy = 0;
	fontCount = 0;
	alive = false;
	return true;
}

void Score::AddScore(int type) //�X�R�A�̉��_
{
	if (type == 0)
	{
		score += SCORE_POINT;
	}
	if (type == 1)
	{
		score += ITEM_POINT;
	}
	if (type == 2)
	{
		score += BOSS_POINT;
	}
}

int Score::GetScore(void)
{
	return score;
}