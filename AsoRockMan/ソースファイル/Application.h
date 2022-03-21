//#pragma once
#include "SceneManager.h"

//定数定義

class Application
{
private://メンバー変数
	//インスタンスの生成
	SceneManager mScenemanager;

public:      //メンバー関数
	bool Init(void);          //インスタンスの生成処理
	void Run(void);           //インスタンスの実行処理
	bool Release(void);       //インスタンスの開放処理
};