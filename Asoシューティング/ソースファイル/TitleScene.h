//#pragma once

//定数定義
#define PAI 3.1415926535       //円周率
#define TITLE_SIZE_X 320       //文字のサイズX
#define TITLE_SIZE_Y 80        //文字のサイズY

class TitleScene
{
private:
	int tImage;                   //グラフィックハンドル（タイトル）
	int RImage;                   //グラフィックハンドル（時計回り）
	int LImage;                   //グラフィックハンドル（反時計回り）
	double en;                    //回転の速度
	int plus;                     //ゲームカウンター(+)
	int	minus;                    //ゲームカウンター(-)

public:
	bool Init(void);              //インスタンスの生成時処理
	void UpDate(void);            //インスタンスの更新処理
	void Draw(void);              //インスタンスの描画処理
	bool Release(void);           //インスタンスの開放処理
	bool GameInit(void);          //ゲームオーバー後の初期化処理
};
