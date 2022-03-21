#include<DxLib.h>			//Dx���C�u�����̎g�p
#include"KeyCheck.h"

//�L�[���̏�����

bool keyOld[KEY_LIST_MAX];			//1�t���[���O�̃L�[���
bool keyNew[KEY_LIST_MAX];			//���t���[���̃L�[���
bool keyTrgUp[KEY_LIST_MAX];		//KeyDown�g���K�[
bool keyTrgDown[KEY_LIST_MAX];		//KeyUp�g���K�[

void KeyInit(void)
{
	//�L�[�Ǘ��p�̔z������ׂď���������
	for (int k = 0; k < KEY_LIST_MAX; k++)
	{
		keyOld[k] = false;
		keyNew[k] = false;
		keyTrgUp[k] = false;
		keyTrgDown[k] = false;
	}
}
//�L�[���̍쐬
void CheckKeyList(void)
{
	//�L�[�Ǘ��f�[�^�̍쐬
	//�P�t���[���O�̏�Ԃ��쐬�A����ȊO�͑S������
	for (int k = 0; k < KEY_LIST_MAX; k++)
	{
		keyOld[k] = keyNew[k];
		keyNew[k] = false;
		keyTrgUp[k] = false;
		keyTrgDown[k] = false;
	}

	//KeyOld[KEY_SYS_START] = KeyNew[KEY_SYS_START];
	//KeyNew[KEY_SYS_START] = false;
	//KeyTrgUp[KEY_SYS_START] = false;
	//KeyTrgDown[KEY_SYS_START] = false;


	//���t���[���f�[�^���쐬
	keyNew[KEY_SYS_START] = CheckHitKey(KEY_INPUT_SPACE);

	//�}�E�X�̐ݒ�
	keyNew[MOUSE_LEFT] = GetMouseInput() & MOUSE_INPUT_LEFT;
	keyNew[MOUSE_RIGHT] = GetMouseInput() & MOUSE_INPUT_RIGHT;
	keyNew[MOUSE_MIDDLE] = GetMouseInput() & MOUSE_INPUT_MIDDLE;

	//PLAYER1:�L�[�{�[�h�̉E��
	keyNew[KEY_P1_UP] = CheckHitKey(KEY_INPUT_UP);
	keyNew[KEY_P1_DOWN] = CheckHitKey(KEY_INPUT_DOWN);
	keyNew[KEY_P1_LEFT] = CheckHitKey(KEY_INPUT_LEFT);
	keyNew[KEY_P1_RIGHT] = CheckHitKey(KEY_INPUT_RIGHT);
	keyNew[KEY_P1_A] = CheckHitKey(KEY_INPUT_RCONTROL);
	keyNew[KEY_P1_B] = CheckHitKey(KEY_INPUT_RSHIFT);

	//PLAYER2:�L�[�{�[�h�̍���
	keyNew[KEY_P2_UP] = CheckHitKey(KEY_INPUT_W);
	keyNew[KEY_P2_DOWN] = CheckHitKey(KEY_INPUT_S);
	keyNew[KEY_P2_LEFT] = CheckHitKey(KEY_INPUT_A);
	keyNew[KEY_P2_RIGHT] = CheckHitKey(KEY_INPUT_D);
	keyNew[KEY_P2_A] = CheckHitKey(KEY_INPUT_LCONTROL);
	keyNew[KEY_P1_B] = CheckHitKey(KEY_INPUT_LSHIFT);

	//�g���K�[�����쐬
	for (int k = 0; k < KEY_LIST_MAX; k++)
	{
		if (keyNew[k] == 1 && keyOld[k] == 0)
		{
			keyTrgDown[k] = true;
		}

		if (keyNew[k] == 0 && keyOld[k] == 1)
		{
			keyTrgUp[k] = true;
		}
	}
}