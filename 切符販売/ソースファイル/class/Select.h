#pragma once
#include "Ticket.h"

class Select :
    public Ticket
{
public:

	Select();							//コンストラクタ
	~Select();							//デストラクタ

	bool Init(void) override;			//初期化処理
	void UpDate(void) override;			//更新処理
	void Draw(void) override;			//描画処理

private:

	const char* MSG_SELECT = "支払方法を選択してください";		//表示メッセージ

	const int SCREEN_SIZE_X = 640;								//画面サイズX
};

