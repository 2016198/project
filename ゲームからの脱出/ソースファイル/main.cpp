//--------------------------------------------
//ƒQ[ƒ€ŠJ”­
//--------------------------------------------

#include <DxLib.h>	
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"		
#include "class/Application.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR IpCmdLine, _In_ int nCmdShow)
{

	if (!lpApplication.Init())			//‰Šú‰»ˆ—
	{
		return -1;	
	}

	lpApplication.Run();				//Àsˆ—

	lpApplication.Release();			//‰ğ•úˆ—

	return 0;
}
