#pragma once

//定数定義
//スクリーンサイズ
#define SCREEN_SIZE_X 768
#define SCREEN_SIZE_Y 480

//マップチップのサイズ
#define CHIP_SIZE_X 32
#define CHIP_SIZE_Y 32

//マップチップの数
#define MAP_X 24
#define MAP_Y 14

//リフトのサイズ
#define LIFT_SIZE_X 120
#define LIFT_SIZE_Y 16

enum class DIR	//キャラクターの向き
{
	RIGHT,
	LEFT,
	TOP,
	BOTTOM,
	MAX
};

enum class PLAYER_TYPE //プレイヤーの種類
{
	PLAYER1,
	PLAYER2,
	MAX
};
