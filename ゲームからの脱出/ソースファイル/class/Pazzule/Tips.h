#pragma once

class Tips
{
public:
	bool Init(void);
	bool Update(void);
	bool Release(void);

	//ヒント画像の描画
	void SlideDraw(void);
	void LightDraw(void);
	void MatchDraw(void);

	bool MatchFlag(void);
	void InventoryDraw(void);
	bool ReturnFlag(void);


private:

	//画像格納変数
	int slideTips;	//ヒント１
	int lightTips;	//ヒント２
	int matchTips;	//ヒント１と２を合わせた画像

	//ヒントを手に入れるためのフラグ
	bool slideFlag;	
	bool lightFlag;
	bool matchFlag;

	int count;
	int font;
};

