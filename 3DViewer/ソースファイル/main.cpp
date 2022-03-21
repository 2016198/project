//------------------------------------------
// 学籍番号:2016198		氏名:筒井杏二
//------------------------------------------
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include "Application.h"

// WinMain関数
//---------------------------------
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	Application application;	//インスタンスの生成

	if (!application.Init())
	{
		return -1;
	}

	application.Run();

	if (!application.Release())
	{
		return -1;
	}

	return 0;
}
