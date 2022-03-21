//#pragma once

//定義の宣伝
enum KEY_LIST
{
	//システム情報のキー情報
	KEY_SYS_START,
	KEY_SYS_RESET,
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,

	//プレイヤー１のキー情報
	KEY_P1_UP,
	KEY_P1_DOWN,
	KEY_P1_LEFT,
	KEY_P1_RIGHT,
	KEY_P1_A,
	KEY_P1_B,

	//プレイヤー２のキー情報
	KEY_P2_UP,
	KEY_P2_DOWN,
	KEY_P2_LEFT,
	KEY_P2_RIGHT,
	KEY_P2_A,
	KEY_P2_B,

	//キーリストの最大値
	KEY_LIST_MAX
};

//キー管理用変数
//true : キーを押している状態　または　トリガーが発生している状態
//後でC++化するので今のところ、extrunで公開するゾ～
//extern bool KeyOld[KEY_LIST_MAX];          //１フレーム前のキーの状態
extern bool KeyNow[KEY_LIST_MAX];            //現在のキーの状態
extern bool KeyTrgUp[KEY_LIST_MAX];          //KeyDownの状態
extern bool KeyTrgDown[KEY_LIST_MAX];        //KeyUpの状態

//プロトタイプ宣伝
void KeyInit(void);           //キー情報の初期化処理
void CheckKeyList(void);      //キー情報の作成