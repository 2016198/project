//#pragma once
#include "SceneManager.h"

//�萔��`

class Application
{
private://�����o�[�ϐ�
	//�C���X�^���X�̐���
	SceneManager mScenemanager;

public:      //�����o�[�֐�
	bool Init(void);          //�C���X�^���X�̐�������
	void Run(void);           //�C���X�^���X�̎��s����
	bool Release(void);       //�C���X�^���X�̊J������
};