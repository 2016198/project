#pragma once


class GameClearScene
{
public:
	bool Init(void);
	bool Update(void);
	void Draw(void);
	bool Release(void);

private:
	int image_;		//”wŒi‰æ‘œŠi”[—p
	int font_;		//ƒtƒHƒ“ƒgî•ñŠi”[—p
	int count_;

	bool flag_;
};