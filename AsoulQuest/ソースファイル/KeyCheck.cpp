#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"

//�L�[�Ǘ��p�ϐ�
//true : �L�[�������Ă����ԁ@�܂��́@�g���K�[���������Ă�����
bool KeyOld[KEY_LIST_MAX];            //���݂̃L�[�̏��
bool KeyNow[KEY_LIST_MAX];            //�P�t���[���O�̃L�[�̏��
bool KeyTrgUp[KEY_LIST_MAX];          //KeyDown�̏��
bool KeyTrgDown[KEY_LIST_MAX];        //KeyUp�̏��

void KeyInit(void)       //�L�[���̏�����
{
	//�z��̏���������
	for (int j = 0; j < KEY_LIST_MAX; j++)
	{
		KeyOld[j] = false;
		KeyNow[j] = false;
		KeyTrgUp[j] = false;
		KeyTrgDown[j] = false;
	}
}

void CheckKeyList(void)    //�L�[���̍쐬
{
	//�L�[�Ǘ��f�[�^�[�̍쐬
	for (int l = 0; l < KEY_LIST_MAX; l++)
	{
		KeyOld[l] = KeyNow[l];
		KeyNow[l] = false;
		KeyTrgUp[l] = false;
		KeyTrgDown[l] = false;
	}

	KeyNow[KEY_SYS_START] = CheckHitKey(KEY_INPUT_SPACE);
	KeyNow[KEY_SYS_RESET] = CheckHitKey(KEY_INPUT_Z);
	KeyNow[MOUSE_LEFT] = GetMouseInput()&MOUSE_INPUT_LEFT;
	KeyNow[MOUSE_RIGHT] = GetMouseInput()&MOUSE_INPUT_RIGHT;
	KeyNow[MOUSE_MIDDLE] = GetMouseInput()&MOUSE_INPUT_MIDDLE;

	KeyNow[KEY_P1_UP] = CheckHitKey(KEY_INPUT_UP);
	KeyNow[KEY_P1_DOWN] = CheckHitKey(KEY_INPUT_DOWN);
	KeyNow[KEY_P1_LEFT] = CheckHitKey(KEY_INPUT_LEFT);
	KeyNow[KEY_P1_RIGHT] = CheckHitKey(KEY_INPUT_RIGHT);
	KeyNow[KEY_P1_A] = CheckHitKey(KEY_INPUT_RCONTROL);
	KeyNow[KEY_P1_B] = CheckHitKey(KEY_INPUT_BACKSLASH);

	KeyNow[KEY_P2_UP] = CheckHitKey(KEY_INPUT_W);
	KeyNow[KEY_P2_DOWN] = CheckHitKey(KEY_INPUT_S);
	KeyNow[KEY_P2_LEFT] = CheckHitKey(KEY_INPUT_A);
	KeyNow[KEY_P2_RIGHT] = CheckHitKey(KEY_INPUT_D);
	KeyNow[KEY_P2_A] = CheckHitKey(KEY_INPUT_G);
	KeyNow[KEY_P2_B] = CheckHitKey(KEY_INPUT_F);

	for (int n = 0; n < KEY_LIST_MAX; n++)
	{
		KeyTrgDown[n] = ~KeyOld[n] & KeyNow[n];          //���Z
		KeyTrgUp[n] = KeyOld[n] & ~KeyNow[n];            //���Z
	}
	//for (int n = 0; n < KEY_LIST_MAX; n++)
	//{
		/*if (KeyTrgDown[n]) printf("d\n");
		if (KeyTrgUp[n]) printf("h\n");*/
	//}
}