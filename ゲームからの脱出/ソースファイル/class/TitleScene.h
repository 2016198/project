#pragma once
class TitleScene
{
public:
	bool Init(void);
	bool Update(void);
	void Draw(void);
	bool Release(void);

private:
	int image_;	//”wŒi‰æ‘œŠi”[—p
	int count_;
	int font_;	//ƒtƒHƒ“ƒgî•ñŠi”[—p
};
