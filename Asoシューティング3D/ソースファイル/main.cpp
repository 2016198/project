//------------------------------------------
// ����      �F����
//------------------------------------------
#include <DxLib.h>
#include "Application.h"

// WinMain�֐�
//---------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
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
