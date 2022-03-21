#pragma once 

//マップのチップ数
#define MAP_X 50
#define MAP_Y 50

//マップのチップサイズ
#define CHIP_SIZE_X 32
#define CHIP_SIZE_Y 32

//敵の数
#define ENEMY_COUNT 10

//弾の数
#define SHOT_COUNT 40

//スコアの数
#define SCORE_COUNT 10

//アイテムの数
#define ITEM_COUNT 10

//爆発の数
#define BLAST_COUNT 10

//キャラクターのライフ最大値
#define LIFE_COUNT 100


//キャラクターの向き
enum class DIR {
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_MAX,
};

//敵の種類管理用
enum ENEMY_TYPE {
	ENEMY_TYPE_SLIME,
	ENEMY_TYPE_BEE,
	ENEMY_TYPE_FLAME,
	ENEMY_TYPE_R_DRAGON,
	ENEMY_TYPE_B_DRAGON,
	ENEMY_TYPE_BOSS,
	ENEMY_TYPE_MAX
};
