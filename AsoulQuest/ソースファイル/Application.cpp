#include "Application.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include <time.h>
#include "KeyCheck.h"

bool Application::Init(void) //インスタンスの初期化
{
	//----------------システム処理
	SetWindowText("課題4_2016198_筒井杏二");
	//システム処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);           //640x480ドット65536色モードの設定
	ChangeWindowMode(true);                                   //true:window   false:フルスクリーン
	if (DxLib_Init() == -1)                                   //Dxライブラリーの初期化
	{
		return false;
	}
	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 225);

	//乱数の初期化
	srand((unsigned int)time(NULL));

	//各初期化処理
	if (!mScenemanager.Init(SCREEN_SIZE_X, SCREEN_SIZE_Y)) return false;
	KeyInit();

	return true;
}

void Application::Run(void)   //インスタンスの実行
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		CheckKeyList();                                     //トリガーチェック
		_dbgStartDraw();
		//インスタンス実行処理
		mScenemanager.Run();
		_dbgAddDraw();
		ScreenFlip();     //裏画面を表画面にコピー
	}
}

bool Application::Release(void)  //インスタンスの開放
{
	//インスタンスの開放処理
	if (!mScenemanager.Release()) return false;
	DxLib_End();                                        //Dxライブラリの終了
	return true;                                        //プログラムの終了
}