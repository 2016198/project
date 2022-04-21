#pragma once
#include "Ticket.h"

class EleMoney :
    public Ticket
{

public:

	EleMoney();							//コンストラクタ
	~EleMoney();						//デストラクタ

	bool Init(void) override;			//初期化処理
	void UpDate(void) override;			//更新処理
	void Draw(void) override;			//描画処理

private:

	bool ticketConditions(int num);		//チケット購入できる枚数の表示

	const int ELEMONEY = 1000;			//電子マネーの残高
	int purchase_;						//購入額

	const char* MSG_LOG[2] = {			//出力メッセージ
		"取引成功。支払額 → %d円",
		"取引失敗。残高が不足しています"
	};
};

