#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"

//キー管理用変数
//true : キーを押している状態　または　トリガーが発生している状態
bool KeyOld[KEY_LIST_MAX];            //現在のキーの状態
bool KeyNow[KEY_LIST_MAX];            //１フレーム前のキーの状態
bool KeyTrgUp[KEY_LIST_MAX];          //KeyDownの状態
bool KeyTrgDown[KEY_LIST_MAX];        //KeyUpの状態

void KeyInit(void)       //キー情報の初期化
{
	//配列の初期化処理
	for (int j = 0; j < KEY_LIST_MAX; j++)
	{
		KeyOld[j] = false;
		KeyNow[j] = false;
		KeyTrgUp[j] = false;
		KeyTrgDown[j] = false;
	}
}

void CheckKeyList(void)    //キー情報の作成
{
	//キー管理データーの作成
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
		KeyTrgDown[n] = ~KeyOld[n] & KeyNow[n];          //演算
		KeyTrgUp[n] = KeyOld[n] & ~KeyNow[n];            //演算
	}
	//for (int n = 0; n < KEY_LIST_MAX; n++)
	//{
		/*if (KeyTrgDown[n]) printf("d\n");
		if (KeyTrgUp[n]) printf("h\n");*/
	//}
}