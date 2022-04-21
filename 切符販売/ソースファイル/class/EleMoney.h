#pragma once
#include "Ticket.h"

class EleMoney :
    public Ticket
{

public:

	EleMoney();							//�R���X�g���N�^
	~EleMoney();						//�f�X�g���N�^

	bool Init(void) override;			//����������
	void UpDate(void) override;			//�X�V����
	void Draw(void) override;			//�`�揈��

private:

	bool ticketConditions(int num);		//�`�P�b�g�w���ł��閇���̕\��

	const int ELEMONEY = 1000;			//�d�q�}�l�[�̎c��
	int purchase_;						//�w���z

	const char* MSG_LOG[2] = {			//�o�̓��b�Z�[�W
		"��������B�x���z �� %d�~",
		"������s�B�c�����s�����Ă��܂�"
	};
};

