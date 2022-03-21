#pragma once
#include "../Vector2.h"
#include "../Color3.h"

enum class MOVE_DIR			//移動の方向
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX
};

class Fire
{
public:

	Fire(std::vector<int> imageVec);	//コンストラクタ
	~Fire();							//デストラクタ

	static constexpr int ANIM_SIZE = 4;	//アニメーションの数

	void Create(int num);				//生成処理
	void Update(void);					//更新処理
	void Move(MOVE_DIR dir);			//移動処理
	void Draw(void);					//描画処理
	bool Check(int pos);				//確認処理

	bool IsAlive(void);					//生存チェック

private:

	Vector2 offsetSize_;				//オフセット
	int move_;							//移動回数
	double size_;						//大きさ
	int pos_;							//現在の座標
	bool alive_;						//生存確認
	Vector2 drawPos_;					//描画座標
	std::vector<int> image_;			//グラフィックハンドル
};

