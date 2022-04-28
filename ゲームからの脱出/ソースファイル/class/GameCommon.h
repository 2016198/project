#pragma once
#include <DxLib.h>

//マップチップのサイズ
constexpr int CHIP_SIZE_X = 32;
constexpr int CHIP_SIZE_Y = 32;

//画面サイズ
constexpr int SCREEN_SIZE_X = 640;
constexpr int SCREEN_SIZE_Y = 480;

//アニメーションの最大数
constexpr int ANIM_MAX = 3;

//方向の管理用
enum class DIR {
	DOWN,		//下方向
	LEFT,		//左
	RIGHT,		//右
	UP,			//上
	MAX
};
