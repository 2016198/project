#include <DxLib.h>
#include "Light.h"
#include "../KeyCheck.h"

bool Light::Init(void)
{
	font_ = CreateFontToHandle("HGSｺﾞｼｯｸE", 60, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 4);

	for (int d = 0; d < P; d++)
	{
		Light[d] = 0;
		color[d] = GetColor(100, 100, 100);
		masu[d].x = 100 * (d % 3 + 1);
		masu[d].y = 100 * (d / 3 + 1);
	}
	clear = 0;
	clearFlag_ = false;
	backFlag = false;
	return true;
}

void Light::Update(void)
{
	GetMousePoint(&mouse.x, &mouse.y);
	gameCnt++;
	if (keyTrgDown[MOUSE_RIGHT])//リセット処理
	{
		for (int d = 0; d < P; d++)
		{
			Light[d] = 0;
		}
	}
	for (int p = 0; p < P; p++)
	{
		if (Check(masu[p].x, masu[p].y, SIZE))
		{
			Chach[p] = true;
			if (keyTrgDown[MOUSE_LEFT])//左クリックしたときの処理
			{
				Pattan(p);
			}
		}
		else
		{
			Chach[p] = false;
		}
	}
	//if (keyTrgDown[MOUSE_MIDDLE])//デバッグモード
	//{
	//	for (int p = 0; p < P; p++)
	//	{
	//		Light[p] = 1;
	//	}
	//}
	for (int t = 0; t < P; t++)//クリアチェック
	{
		if (Light[t] % 2 == 1)
		{
			clear++;
		}
		else
		{
			clear = 0;
			break;
		}
	}

	if (keyTrgDown[KEY_P1_X])
	{
		backFlag = true;
	}
}

void Light::Draw(void)
{
	DrawBox(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, GetColor(0, 0, 255), true);

	for (int d = 0; d < P; d++)
	{
		if (Light[d] % 2 == 1)
		{
			color[d] = GetColor(255, 255, 255);
		}
		else
		{
			color[d] = GetColor(100, 100, 100);
		}
		if (Chach[d] == true)
		{
			DrawBox(masu[d].x - 5, masu[d].y - 5, masu[d].x + SIZE + 5, masu[d].y + SIZE + 5, color[d], true);
		}
		DrawBox(masu[d].x, masu[d].y, masu[d].x + SIZE, masu[d].y + SIZE, color[d], true);
		DrawFormatString(masu[d].x + 20, masu[d].y + 20, GetColor(0, 0, 0), "%d", d + 1);
	}
	if ((gameCnt / 30) % 2 == 0)
	{
		if (!clearFlag_)
		{
			DrawExtendString(220, 0, 2.0f, 2.0f, "マウスで操作", GetColor(0, 0, 0));
			DrawExtendString(200, 400, 1.5f, 1.5f, "右クリックでリセット", GetColor(0, 0, 0));
			DrawExtendString(250, 424, 1.5f, 1.5f, "Xキーで戻る", 0x000000);
		}
		else
		{
			DrawExtendString(200, 400, 1.5f, 1.5f, "Spaceキーで戻る", GetColor(0, 0, 0));
		}
	}

	//DrawString(0, 80, "ホイールクリックでデバッグモード", GetColor(255, 255, 255));

	if (clear == P)//クリアしたときの処理
	{
		DrawStringToHandle(100, 200, "ゲームクリア―", 0xffffff, font_);
		clear = 0;
		clearFlag_ = true;
	}
}

bool Light::Release(void)
{
	return true;
}

bool Light::ReturnFlag(void)
{
	if (clearFlag_)
	{
		backFlag = false;
		return true;
	}
	return false;
}

bool Light::Back(void)
{
	if (backFlag)
	{
		backFlag = false;
		return true;
	}
	return false;
}

void Light::Pattan(int pase)
{
	Light[pase]++;
	switch (pase)
	{
	case 0:
		Light[1]++;
		Light[3]++;
		break;
	case 1:
		Light[0]++;
		Light[2]++;
		Light[4]++;
		break;
	case 2:
		Light[1]++;
		Light[5]++;
		break;
	case 3:
		Light[0]++;
		Light[4]++;
		Light[6]++;
		break;
	case 4:
		Light[5]++;
		Light[3]++;
		Light[1]++;
		Light[7]++;
		break;
	case 5:
		Light[8]++;
		Light[2]++;
		Light[4]++;
		break;
	case 6:
		Light[7]++;
		Light[3]++;
		break;
	case 7:
		Light[4]++;
		Light[8]++;
		Light[6]++;
		break;
	case 8:
		Light[5]++;
		Light[7]++;
		break;
	default:
		break;
	}
}

bool Light::Check(int x, int y, int size)
{
	if (x <= mouse.x &&
		x + size >= mouse.x &&
		y <= mouse.y &&
		y + size >= mouse.y)
	{
		return true;
	}
	return false;
}
