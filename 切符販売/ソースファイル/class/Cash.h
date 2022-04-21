#pragma once
#include <map>
#include "Ticket.h"

class Cash:
	public Ticket
{
public:

	Cash();								//�R���X�g���N�^
	~Cash();							//�f�X�g���N�^

	bool Init(void) override;			//����������
	void UpDate(void) override;			//�X�V����
	void Draw(void) override;			//�`�揈��

private:
	bool ticketConditions(int num);							//�`�P�b�g�w���ł��閇���̕\��

	static constexpr size_t CASH_COUNT = 7U;				//�����̐�

	const std::array<std::string, CASH_COUNT> CASH_TYPE = {	//�����̎��
		"10",
		"50",
		"100",
		"500",
		"1000",
		"5000",
		"10000"
	};

	const std::array<int, CASH_COUNT> CASH_HAVE = {			//�����ɏ������Ă錻���̖���
		15,		//10�~
		3,		//50�~
		2,		//100�~
		1,		//500�~
		1,		//1000�~
		1,		//5000�~
		1		//10000�~
	};

	std::map<std::string, int> haveCash_;			//�������Ă��錻��
	std::map<std::string, int> inputCash_;			//�}����������
	std::map<std::string, int> changeCash_;			//�}����������
	int changeAdd_;									//����
	int pay_;										//�x���z
};

