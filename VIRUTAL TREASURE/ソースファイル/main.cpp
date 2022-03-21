#include <DxLib.h>
#include "resource.h"
#include "class/scene/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	SetOutApplicationLogValidFlag(0);			//Log.txt���쐬���Ȃ�
	SetWindowIconID(101);						//.exe�̃A�C�R���`�F���W
	SetWindowText("TreasureGame");
	ChangeWindowMode(true);

	if (!lpSceneMng.Init())	//����������
	{
		return -1;
	}

	lpSceneMng.Run();		//���s����

	lpSceneMng.Release();	//�������

	return 0;				//�v���O�����̏I��
}