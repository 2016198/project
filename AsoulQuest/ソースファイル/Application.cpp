#include "Application.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include <time.h>
#include "KeyCheck.h"

bool Application::Init(void) //�C���X�^���X�̏�����
{
	//----------------�V�X�e������
	SetWindowText("�ۑ�4_2016198_����Ǔ�");
	//�V�X�e������
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);           //640x480�h�b�g65536�F���[�h�̐ݒ�
	ChangeWindowMode(true);                                   //true:window   false:�t���X�N���[��
	if (DxLib_Init() == -1)                                   //Dx���C�u�����[�̏�����
	{
		return false;
	}
	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 225);

	//�����̏�����
	srand((unsigned int)time(NULL));

	//�e����������
	if (!mScenemanager.Init(SCREEN_SIZE_X, SCREEN_SIZE_Y)) return false;
	KeyInit();

	return true;
}

void Application::Run(void)   //�C���X�^���X�̎��s
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		CheckKeyList();                                     //�g���K�[�`�F�b�N
		_dbgStartDraw();
		//�C���X�^���X���s����
		mScenemanager.Run();
		_dbgAddDraw();
		ScreenFlip();     //����ʂ�\��ʂɃR�s�[
	}
}

bool Application::Release(void)  //�C���X�^���X�̊J��
{
	//�C���X�^���X�̊J������
	if (!mScenemanager.Release()) return false;
	DxLib_End();                                        //Dx���C�u�����̏I��
	return true;                                        //�v���O�����̏I��
}