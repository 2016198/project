#pragma once
#include "../Vector2.h"

class Bug
{
public:

	Bug(int image);		//コンストラクタ
	~Bug() {};			//デストラクタ

	void Generate(Vector2 pos, double angle, double life);
	void Update(double delta);		//更新処理
	void Draw(void);				//描画処理

	bool IsAlive(void);				//生存しているかどうか

private:

	int image_;			//グラフィックハンドル
	double life_;		//表示時間
	Vector2 pos_;		//座標
	double angle_;		//角度
};
