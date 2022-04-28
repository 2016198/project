#include <DxLib.h>
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"
#include "Application.h"
#include "KeyCheck.h"
#include "../Resource.h"

bool Application::Init(void)
{
	//�V�X�e������
	SetOutApplicationLogValidFlag(false);

	SetWindowIconID(IDI_ICON1);
	SetWindowText("�y������E�o�Q�[���z�Q�[������̒E�o");		//�Q�[���E�B���h�E�̃^�C�g��

	SetGraphMode(640, 480, 16);	//�Q�[���E�B���h�E�̃T�C�Y�ƐF���[�h��ݒ�
	ChangeWindowMode(true);		//�Q�[���E�B���h�E�̕\�����@�ifalse�F�t���X�N���[���j
	if (DxLib_Init() == -1)
	{
		TRACE("DxLib�̏��������s");
		return false;	//Dx���C�u�����̏��������s�̂��߃V�X�e���I��

	}

	_dbgSetup(640, 480, 255);

	lpSceneManager.Init();
	return true;
}
bool Application::Run(void)
{	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//���C������
		lpSceneManager.Run();
	}

	return true;
}
bool Application::Release(void)
{
	lpSceneManager.Release();

	//�V�X�e���I������
	DxLib_End();			//DX���C�u�����̏I������
	return true;			//�Q�[���̏I��
}