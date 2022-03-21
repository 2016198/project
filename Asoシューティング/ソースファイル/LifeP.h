//#pragma once

//定数定義
#define HEART_SIZE_X 16       //ハートの横サイズ
#define HEART_SIZE_Y 16       //ハートの縦サイズ

class LifeP
{
private:
	int image;        //グラフィックハンドル (０:自機、１:ハート)
	int posx;         //ハートの座標
	int posy;         //ハートの座標
	int Speed;        //速さ
	int count;        //プレイヤーの残機

public:               //メンバー関数
	bool Init(void);                  //インスタンスの生成時の処理
	void Update(void);                //インスタンスの更新処理
	void Draw(int lifeP);             //インスタンスの描画処理 
	bool Release(void);               //インスタンスの開放処理
	bool GameInit(void);              //ハートの初期化処理
};
