#pragma once
//定数定義
#define SCREEN_SIZE_X 800                                  //画面の横サイズ
#define SCREEN_SIZE_Y 600                                  //画面の縦サイズ
#define GAME_SCREEN_X 40                                   //ゲームのわくX
#define GAME_SCREEN_Y 75                                   //ゲームのわくY
#define GAME_SCREEN_SIZE_X 640                             //ゲームの仮面サイズX
#define GAME_SCREEN_SIZE_Y 480                             //ゲームの画面サイズY
#define ANIM_MAX 3                                         //アニメーションのコマ数
#define PLAYER_SIZE_X 32                                   //自機のサイズX
#define PLAYER_SIZE_Y 32                                   //自機のサイズY
#define PLAYER_LIFE 5                                      //ライフの数
#define ENEMY_SIZE_X 32                                    //敵のサイズX
#define ENEMY_SIZE_Y 32                                    //敵のサイズY
#define ENEMY_POINT 100                                    //敵を倒した時のポイント
#define ENEMY_BONUS 5                                      //UFOを倒した時のポイント(ENEMY_POINT × ENEMY_BONUS)
#define ENEMY_COUNT_X 8                                    //敵の数X
#define ENEMY_COUNT_Y 7                                    //敵の数Y
#define P_SHOT_SIZE_X 6                                    //弾のサイズ横p
#define P_SHOT_SIZE_Y 30                                   //弾のサイズ縦p
#define E_SHOT_SIZE_X 16                                   //弾のサイズ横e
#define E_SHOT_SIZE_Y 25                                   //弾のサイズ縦e
#define SCORE_MAX 9999                                     //スコアの最大値
#define SCORE_TIME 30                                      //スコアの表示時間(N/60秒)
#define TITLE_SIZE_X 423                                   //タイトルのサイズX
#define TITLE_SIZE_Y 198                                   //タイトルのサイズY
#define ARROW_SIZE_X 32                                    //矢印のサイズX
#define ARROW_SIZE_Y 32                                    //矢印のサイズY
#define GAMEOVER_SIZE_X 452                                //ゲームオーバーのサイズ
#define GAMEOVER_SIZE_Y 123                                //ゲームオーバーのサイズ
#define GET_ENEMY_POS_Y(y) (ENEMY_SIZE_Y * y * 9 / 7)      //縦の隙間
#define GET_ENEMY_POS_X(x) (ENEMY_SIZE_X * x * 3 / 2)      //横の隙間
#define PI  3.1415926535897932384626433832795f	  	       //円周率

enum DIR_ID {
	DIR_DOWN,               //下方向
	DIR_LEFT,               //左方向
	DIR_RIGHT,              //右方向
	DIR_UP,                 //上方向
	DIR_MAX
};

enum ENEMY_TYPE {           //敵の種類
	ENEMY_TYPE_1,
	ENEMY_TYPE_2,
	ENEMY_TYPE_3,
	ENEMY_TYPE_4,
	ENEMY_TYPE_5,
	ENEMY_TYPE_6,
	ENEMY_TYPE_UFO,
	ENEMY_TYPE_MAX
};

enum MOVE_LR {                  //左か右か
	MOVE_LEFT,   
	MOVE_RIGHT,  
	MOVE_MAX
};

enum MOVE_MODE {                //移動モードが左右か下か
	MOVE_MODE_LR,    
	MOVE_MODE_DOWN,  
	MOVE_MODE_MAX
};

enum SCENE_ID {              //ゲームのシーン
	SCENE_ID_INIT,
	SCENE_ID_GAME,
	SCENE_ID_TITLE,
	SCENE_ID_LOSE,
	SCENE_ID_MAX
};
                                  //"戻り値" "名前"("引数");
bool SysInit(void);               //プロトタイプ宣伝bool
bool GameInit(void);               //ゲームの初期化処理
void InitShot(void);              //弾を消す関数
void CheckEnemyMoveLR(void);      //敵の移動モード
void Draw(void);                  //作画処理
void Player(void);                //プレイヤー処理
void PlayerDeathProcess(void);    //ゲームオーバー処理
void Enemy(void);                 //敵の処理
void PShot(void);                 //弾(P)の処理
void EShot(void);                 //弾(E)の処理
void HitCheck(void);              //当たり判定
void Score(void);                 //スコアの処理
void BgMove(void);                //背景の処理
void Gamestart(void);             //初期処理
void Gamescene(void);             //ゲームの処理
void Gameclear(void);             //ゲームクリアの処理
void Gameover(void);              //ゲームオーバーの処理
void KeyCheck(void);              //キートリガーチェック用関数
void InitScene(void);             //初期化シーン