//------------------------------------------
// �w�Дԍ�:2016198		����:����Ǔ�
//------------------------------------------
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include "Application.h"

// WinMain�֐�
//---------------------------------
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	Application application;	//�C���X�^���X�̐���

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
