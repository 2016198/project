#pragma once
#include "SceneManager.h"

#define lpApplication Application::GetInstance()	//�V���O���g�[��

class Application
{
public:

	bool Init(void);				//����������
	bool Run(void);					//�X�V����
	bool Release(void);				//�������

	static Application& GetInstance()	//�V���O���g�[��
	{
		static Application mApplication;
		return mApplication;
	}

private:

	Application() {};
	~Application() {};
};
