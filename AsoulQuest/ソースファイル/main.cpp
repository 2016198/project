/*************************************************************/
/*�Q�[������  �F       Project4                              */
/*����        �F       2016198_����Ǔ�                      */
/*************************************************************/

#include "main.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include "time.h"
#include "Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�C���X�^���X�̐���
	Application application;

	//�C���X�^���X�̏�����
	if (!application.Init()) return -1;

	//�C���X�^���X�̎��s
	application.Run();

	//�C���X�^���X�̊J��
	if (!application.Release()) return -1;

	return 0;
}
