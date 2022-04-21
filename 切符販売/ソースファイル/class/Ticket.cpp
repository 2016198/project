#include <DxLib.h>
#include "Ticket.h"

Ticket::Ticket()//�R���X�g���N�^
{
	GetMousePoint(&x_, &y_);
	mouse_[0] = false;
	mouse_[1] = false;
	scene_ = SCENE_ID::MAX;
	width_ = 0;
	IsBuy_ = false;
	ticketPrice_ = 0;
	ticketNum_ = 0;
	colorB_ = WHITE;
}

Ticket::~Ticket()//�f�X�g���N�^
{
}

SCENE_ID Ticket::GetScene(void)	//���݂̃V�[�������
{
	return scene_;
}

bool Ticket::MouseOneInput(void)//�}�E�X�̓���
{
	return mouse_[0] && !mouse_[1];
}

bool Ticket::HitBack(void)//1�߂�{�^��
{
	return x_ > 10 && y_ > 436 && x_ < 130 && y_ < 470;
}

void Ticket::DrawBack(void)//�߂�{�^���`��
{
	DrawExtendString(10, 438, 2.0, 2.0, "1�߂�", colorB_.GetColorCode());
	DrawBox(8, 436, 130, 470, colorB_.GetColorCode(), false);
}
