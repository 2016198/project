/*************************************************************/
/*ゲーム制作  ：       Project4                              */
/*氏名        ：       2016198_筒井杏二                      */
/*************************************************************/

#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include "time.h"
#include "Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//インスタンスの生成
	Application application;

	//インスタンスの初期化
	if (!application.Init()) return -1;

	//インスタンスの実行
	application.Run();

	//インスタンスの開放
	if (!application.Release()) return -1;

	return 0;
}
