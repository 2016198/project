#include <DxLib.h>
#include <time.h>
#include "class/Select.h"
#include "class/Cash.h"
#include "class/EleMoney.h"
#include "resource.h"

constexpr int SCREEN_SIZE_X = 640;		//��ʂ̃T�C�Y�F��
constexpr int SCREEN_SIZE_Y = 480;		//��ʂ̃T�C�Y�F�c

Ticket* SceneChange(SCENE_ID nextScene) //�V�[���؂�ւ�
{
	Ticket* ticket = nullptr;
	switch (nextScene)
	{
	case SCENE_ID::SELECT:
		ticket = new Select();
		break;
	case SCENE_ID::CASH:
		ticket = new Cash();
		break;
	case SCENE_ID::ELEMONEY:
		ticket = new EleMoney();
		break;
	default:
		//�Ȃ�
		break;
	}
	return ticket;
};

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(true);
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	SetMainWindowText("�ؕ��̔�");
	SetWindowIconID(IDI_ICON1);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//��������
	Ticket* ticket_;
	SCENE_ID beforeScene_, afterScene_;

	//���̋���Ɩ���: 10 �~�� 15 ���A50 �~�� 3 ���A100 �~�� 2 ���A500 �~�� 1 ���A1000 �~�D 1 ���A
	//5000 �~�D 1 ���A10000 �~�D 1��
	//�����̏ꍇ��130�~�d�q�}�l�[�̏ꍇ��124�~�ƂȂ�

	//����������
	ticket_ = new Select();
	beforeScene_ = afterScene_ = ticket_->GetScene();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�X�V����
		ticket_->UpDate();
		afterScene_ = ticket_->GetScene();

		if (afterScene_ != beforeScene_) //�V�[���̐؂�ւ�
		{
			delete ticket_;
			ticket_ = nullptr;
			ticket_ = SceneChange(afterScene_);
		}

		beforeScene_ = afterScene_;

		//�`�揈��
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		ticket_->Draw();
		ticket_->DrawBack();

		ScreenFlip();
	}

	//�������
	delete ticket_;
	ticket_ = nullptr;

	DxLib_End();
	return 0;
}