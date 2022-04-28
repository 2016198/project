#pragma once

class Tips
{
public:
	bool Init(void);
	bool Update(void);
	bool Release(void);

	//ƒqƒ“ƒg‰æ‘œ‚Ì•`‰æ
	void SlideDraw(void);
	void LightDraw(void);
	void MatchDraw(void);

	bool MatchFlag(void);
	void InventoryDraw(void);
	bool ReturnFlag(void);


private:

	//‰æ‘œŠi”[•Ï”
	int slideTips;	//ƒqƒ“ƒg‚P
	int lightTips;	//ƒqƒ“ƒg‚Q
	int matchTips;	//ƒqƒ“ƒg‚P‚Æ‚Q‚ğ‡‚í‚¹‚½‰æ‘œ

	//ƒqƒ“ƒg‚ğè‚É“ü‚ê‚é‚½‚ß‚Ìƒtƒ‰ƒO
	bool slideFlag;	
	bool lightFlag;
	bool matchFlag;

	int count;
	int font;
};

