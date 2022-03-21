#pragma once
#include <type_traits>
#include <memory>
#include <array>
#include <map>
#include <string>
#include <vector>
#include "../Vector2.h"
#include "../Color3.h"
#include "../manager/MaterialManager.h"
#include "../Input/BaseInput.h"
#include "item/Item.h"

enum class DIR			//playerの向き
{
	DOWN,				//下
	LIFT,				//左
	RIGHT,				//右
	UP,					//上
	MAX
};

enum class MODE	//選択モード
{
	MOVE,					//移動
	ITEM,					//アイテム選択
	SELECT,					//移動かアイテムか選択
	WARP,					//ワープ移動
	NONE
};

constexpr int INVECTORY_MAX = 4;					//インベントリの最大値
constexpr size_t SOUND_CNT = 13;					//サウンドの数
constexpr int ANIM_SIZE = 3;						//アニメーションの数
constexpr Vector2 IMAGE_SIZE = { 96, 128 };			//プレイヤー画像のサイズ
constexpr Vector2 NUM_CNT = { 10, 1 };				//プレイヤー画像のサイズ
constexpr Vector2 PLAYER_SIZE = {					//プレイヤーのサイズ
	IMAGE_SIZE.x / ANIM_SIZE,
	IMAGE_SIZE.y / static_cast<int>(DIR::MAX)
};			
constexpr Vector2 PLAYER_HAFE_SIZE = {		//プレイヤーの半分サイズ
	PLAYER_SIZE.x / 2,
	PLAYER_SIZE.y / 2,
};

class Player
{
private:

	enum class HAPPENING	//ハプニング
	{
		RANDOM_POS,			//どこかへ飛ぶ
		RESET_POS,			//最初のところへ戻る
		GET_ITEM,			//アイテム入手
		CHANGE_POS,			//場所交換
		CHANGE_MAP,			//自陣変更
		NONE,				//はずれ
		MAX
	};

	struct PLAYER	//プレイヤーの情報
	{
		int pos[7];										//座標：0 = 現在、1～ = 過去のログ
		std::vector<ITEM>item;							//所持しているアイテム
		int move;										//何回移動したか
		DIR dir;										//プレイヤーの向き
		int warp;										//移動先
		double delta_;									//残り時間
	}; 

	const std::array<int, 4U> animNum_ = {	//アニメーションのループ
		0,
		1,
		2,
		1
	};

	std::string item_name_[static_cast<int>(ITEM::MAX)]	//表示する文字
	{
		"方位磁石を手に入れた！",
		"金属探知機を手に入れた！",
		"磁石を手に入れた！",
		"ろうそくを手に入れた！",
		"アイテムがいっぱいで入手できなかった…"
	};

	std::map<std::string, std::vector<std::string>> fileName_;			//グラフィック関係
	std::map<std::string ,VecInt> image_;								//グラフィックハンドル
	VecInt sound_;														//サウンドハンドル

	//セレクト用変数
	MODE select_;			//今どこにカーソルがあるか
	ITEM selectItem_;		//どのアイテムを選んでる？
	int selectInven_;		//インベントリの選択値
	int offsetSize_[static_cast<int>(ITEM::MAX) - 1] = {5, 1, 1, 1};//選択しているのを大きくする
	void SetSize(int num);	//選択してるのはどれ？
	
	//移動用変数
	Vector2 drawPos_[7];	//描画の座標
	Vector2 movePow_;		//移動量
	double moveSpeed_;		//移動の速さ
	int map_;				//目的地
	PLAYER player_ = {};	//Playerの独自の変数
	int alpha_;				//色の透明度
	Color3 color_;			//色コード
	bool moveEnd_;			//いどうおわった？
	void Move(void);		//移動する
	void MoveEnd(void);		//移動が終わったら実行
	int surround_;			//囲んだところ
	int SetSurround(void);	//囲んだところはどこ
	std::map<DIR, std::pair<bool, double>> canMove_ = {};				//移動可能
	unsigned int defultColor_;											//初期カラー
	void ChackDir(void);												//向きの処理

	//アイテム用変数
	double angle_;			//方位磁針の角度
	ITEM useItem_;			//どのアイテムを使っている？
	int fullItem_;			//アイテムがいっぱいか
	double itemLife_;		//アイテムの効果時間
	bool useMagnet_;		//磁石を使用しているか

	//その他
	MODE mode_;								//今のmode
	bool fadeIn_;							//色が変わる
	bool fadeOut_;							//色が変わる
	int respawn_;							//最初にいたところ
	int font_;								//フォントのハンドル
	double fontSize_;						//フォントのサイズ
	double delta_;							//デルタタイム
	bool lock_;								//一回でも移動したらロックする
	bool isMove_;							//動いているかどうか
	double target_;							//画像の角度
	double targetSenter_;					//画像の角度

	//アニメーション
	std::pair<double, int> animCnt_[2];			//アニメーション管理
	void SetAnim(double delta, int num);		//アニメーション処理
	double Deg2Rad(double deg);					//DegからRadへ変換

	//入力関係
	InputList input_ = {};					//入力情報

public:

	bool Init(int pos, int point, Color3 color);		//初期化処理
	bool Update(const InputList input, double delta);	//更新処理
	void Draw(int size);				//描画処理(メイン)
	void DrawMoveLine(void);			//描画処理(位置が重なってもわかりやすく)
	void DrawPlayer(bool over,int size);//描画処理(プレイヤーの画像)
	void DrawInfo(int num);				//描画処理(プレイヤーの情報)
	bool Release(void);					//解放処理

	Player(const char* nameG, const char* nameS);		//コンストラクタ
	~Player();											//デストラクタ

	bool IsChange_;						//場所交代
	bool IsHere_;						//集合
	void SetPos(int point);				//場所交代
	void SetItemLife(double life);		//アイテムの効果時間を取得

	void Happening(HAPPENING eve);		//間違えたところを囲んだら
	void ResetMove(void);				//ターンが終了
	ITEM GetSelectItem(void);			//選択しているアイテムを表示
	ITEM GetUseItem(void);				//使用しているアイテムを表示
	double GetAngle(void);				//角度を返す
	Vector2 GetDrawPos(void);			//座標Vector2を取得
	bool CheckHap(void);				//囲んだところが間違っているか:false　正解、あるいは囲んでない
	int GetMap(void);					//目的地を返す
	int GetPoint(void);					//座標を返す
	Vector2 GetDisVec2(void);			//目的地までの距離(x成分とy成分)
	void Undo(void);					//一つ戻す
	void Candle(CANDLE candle);			//ろうそくの効果
	bool IsFull(void);					//アイテムがいっぱいかどうか
	int GetMove(void);					//プレイヤーの移動量を受け取る
	void SetMode(MODE mode);			//モードの変更
	MODE GetMode(void);					//プレイヤーのモードを受け取る
	Vector2 GetInfoDrawPos(int num);	//情報の描画のわたす
	int GetSurround(void);				//囲んだ位置を返す
};

static DIR begin(DIR) { return DIR::DOWN; };
static DIR end(DIR) { return DIR::MAX; };
static DIR operator++(DIR& state)
{
	state = static_cast<DIR>(std::underlying_type<DIR>::type(state) + 1);
	return state;
};
static DIR operator*(const DIR& state) { return state; };

