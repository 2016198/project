//#pragma once
//#include "Stage.h"
//#include "Player.h"
#include "Vector2.h"
#include "gamecommon.h"
class Player;
class Stage;
class Shot;
class Lift;

//定数定義

class GameScene 
{
private:                    //メンバー変数
	int mCounter;           //ゲームカウンター

	Stage *mStage;			//"ステージ"のインスタンス生成用
	Player *mPlayer[static_cast<int>(PLAYER_TYPE::MAX)];		//"プレイヤー"のインスタンス生成用
	Shot *mShot;			//"ショット"のインスタンス生成
	Lift *mLift;			//"リフト"のインスタンス生成

	 
public:                    //メンバー関数
	bool Init(void);       //インスタンスの生成処理
	bool UpDate(void);     //インスタンスの更新処理
	void Draw(void);       //インスタンスの描画処理
	bool Release(void);    //インスタンスの開放処理
	bool GameInit(void);   //インスタンスの初期化処理

	int GetEvent(Vector2 pos);//マップのイベント情報を返す
	bool GetLiftAlive(void);//リフトの情報を返す。
	Vector2 GetLiftPos(void);//リフトの情報を返す。
};