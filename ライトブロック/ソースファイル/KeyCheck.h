//#pragma once

//定義の宣言
enum KEY_LIST			//キー管理情報
{
	//システム関連のキー情報
	KEY_SYS_START,
	//マウス操作情報
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,

	//プレイヤー1のキー情報
	KEY_P1_UP,
	KEY_P1_DOWN,
	KEY_P1_LEFT,
	KEY_P1_RIGHT,
	KEY_P1_A,
	KEY_P1_B,

	//プレイヤー2のキー情報
	KEY_P2_UP,
	KEY_P2_DOWN,
	KEY_P2_LEFT,
	KEY_P2_RIGHT,
	KEY_P2_A,
	KEY_P2_B,

	KEY_LIST_MAX

};
//true:キーを押している状態、またはトリガーが発生している状態
extern bool keyOld[KEY_LIST_MAX];			//1フレーム前のキー状態
extern bool keyNew[KEY_LIST_MAX];			//現フレームのキー状態
extern bool keyTrgUp[KEY_LIST_MAX];		//KeyDownトリガー
extern bool keyTrgDown[KEY_LIST_MAX];		//KeyUpトリガー

//プロトタイプ宣言
void KeyInit(void);				//キー情報の初期化
void CheckKeyList(void);		//キー情報の作成