#pragma once
#include "SceneManager.h"

#define lpApplication Application::GetInstance()	//シングルトーン

class Application
{
public:

	bool Init(void);				//初期化処理
	bool Run(void);					//更新処理
	bool Release(void);				//解放処理

	static Application& GetInstance()	//シングルトーン
	{
		static Application mApplication;
		return mApplication;
	}

private:

	Application() {};
	~Application() {};
};
