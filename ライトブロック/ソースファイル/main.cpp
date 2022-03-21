//--------------------------------------------
//ゲーム制作
//--------------------------------------------

#include <DxLib.h>
#include <time.h>
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"			
#include "KeyCheck.h"
#include "main.h"
#include "Light.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR IpCmdLine, _In_ int nCmdShow)
{
	//システム処理
	SetWindowText("ゲーム開発");								//ゲームウィンドウのタイトル
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);				//ゲームウィンドウのサイズと色モードを設定
	ChangeWindowMode(true);										//ゲームウィンドウの表示方法（false：フルスクリーン）
	if (DxLib_Init() == -1)
	{
		TRACE("DxLibの初期化失敗");
		return -1;							//Dxライブラリの初期化失敗のためシステム終了
	}

	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 255);

	//インスタンスの生成
	Light light;

	//変数の初期化
	srand((unsigned int)time(NULL));
	KeyInit();
	light.Init();

	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();
		//メイン処理
		light.UpDate();
		//描画処理
		SetDrawScreen(DX_SCREEN_BACK);			//描画する画面を裏の画面に設定
		ClearDrawScreen();						//描画する画面の内容を消去
		CheckKeyList();
		light.Draw();
		_dbgAddDraw();
		ScreenFlip();							//裏の画面を表の画面に瞬間コピー
	}

	//システム終了処理
	DxLib_End();			//DXライブラリの終了処理
	return 0;			//ゲームの終了
}
