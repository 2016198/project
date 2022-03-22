#pragma once
#include <memory>
#include<list>
#include<map>
#include "../common/ImageMng.h"
#include "../common/ListMng.h"
#include "../common/Vector2.h"
#include "../common/input/Controller.h"
#include "../common/Collision.h" 

//class Controller;
//struct Move;
//struct StateCheck;
//struct KeyCheck;

class Obj
{
public:
	Obj();
	~Obj();
	virtual bool Init(CntType cntType, Vector2 pos) = 0;
	virtual void UpDate(ColList colList) = 0;
	virtual void Draw() = 0;
private:

protected:
	std::string state_;							//オブジェクトのアニメーションの状態
	std::string bState_;						//1フレーム前オブジェクトのアニメーションの状態
	double speedY_ = 0.0;						//移動速度:縦
	Vector2 pos_;								//座標
	Vector2 bPos_;								//一フレーム前の座標
	std::unique_ptr<Controller> controller_;	//コントローラ
	Vector2 collisionSize;						//当たり判定サイズ
	AnimeData animeData_;						//アニメのデータ
	bool turn_;									//画像の反転するか
	const double gravity = 0.2;					//重力加速度
	ColList colList_;							//当たり判定（地形）

	//friend Move;								//ジャイアン
	//friend StateCheck;
	//friend KeyCheck;
};

