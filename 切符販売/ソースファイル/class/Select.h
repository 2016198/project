#pragma once
#include "Ticket.h"

class Select :
    public Ticket
{
public:

	Select();							//�R���X�g���N�^
	~Select();							//�f�X�g���N�^

	bool Init(void) override;			//����������
	void UpDate(void) override;			//�X�V����
	void Draw(void) override;			//�`�揈��

private:

	const char* MSG_SELECT = "�x�����@��I�����Ă�������";		//�\�����b�Z�[�W

	const int SCREEN_SIZE_X = 640;								//��ʃT�C�YX
};

