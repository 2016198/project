#include <DxLib.h>
#include <time.h>
#include "Slide.h"
#include "../GameScene.h"
#include "../GameCommon.h"
#include "../KeyCheck.h"
#include "../../_debug/_DebugDispOut.h"
#include "../../_debug/_DebugConOut.h"

bool Slide::Init(void)
{
	clearFlag_ = false;
	backFlag = false;
	font_ = CreateFontToHandle("HGSｺﾞｼｯｸE", 60, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 4);
	srand((unsigned int)time(NULL));
	KeyInit();
	cnt = 0;
	for (int d = 0; d < P + 1; d++)
	{
		masu[d].x = 100 * (d % 3 + 1);
		masu[d].y = 100 * (d / 3 + 1);
		masu[d].masu = d;
		Random[d].y = d;
		Random[d].masu = d;
	}
	num_ = GetRand(3);	//乱数
	Pattan(num_);

	for (int e = 0; e < P + 1; e++)
	{
		for (int g = P; g > e; g--)
		{
			if (Random[g].x < Random[g - 1].x)
			{
				XY wk = Random[g];
				Random[g] = Random[g - 1];
				Random[g - 1] = wk;
			}
		}
	}

	for (int d = 0; d < P; d++)
	{
		p[d] = masu[Random[d].y];
		Chach[d] = false;
	}

	emptyMasu = Random[P].y;
	return true;
}

void Slide::Update(void)
{
	_dbgStartDraw();
	//メイン処理
	GetMousePoint(&X, &Y);
	gameCnt++;

	if (cnt < 8)
	{
		for (int r = 0; r < P; r++)
		{
			Move(r);
		}
	}
	if (keyTrgDown[MOUSE_RIGHT] && cnt < 8)
	{
		for (int d = 0; d < P + 1; d++)
		{
			Random[d].y = d;
			Random[d].masu = d;
			Chach[d] = false;
		}
		Pattan(num_);
		for (int e = 0; e < P + 1; e++)
		{
			for (int g = P; g > e; g--)
			{
				if (Random[g].x < Random[g - 1].x)
				{
					XY wk = Random[g];
					Random[g] = Random[g - 1];
					Random[g - 1] = wk;
				}
			}
		}
		for (int d = 0; d < P; d++)
		{
			p[d] = masu[Random[d].y];
		}

		emptyMasu = Random[P].y;
	}

	//デバッグモード
	//if (keyTrgDown[MOUSE_MIDDLE] && cnt < 8)
	//{
	//	for (int t = 0; t < P; t++) {
	//		p[t].x = 100 * (t % 3 + 1);
	//		p[t].y = 100 * (t / 3 + 1);
	//		p[t].masu = t;
	//	}
	//	emptyMasu = 8;
	//}

	if (emptyMasu == 8)
	{
		for (int w = 0; w < P - 2; w++)
		{
			if (p[w].masu == w)
			{
				cnt++;
			}
			else
			{
				cnt = 0;
				break;
			}
		}
		if (p[6].masu == 6 && p[7].masu == 7)
		{
			cnt += 2;
		}
		else if (p[6].masu == 7 && p[7].masu == 6)
		{
			cnt += 2;
		}
		else
		{
			cnt = 0;
		}
	}

	if (keyTrgDown[KEY_P1_X])
	{
		backFlag = true;
	}
}

void Slide::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);			//描画する画面を裏の画面に設定
	ClearDrawScreen();						//描画する画面の内容を消去
	CheckKeyList();
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(0, 0, 255), true);
	for (int d = 0; d < P; d++)
	{
		if (Chach[d] == true)
		{
			DrawBox(p[d].x - 5, p[d].y - 5, p[d].x + SIZE + 5, p[d].y + SIZE + 5, GetColor(255, 255, 255), true);
		}
		DrawBox(p[d].x, p[d].y, p[d].x + SIZE, p[d].y + SIZE, GetColor(255, 255, 255), true);
		DrawFormatString(p[d].x + 20, p[d].y + 20, GetColor(0, 0, 0), "%d", d + 1);
	}

	if (cnt >= 8)
	{
		DrawBox(masu[P].x, masu[P].y, masu[P].x + SIZE, masu[P].y + SIZE, GetColor(255, 255, 255), true);
		DrawFormatString(masu[P].x + 20, masu[P].y + 20, GetColor(0, 0, 0), "%d", P + 1);
		DrawStringToHandle(100, 200, "ゲームクリア―", 0xffffff,font_);
		clearFlag_ = true;
	}
	if ((gameCnt / 20) % 2 == 0)
	{
		if (!clearFlag_)
		{
			DrawExtendString(220, 0, 2.0f, 2.0f, "マウスで操作", GetColor(0, 0, 0));
			DrawExtendString(200, 400, 1.5f, 1.5f, "右クリックでリセット", GetColor(0, 0, 0));
			DrawExtendString(250, 424, 1.5f, 1.5f, "Xキーで戻る", 0x000000);

			//デバッグ用
			//DrawExtendString(200, 400, 1.5f, 1.5f, "\nホイールクリックでクリアー", GetColor(0, 0, 0));
		}
		else
		{
			DrawExtendString(200, 400, 1.5f, 1.5f, "Spaceキーで戻る", 0x000000);
		}
	}
	_dbgAddDraw();
	ScreenFlip();	//裏の画面を表の画面に瞬間コピー
}

bool Slide::ReturnFlag(void)
{
	if (clearFlag_)
	{
		backFlag = false;
		return true;
	}
	return false;
}

bool Slide::Back(void)
{
	if (backFlag)
	{
		backFlag = false;
		return true;
	}
	return false;
}

void Slide::Pattan(int num)
{
	switch (num)
	{
	case 0:
		//8は空マス
		//引かれる数字(左)がピースの添え字
		Random[0].x = 8;
		Random[1].x = 3 - 1;
		Random[2].x = 1 - 1;
		Random[3].x = 4 - 1;
		Random[4].x = 8 - 1;
		Random[5].x = 7 - 1;
		Random[6].x = 2 - 1;
		Random[7].x = 5 - 1;
		Random[8].x = 6 - 1;
		break;
	case 1:
		Random[0].x = 8 - 1;
		Random[1].x = 4 - 1;
		Random[2].x = 5 - 1;
		Random[3].x = 3 - 1;
		Random[4].x = 2 - 1;
		Random[5].x = 8;
		Random[6].x = 6 - 1;
		Random[7].x = 7 - 1;
		Random[8].x = 1 - 1;
		break;
	case 2:
		Random[0].x = 7 - 1;
		Random[1].x = 4 - 1;
		Random[2].x = 3 - 1;
		Random[3].x = 6 - 1;
		Random[4].x = 1 - 1;
		Random[5].x = 2 - 1;
		Random[6].x = 5 - 1;
		Random[7].x = 8 - 1;
		Random[8].x = 8;
		break;
	case 3:
		Random[0].x = 7 - 1;
		Random[1].x = 1 - 1;
		Random[2].x = 2 - 1;
		Random[3].x = 8 - 1;
		Random[4].x = 5 - 1;
		Random[5].x = 3 - 1;
		Random[6].x = 4 - 1;
		Random[7].x = 8;
		Random[8].x = 6 - 1;
		break;
	}
}

void Slide::Move(int pase)
{
	switch (emptyMasu)
	{
	case 0:
		if (p[pase].masu == 1 || p[pase].masu == 3)
		{
			if (Check(p[pase].x, p[pase].y, SIZE))
			{
				if (keyTrgDown[MOUSE_LEFT])
				{
					int empty = p[pase].masu;
					p[pase] = masu[emptyMasu];
					emptyMasu = empty;
					Chach[pase] = false;
				}
				else
				{
					Chach[pase] = true;
				}
			}
			else
			{
				Chach[pase] = false;
			}
		}
		break;
	case 1:
		if (p[pase].masu == 0 || p[pase].masu == 2 || p[pase].masu == 4)
		{
			if (Check(p[pase].x, p[pase].y, SIZE))
			{
				if (keyTrgDown[MOUSE_LEFT])
				{
					int empty = p[pase].masu;
					p[pase] = masu[emptyMasu];
					emptyMasu = empty;
					Chach[pase] = false;
				}
				else
				{
					Chach[pase] = true;
				}
			}
			else
			{
				Chach[pase] = false;
			}
		}
		break;
	case 2:
		if (p[pase].masu == 1 || p[pase].masu == 5)
		{
			if (Check(p[pase].x, p[pase].y, SIZE))
			{
				if (keyTrgDown[MOUSE_LEFT])
				{
					int empty = p[pase].masu;
					p[pase] = masu[emptyMasu];
					Chach[pase] = false;
					emptyMasu = empty;
				}
				else
				{
					Chach[pase] = true;
				}
			}
			else
			{
				Chach[pase] = false;
			}
		}
		break;
	case 3:
		if (p[pase].masu == 0 || p[pase].masu == 6 || p[pase].masu == 4)
		{
			if (Check(p[pase].x, p[pase].y, SIZE))
			{
				if (keyTrgDown[MOUSE_LEFT])
				{
					int empty = p[pase].masu;
					p[pase] = masu[emptyMasu];
					emptyMasu = empty;
					Chach[pase] = false;
				}
				else
				{
					Chach[pase] = true;
				}
			}
			else
			{
				Chach[pase] = false;
			}
		}
		break;
	case 4:
		if (p[pase].masu == 1 || p[pase].masu == 3 || p[pase].masu == 5 || p[pase].masu == 7)
		{
			if (Check(p[pase].x, p[pase].y, SIZE))
			{
				if (keyTrgDown[MOUSE_LEFT])
				{
					int empty = p[pase].masu;
					p[pase] = masu[emptyMasu];
					emptyMasu = empty;
					Chach[pase] = false;
				}
				else
				{
					Chach[pase] = true;
				}
			}
			else
			{
				Chach[pase] = false;
			}
		}
		break;
	case 5:
		if (p[pase].masu == 2 || p[pase].masu == 4 || p[pase].masu == 8)
		{
			if (Check(p[pase].x, p[pase].y, SIZE))
			{
				if (keyTrgDown[MOUSE_LEFT])
				{
					int empty = p[pase].masu;
					p[pase] = masu[emptyMasu];
					emptyMasu = empty;
					Chach[pase] = false;
				}
				else
				{
					Chach[pase] = true;
				}
			}
			else
			{
				Chach[pase] = false;
			}
		}
		break;
	case 6:
		if (p[pase].masu == 3 || p[pase].masu == 7)
		{
			if (Check(p[pase].x, p[pase].y, SIZE))
			{
				if (keyTrgDown[MOUSE_LEFT])
				{
					int empty = p[pase].masu;
					p[pase] = masu[emptyMasu];
					emptyMasu = empty;
					Chach[pase] = false;
				}
				else
				{
					Chach[pase] = true;
				}
			}
			else
			{
				Chach[pase] = false;
			}
		}
		break;
	case 7:
		if (p[pase].masu == 6 || p[pase].masu == 8 || p[pase].masu == 4)
		{
			if (Check(p[pase].x, p[pase].y, SIZE))
			{
				if (keyTrgDown[MOUSE_LEFT])
				{
					int empty = p[pase].masu;
					p[pase] = masu[emptyMasu];
					emptyMasu = empty;
					Chach[pase] = false;
				}
				else
				{
					Chach[pase] = true;
				}
			}
			else
			{
				Chach[pase] = false;
			}
		}
		break;
	case 8:
		if (p[pase].masu == 5 || p[pase].masu == 7)
		{
			if (Check(p[pase].x, p[pase].y, SIZE))
			{
				if (keyTrgDown[MOUSE_LEFT])
				{
					int empty = p[pase].masu;
					p[pase] = masu[emptyMasu];
					emptyMasu = empty;
					Chach[pase] = false;
				}
				else
				{
					Chach[pase] = true;
				}
			}
			else
			{
				Chach[pase] = false;
			}
		}
		break;
	}
}

bool Slide::Check(int x, int y, int size)
{
	if (x <= X &&
		x + size >= X &&
		y <= Y &&
		y + size >= Y)
	{
		return true;
	}
	return false;
}
