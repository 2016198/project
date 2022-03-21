#include<DxLib.h>			//Dxライブラリの使用
#include"KeyCheck.h"

//キー情報の初期化

bool keyOld[KEY_LIST_MAX];			//1フレーム前のキー状態
bool keyNew[KEY_LIST_MAX];			//現フレームのキー状態
bool keyTrgUp[KEY_LIST_MAX];		//KeyDownトリガー
bool keyTrgDown[KEY_LIST_MAX];		//KeyUpトリガー

void KeyInit(void)
{
	//キー管理用の配列をすべて初期化する
	for (int k = 0; k < KEY_LIST_MAX; k++)
	{
		keyOld[k] = false;
		keyNew[k] = false;
		keyTrgUp[k] = false;
		keyTrgDown[k] = false;
	}
}
//キー情報の作成
void CheckKeyList(void)
{
	//キー管理データの作成
	//１フレーム前の状態を作成、それ以外は全初期化
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


	//現フレームデータを作成
	keyNew[KEY_SYS_START] = CheckHitKey(KEY_INPUT_SPACE);

	//マウスの設定
	keyNew[MOUSE_LEFT] = GetMouseInput() & MOUSE_INPUT_LEFT;
	keyNew[MOUSE_RIGHT] = GetMouseInput() & MOUSE_INPUT_RIGHT;
	keyNew[MOUSE_MIDDLE] = GetMouseInput() & MOUSE_INPUT_MIDDLE;

	//PLAYER1:キーボードの右側
	keyNew[KEY_P1_UP] = CheckHitKey(KEY_INPUT_UP);
	keyNew[KEY_P1_DOWN] = CheckHitKey(KEY_INPUT_DOWN);
	keyNew[KEY_P1_LEFT] = CheckHitKey(KEY_INPUT_LEFT);
	keyNew[KEY_P1_RIGHT] = CheckHitKey(KEY_INPUT_RIGHT);
	keyNew[KEY_P1_A] = CheckHitKey(KEY_INPUT_RCONTROL);
	keyNew[KEY_P1_B] = CheckHitKey(KEY_INPUT_RSHIFT);

	//PLAYER2:キーボードの左側
	keyNew[KEY_P2_UP] = CheckHitKey(KEY_INPUT_W);
	keyNew[KEY_P2_DOWN] = CheckHitKey(KEY_INPUT_S);
	keyNew[KEY_P2_LEFT] = CheckHitKey(KEY_INPUT_A);
	keyNew[KEY_P2_RIGHT] = CheckHitKey(KEY_INPUT_D);
	keyNew[KEY_P2_A] = CheckHitKey(KEY_INPUT_LCONTROL);
	keyNew[KEY_P1_B] = CheckHitKey(KEY_INPUT_LSHIFT);

	//トリガー情報を作成
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