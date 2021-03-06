//--------------------------------------------
//ゲーム開発
//--------------------------------------------

#include <DxLib.h>	
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"		
#include "class/Application.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR IpCmdLine, _In_ int nCmdShow)
{

	if (!lpApplication.Init())			//初期化処理
	{
		return -1;	
	}

	lpApplication.Run();				//実行処理

	lpApplication.Release();			//解放処理

	return 0;
}
