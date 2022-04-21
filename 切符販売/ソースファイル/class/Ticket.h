#pragma once
#include <vector>
#include <array>
#include <string>
#include "Color3.h"

enum class SCENE_ID
{
	SELECT,
	CASH,
	ELEMONEY,
	MAX
};

class Ticket
{
public:
	Ticket();							//�R���X�g���N�^
	~Ticket();							//�f�X�g���N�^

	virtual bool Init(void) = 0;		//����������
	virtual void UpDate(void) = 0;		//�X�V����
	virtual void Draw(void) = 0;		//�`�揈��

	SCENE_ID GetScene(void);			//�V�[�������
	void DrawBack(void);				//�߂�{�^���`��

protected:

	bool MouseOneInput(void);								//1�t���[���̓���
	bool HitBack(void);										//�߂�{�^���ɂӂꂽ��

	const  std::array<std::string, 4U> BUY_TICKET = {		//�w������`�P�b�g�̖���
	"+1",
	"+10",
	"-1",
	"-10"
	};
	const char* MSG_BUY = "�w��";					//�w���̕���

	int width_;										//�����̉���
	bool IsBuy_;									//�w��������
	std::vector<Color3> color_;						//�J���[�R�[�h
	Color3 colorB_;									//�J���[�R�[�h
	int ticketPrice_;								//�ؕ��̒l�i
	int ticketNum_;									//�ؕ��̖���

	int x_, y_;										//�}�E�X�̍��W
	std::array<bool, 2U> mouse_;					//�}�E�X�̓���

	SCENE_ID scene_;								//���݂̃V�[��
};

