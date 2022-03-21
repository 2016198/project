#pragma once

//定数宣伝
/*---------------------------------*/
#define SCREEN_SIZE_X 600     //画面の横サイズ
#define SCREEN_SIZE_Y 480     //画面の縦サイズ

//プロトタイプ宣伝
enum SCENE_ID {
	TITLE_SCENE,
	GAME_SCENE,
	GAME_OVER_SCENE,
	GAME_CLEAR_SCENE,
	MAX_SCENE
};

void KeyCheck(void);
