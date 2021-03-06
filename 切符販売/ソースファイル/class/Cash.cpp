#include <DxLib.h>
#include "Cash.h"

Cash::Cash() : Ticket()//コンストラクタ
{
	scene_ = SCENE_ID::CASH;
	color_.resize(CASH_COUNT + 6U);
	Init();
	UpDate();
}

Cash::~Cash()//デストラクタ
{
}

bool Cash::Init(void)//初期化処理
{
	for (int r = 0; r < CASH_COUNT; r++)
	{
		haveCash_[CASH_TYPE[r]] = CASH_HAVE[r];
		inputCash_[CASH_TYPE[r]] = 0;
		changeCash_[CASH_TYPE[r]] = 0;
	}

	for (auto& c : color_)
	{
		c = WHITE;
	}

	pay_ = 0;
	changeAdd_ = 0;
	ticketPrice_ = 130;

	return false;
}

void Cash::UpDate(void)//更新処理
{
	GetMousePoint(&x_, &y_);
	mouse_[0] = GetMouseInput() & MOUSE_INPUT_LEFT;

	//戻るボタン
	if (HitBack())
	{
		colorB_ = YELLOW;
		if (MouseOneInput())
		{
			scene_ = SCENE_ID::SELECT;
		}
	}
	else
	{
		colorB_ = WHITE;
	}

	if (IsBuy_ == false)
	{

		//現金選択
		for (int p = 0; p < CASH_COUNT; p++)
		{
			if (haveCash_[CASH_TYPE[p].c_str()] > 0)
			{
				color_[p] = WHITE;
			}
			else
			{
				color_[p] = GRAY;
			}

			width_ = GetDrawFormatStringWidth(
				"%s円 → %d枚",
				CASH_TYPE[p].c_str(),
				haveCash_[CASH_TYPE[p].c_str()]);

			if (x_ > 28 &&
				y_ > 50 * p + 58 &&
				x_ < 31 + width_ &&
				y_ < 50 * p + 77)
			{
				if (haveCash_[CASH_TYPE[p].c_str()] > 0)
				{
					color_[p] = YELLOW;
				}
				else
				{
					color_[p] = RED;
				}

				if (MouseOneInput())
				{
					if (haveCash_[CASH_TYPE[p].c_str()] > 0)
					{
						pay_ += atoi(CASH_TYPE[p].c_str());
						haveCash_[CASH_TYPE[p].c_str()]--;
					}
				}
			}
		}

		//挿入された現金
		for (int p = 0; p < CASH_COUNT; p++)
		{
			inputCash_[CASH_TYPE[p].c_str()] = CASH_HAVE[p] - haveCash_[CASH_TYPE[p].c_str()];
		}

		//切符の枚数選択
		for (int t = 0; t < 4; t++)
		{
			if (ticketConditions(t))
			{
				color_[CASH_COUNT + t] = WHITE;
			}
			else
			{
				color_[CASH_COUNT + t] = GRAY;
			}

			if (190 + t % 2 * 60 < x_ &&
				100 + t / 2 * 107 < y_ &&
				220 + t % 2 * 60 > x_ &&
				130 + t / 2 * 107 > y_)
			{
				if (ticketConditions(t))
				{
					color_[CASH_COUNT + t] = YELLOW;
				}
				else
				{
					color_[CASH_COUNT + t] = RED;
				}

				if (MouseOneInput())
				{
					if (ticketConditions(t))
					{
						ticketNum_ += atoi(BUY_TICKET[t].c_str());
					}
				}
			}

		}

		if (ticketNum_ <= 0)
		{
			ticketNum_ = 0;
			color_[CASH_COUNT + 4U] = GRAY;
		}
		else
		{
			color_[CASH_COUNT + 4U] = WHITE;
		}

		//購入
		width_ = GetDrawExtendStringWidth(2.0, MSG_BUY, color_[CASH_COUNT + 4U].GetColorCode());
		if (203 < x_ && 248 < y_ &&
			205 + width_ > x_ && 283 > y_)
		{
			if (ticketNum_ <= 0)
			{
				color_[CASH_COUNT + 4U] = RED;
			}
			else
			{
				color_[CASH_COUNT + 4U] = YELLOW;
				if (MouseOneInput())
				{
					IsBuy_ = true;
					color_[CASH_COUNT + 4U] = CYAN;
				}
			}

		}

		//お釣り
		changeAdd_ = pay_ - ticketNum_ * ticketPrice_;
		int dir = changeAdd_;
		for (int y = CASH_COUNT - 1; y >= 0; y--)
		{
			if (dir == 0)
			{
				changeCash_[CASH_TYPE[y].c_str()] = 0;
			}
			changeCash_[CASH_TYPE[y].c_str()] = dir / atoi(CASH_TYPE[y].c_str());
			dir %= atoi(CASH_TYPE[y].c_str());
		}

	}
	else
	{
		if (x_ > 190 && y_ > 290 &&
			x_ < 297 && y_ < 324)
		{
			color_[CASH_COUNT + 5U] = YELLOW;
			if (MouseOneInput())
			{
				Init();
				IsBuy_ = false;
				ticketNum_ = 0;
				color_[7] = GRAY;
				color_[8] = GRAY;
			}
		}
		else
		{
			color_[CASH_COUNT + 5U] = WHITE;
		}
	}

	mouse_[1] = mouse_[0];
}

void Cash::Draw(void)//描画処理
{
	//所持している現金
	DrawString(30, 30, "所持金額", WHITE.GetColorCode());
	for (int p = 0; p < haveCash_.size(); p++)
	{
		DrawFormatString(
			30, 50 * p + 60,
			color_[p].GetColorCode(), "%s円 → %d枚",
			CASH_TYPE[p].c_str(),
			haveCash_[CASH_TYPE[p].c_str()]);

		width_ = GetDrawFormatStringWidth(
			"%s円 → %d枚",
			CASH_TYPE[p].c_str(),
			haveCash_[CASH_TYPE[p].c_str()]);

		DrawBox(
			28, 50 * p + 58,
			31 + width_, 50 * p + 77,
			color_[p].GetColorCode(), false
		);
	}

	//挿入した現金
	DrawString(350, 30, "挿入金額", WHITE.GetColorCode());
	for (int p = 0; p < haveCash_.size(); p++)
	{
		DrawFormatString(
			350, 50 * p + 60,
			WHITE.GetColorCode(), "%s円 → %d枚",
			CASH_TYPE[p].c_str(),
			inputCash_[CASH_TYPE[p].c_str()]);

		width_ = GetDrawFormatStringWidth(
			"%s円 → %d枚",
			CASH_TYPE[p].c_str(),
			inputCash_[CASH_TYPE[p].c_str()]);

		DrawBox(
			348, 50 * p + 58,
			351 + width_, 50 * p + 77,
			WHITE.GetColorCode(), false
		);
	}

	//おつり
	if (IsBuy_ == true)
	{
		DrawFormatString(490, 30, WHITE.GetColorCode(), "お釣り → %d円", changeAdd_);
		for (int p = 0; p < haveCash_.size(); p++)
		{
			DrawFormatString(
				490, 50 * p + 60,
				WHITE.GetColorCode(), "%s円 → %d枚",
				CASH_TYPE[p].c_str(),
				changeCash_[CASH_TYPE[p]]);

			width_ = GetDrawFormatStringWidth(
				"%s円 → %d枚",
				CASH_TYPE[p].c_str(),
				changeCash_[CASH_TYPE[p]]);

			DrawBox(
				488, 50 * p + 58,
				491 + width_, 50 * p + 77,
				WHITE.GetColorCode(), false
			);
		}

		//リセット
		DrawExtendString(190, 292, 1.6, 2.0, "リセット", color_[CASH_COUNT + 5U].GetColorCode());
		DrawBox(190, 290, 297, 324, color_[CASH_COUNT + 5U].GetColorCode(), false);
	}

	//チケット枚数
	for (int t = 0; t < 4; t++)
	{
		DrawBox(
			190 + t % 2 * 60,
			100 + t / 2 * 107,
			220 + t % 2 * 60,
			130 + t / 2 * 107,
			color_[CASH_COUNT + t].GetColorCode(),
			false);
	}


	DrawString(197, 108, BUY_TICKET[0].c_str(), color_[CASH_COUNT].GetColorCode());
	DrawString(252, 108, BUY_TICKET[1].c_str(), color_[CASH_COUNT + 1U].GetColorCode());
	DrawString(197, 215, BUY_TICKET[2].c_str(), color_[CASH_COUNT + 2U].GetColorCode());
	DrawString(252, 215, BUY_TICKET[3].c_str(), color_[CASH_COUNT + 3U].GetColorCode());

	//その他
	DrawFormatString(170, 70, WHITE.GetColorCode(), "切手 → 1枚%d円", ticketPrice_);

	DrawFormatString(180, 140, WHITE.GetColorCode(), "挿入額 →  %d円", pay_);
	DrawFormatString(180, 160, WHITE.GetColorCode(), "枚数   →  %d枚", ticketNum_);
	DrawFormatString(180, 180, WHITE.GetColorCode(), "合計   →  %d円", ticketNum_ * ticketPrice_);

	//購入
	DrawExtendString(205, 250, 2.0, 2.0, MSG_BUY, color_[CASH_COUNT + 4U].GetColorCode());
	width_ = GetDrawExtendStringWidth(2.0, MSG_BUY, color_[CASH_COUNT + 4U].GetColorCode());
	DrawBox(203, 248, 205 + width_, 283, color_[CASH_COUNT + 4U].GetColorCode(), false);
}

bool Cash::ticketConditions(int num)//切符条件
{
	switch (num)
	{
	case 0:
		return (ticketNum_ + atoi(BUY_TICKET[0].c_str())) * ticketPrice_ <= pay_;
		break;
	case 1:
		return (ticketNum_ + atoi(BUY_TICKET[1].c_str())) * ticketPrice_ <= pay_;
	case 2:
	case 3:
		return ticketNum_ > 0;
		break;
	default:
		return false;
		break;
	}
}
