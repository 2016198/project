//#pragma once
#include "gamecommon.h"

//�萔��`
#define GAME_OVER_SIZE_X 457
#define GAME_OVER_SIZE_Y 81

class GameOver
{
private:                   //�����o�[�ϐ�
	int mImage;            //�O���t�B�b�N�n���h��
	int mCounter;          //�Q�[���I�[�o�[�J�E���^�[


public:                    //�����o�[�֐�
	bool Init(void);       //�C���X�^���X�̐�������
	bool UpDate(void);     //�C���X�^���X�̍X�V����
	void Draw(void);       //�C���X�^���X�̕`�揈��
	bool Release(void);    //�C���X�^���X�̊J������
	bool GameInit(void);   //�C���X�^���X�̏���������
};
