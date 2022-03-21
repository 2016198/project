#pragma once
#include "BaseScene.h"

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	static SceneMng& GetInstance()
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	//static void Create(void)
	//{
	//	if (s_Instance == nullptr)
	//	{
	//		s_Instance = new SceneMng();
	//	}
	//}
	//static void Destroy(void)
	//{
	//	delete s_Instance;
	//	s_Instance = nullptr;
	//}
	void Run(void);
	void UpDate(void);
	void Draw(void);

private:
	//static SceneMng* s_Instance;
	bool SysInit(void);
	bool initFlag_;
	SceneMng();
	~SceneMng();

	uniqueScene scene_;
};

