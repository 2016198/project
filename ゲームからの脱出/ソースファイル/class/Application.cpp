#include <DxLib.h>
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"
#include "Application.h"
#include "KeyCheck.h"
#include "../Resource.h"

bool Application::Init(void)
{
	//システム処理
	SetOutApplicationLogValidFlag(false);

	SetWindowIconID(IDI_ICON1);
	SetWindowText("【謎解き脱出ゲーム】ゲームからの脱出");		//ゲームウィンドウのタイトル

	SetGraphMode(640, 480, 16);	//ゲームウィンドウのサイズと色モードを設定
	ChangeWindowMode(true);		//ゲームウィンドウの表示方法（false：フルスクリーン）
	if (DxLib_Init() == -1)
	{
		TRACE("DxLibの初期化失敗");
		return false;	//Dxライブラリの初期化失敗のためシステム終了

	}

	_dbgSetup(640, 480, 255);

	lpSceneManager.Init();
	return true;
}
bool Application::Run(void)
{	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//メイン処理
		lpSceneManager.Run();
	}

	return true;
}
bool Application::Release(void)
{
	lpSceneManager.Release();

	//システム終了処理
	DxLib_End();			//DXライブラリの終了処理
	return true;			//ゲームの終了
}