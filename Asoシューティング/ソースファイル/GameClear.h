//#pragma once
#define TITLE_CLEAR_SIZE_X 320    //ゲームクリアのサイズX
#define TITLE_CLEAR_SIZE_Y 80     //ゲームクリアのサイズY
#define TETE_SIZE_X 16            //拍手のサイズX
#define TETE_SIZE_Y 16            //拍手のサイズY

class GameClear
{
private:
	int image;                    //グラフィックハンドル（タイトル）
	int te[2];                    //グラフィックハンドル（拍手）
	int se;                       //効果音ハンドル
	int score;                    //スコア
	int counter;                  //ゲームカウンター
	int x;                        //x座標
	int y;                        //y座標
public:
	bool Init(void);              //インスタンスの生成時処理
	void UpDate(void);            //インスタンスの更新処理
	void Draw(int score);         //インスタンスの描画処理
	bool Release(void);           //インスタンスの開放処理
	void Reset(void);              //カウンターリセット処理
};
