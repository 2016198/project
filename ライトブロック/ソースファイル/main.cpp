//--------------------------------------------
//�Q�[������
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
	//�V�X�e������
	SetWindowText("�Q�[���J��");								//�Q�[���E�B���h�E�̃^�C�g��
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);				//�Q�[���E�B���h�E�̃T�C�Y�ƐF���[�h��ݒ�
	ChangeWindowMode(true);										//�Q�[���E�B���h�E�̕\�����@�ifalse�F�t���X�N���[���j
	if (DxLib_Init() == -1)
	{
		TRACE("DxLib�̏��������s");
		return -1;							//Dx���C�u�����̏��������s�̂��߃V�X�e���I��
	}

	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 255);

	//�C���X�^���X�̐���
	Light light;

	//�ϐ��̏�����
	srand((unsigned int)time(NULL));
	KeyInit();
	light.Init();

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();
		//���C������
		light.UpDate();
		//�`�揈��
		SetDrawScreen(DX_SCREEN_BACK);			//�`�悷���ʂ𗠂̉�ʂɐݒ�
		ClearDrawScreen();						//�`�悷���ʂ̓��e������
		CheckKeyList();
		light.Draw();
		_dbgAddDraw();
		ScreenFlip();							//���̉�ʂ�\�̉�ʂɏu�ԃR�s�[
	}

	//�V�X�e���I������
	DxLib_End();			//DX���C�u�����̏I������
	return 0;			//�Q�[���̏I��
}
