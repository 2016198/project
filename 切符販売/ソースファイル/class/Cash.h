#pragma once
#include <map>
#include "Ticket.h"

class Cash:
	public Ticket
{
public:

	Cash();								//コンストラクタ
	~Cash();							//デストラクタ

	bool Init(void) override;			//初期化処理
	void UpDate(void) override;			//更新処理
	void Draw(void) override;			//描画処理

private:
	bool ticketConditions(int num);							//チケット購入できる枚数の表示

	static constexpr size_t CASH_COUNT = 7U;				//現金の数

	const std::array<std::string, CASH_COUNT> CASH_TYPE = {	//現金の種類
		"10",
		"50",
		"100",
		"500",
		"1000",
		"5000",
		"10000"
	};

	const std::array<int, CASH_COUNT> CASH_HAVE = {			//初期に所持してる現金の枚数
		15,		//10円
		3,		//50円
		2,		//100円
		1,		//500円
		1,		//1000円
		1,		//5000円
		1		//10000円
	};

	std::map<std::string, int> haveCash_;			//所持している現金
	std::map<std::string, int> inputCash_;			//挿入した現金
	std::map<std::string, int> changeCash_;			//挿入した現金
	int changeAdd_;									//おつり
	int pay_;										//支払額
};

