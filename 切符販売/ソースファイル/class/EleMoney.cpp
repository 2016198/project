#include <DxLib.h>
#include "EleMoney.h"

EleMoney::EleMoney()//�R���X�g���N�^
{
	color_.resize(4U);
	scene_ = SCENE_ID::ELEMONEY;
	Init();
	UpDate();
}

EleMoney::~EleMoney()//�f�X�g���N�^
{
}

bool EleMoney::Init(void)//����������
{
	for (auto& c : color_)
	{
		c = WHITE;
	}
	purchase_ = 0;
	ticketPrice_ = 124;
	return true;
}

void EleMoney::UpDate(void)//�X�V����
{
	GetMousePoint(&x_, &y_);
	mouse_[0] = GetMouseInput() & MOUSE_INPUT_LEFT;

	//�߂�{�^��
	if (HitBack())
	{
		colorB_ = YELLOW;
		if (MouseOneInput())
		{
			scene_ = SCENE_ID::SELECT;
		}
	}
	else
	{
		colorB_ = WHITE;
	}

	if (IsBuy_ == false)
	{

		//�ؕ������I��
		for (int t = 0; t < 2; t++)
		{
			if (290 < x_ && 100 + t * 107 < y_ &&
				320 > x_ && 130 + t * 107 > y_)
			{
				if (ticketConditions(t))
				{
					color_[t] = YELLOW;
				}
				else
				{
					color_[t] = RED;
				}

				if (MouseOneInput())
				{
					ticketNum_ += atoi(BUY_TICKET[t + 1 * t].c_str());
					if (ticketNum_ < 0)
					{
						ticketNum_ = 0;
					}
				}
			}
			else
			{
				if (ticketConditions(t))
				{
					color_[t] = WHITE;
				}
				else
				{
					color_[t] = GRAY;
				}
			}
		}

		if (420 < x_ && 147 < y_ &&
			423 + width_ > x_ && 187 > y_)
		{
			if (ticketNum_ > 0)
			{
				color_[2] = YELLOW;
				if (MouseOneInput())
				{
					IsBuy_ = true;
					color_[2] = CYAN;
					if (ticketNum_ * ticketPrice_ <= ELEMONEY)
					{
						purchase_ = ticketNum_ * ticketPrice_;
					}
				}
			}
			else
			{
				color_[2] = RED;
			}
		}
		else
		{
			if (ticketNum_ > 0)
			{
				color_[2] = WHITE;
			}
			else
			{
				color_[2] = GRAY;
			}
		}

	}
	else
	{
		if (x_ > 400 && y_ > 210 &&
			x_ < 507 && y_ < 244)
		{
			color_[3] = YELLOW;
			if (MouseOneInput())
			{
				Init();
				IsBuy_ = false;
				ticketNum_ = 0;
			}
		}
		else
		{
			color_[3] = WHITE;
		}
	}

	mouse_[1] = mouse_[0];
}

void EleMoney::Draw(void)//�`�揈��
{
	DrawBox(100, 280, 540, 420, WHITE.GetColorCode(), false);

	//�`�P�b�g����
	for (int t = 0; t < 2; t++)
	{
		DrawBox(290, 100 + t * 107, 320, 130 + t * 107, color_[t].GetColorCode(), false);
		DrawString(297, 108 + 107 * t, BUY_TICKET[t + 1 * t].c_str(), color_[t].GetColorCode());
	}

	//�w��
	DrawExtendString(422, 151, 2.0, 2.0, MSG_BUY, color_[2].GetColorCode());
	width_ = GetDrawExtendStringWidth(2.0, MSG_BUY, color_[2].GetColorCode());
	DrawBox(420, 147, 423 + width_, 187, color_[2].GetColorCode(), false);

	//���̑�
	DrawFormatString(240, 70, WHITE.GetColorCode(), "�؎� �� 1�� %d�~", ticketPrice_);

	DrawFormatString(240, 140, WHITE.GetColorCode(), "����   ��  %d��", ticketNum_);
	DrawFormatString(240, 180, WHITE.GetColorCode(), "���v   ��  %d�~", ticketNum_ * ticketPrice_);

	DrawExtendFormatString(201, 294, 2.0, 2.0, WHITE.GetColorCode(), "�c�� �� %d�~", ELEMONEY - purchase_);

	//�d�q�}�l�[
	if (IsBuy_ == true)
	{
		if (ticketNum_ * ticketPrice_ <= ELEMONEY)
		{
			DrawExtendFormatString(105, 350, 2.0, 2.0, CYAN.GetColorCode(), MSG_LOG[0], ticketNum_ * ticketPrice_);
		}
		else
		{
			DrawExtendString(105, 350, 1.7, 1.7, MSG_LOG[1], RED.GetColorCode());
		}
	}

	if (IsBuy_ == true)
	{
		//���Z�b�g
		DrawExtendString(400, 212, 1.6, 2.0, "���Z�b�g", color_[3].GetColorCode());
		DrawBox(400, 210, 507, 244, color_[3].GetColorCode(), false);
	}
}

bool EleMoney::ticketConditions(int num)
{
	switch (num)
	{
	case 0:
		return true;
		break;
	case 1:
		return ticketNum_ > 0;
		break;
	default:
		return true;
		break;
	}
}
