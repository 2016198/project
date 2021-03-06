#include <DxLib.h>
#include <time.h>
#include <cmath>
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"
#include "Lock.h"

bool Lock::CheckBox(int x, int y, int sizeX, int sizeY)
{
	if (x <= mouse.x &&
		x + sizeX >= mouse.x &&
		y <= mouse.y &&
		y + sizeY >= mouse.y)
	{
		return true;
	}
	return false;
}

bool Lock::CheckCircle(vector2 sub, int size)
{
	auto subH = hypot(sub.x, sub.y);
	return (int)(subH) <= size;
}

bool Lock::PassCheck(void)
{
	if (pass.size() == pass_size)
	{
		int u = 0;
		int k = 1;
		for (auto const p : pass)
		{
			k *= (int)(p == word[u]);
			if (k == 0)
			{
				return false;
			}
			u++;
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool Lock::Init()
{
	cake = LoadGraph("cake.png");
	time = 0;
	error = 0;
	canOpen = false;
	open = false;
	for (int r = 0; r < 12; r++)
	{
		color[r] = 0xffffff;
	}
	return true;
}

void Lock::UpDate()
{
	check = false;
	GetMousePoint(&mouse.x, &mouse.y);
	if (CheckCircle(vector2{ 200,220 } - mouse, 20))
	{
		if (keyTrgDown[MOUSE_LEFT])
		{
			time = 60;
		}
	}

	if (canOpen == false && error <= 0)
	{
		for (int r = 0; r < 12; r++)
		{
			if (CheckBox(pos.x + ((r % 3) * (size + 20)), pos.y + ((r / 3) * (size + 20)), size, size))
			{
				color[r] = 0xffffff;
				if (keyTrgDown[MOUSE_LEFT])
				{
					switch (r + 1)
					{
					case 10:
						pass.clear();//パスワードのリセット
						break;
					case 11:
						if (!(pass.size() >= pass_max_size))
						{
							pass.push_back(0);//syamu_game
						}
						break;
					case 12:
						if (pass.size() > 0)
						{
							check = true;//パスワードのチェック
						}
						break;
					default:
						if (!(pass.size() >= pass_max_size))
						{
							pass.push_back(r + 1);
						}
						break;
					}
				}
			}
			else
			{
				color[r] = 0x999999;
			}
		}
	}

	if (check)
	{
		canOpen = PassCheck();
		pass.clear();
		if (!canOpen)
		{
			error = 60;
			color[11] = 0x999999;
		}
	}

	if (pass.size() <= 0)
	{
		color[11] = 0x0f0f0f;
		color[9] = 0x0f0f0f;
	}
	if (pass.size() >= pass_max_size)
	{
		for (int y = 0; y < 9; y++)
		{
			color[y] = 0x0f0f0f;
		}
		color[10] = 0x0f0f0f;
	}
}

void Lock::Draw()
{
	DrawBox(150, 50, 500, 400, 0xffffff, 0);
	DrawCircle(200, 220, 20, 0xffffff, 0);
	//DrawFormatString(0, 0, 0xffffff, "%d;;;;%d", mouse.x, mouse.y);
	if (time > 0)
	{
		canOpen ? DrawString(0, 20, "開いた！", 0xffffff), open = true : DrawString(0, 20, "開かない", 0xffffff);
		time--;
	}

	for (int r = 0; r < 12; r++)
	{
		DrawBox(pos.x + ((r % 3) * (size + 20)), pos.y + ((r / 3) * (size + 20)),
			pos.x + size + ((r % 3) * (size + 20)), pos.y + size + ((r / 3) * (size + 20)),
			color[r], 0);
		DrawExtendFormatString(290 + ((r % 3) * 60) + 13, 155 + ((r / 3) * 60) + 5, 2.0, 2.0, color[r], "%s", num[r]);
	}
	int q = 0;
	for (const auto p : pass)
	{
		DrawFormatString(220 + (q * 10), 100, 0xffffff, "%d", p);
		q++;
	}
	if (canOpen)
	{
		DrawString(220, 100, "ロック解除！", 0x00ff00);
	}
	if (error > 0)
	{
		DrawString(220, 100, "エラー！", 0xff0000);
		error--;
	}
	DrawBox(218, 97, 420, 118, 0xffffff, 0);
	DrawQuadrangle(220, 10, 570, 10, 500, 50, 150, 50, 0xffffff, 0);
	DrawLine(570, 10, 570, 360, 0xffffff);
	DrawLine(500, 400, 570, 360, 0xffffff);
	if (open == true)
	{
		DrawBox(151, 51, 499, 399, 0, true);
		DrawExtendGraph(151, 51, 499, 399, cake, true);
		DrawBox(641, 51, 500, 399, 0xffffff, 0);
		DrawBox(639, 51, 501, 399, 0x000000, 1);
		time = 800;
	}
}

bool Lock::Release()
{
	DeleteGraph(cake);
	return true;
}

vector2 operator+(vector2 a, vector2 b)
{
	return vector2{ a.x + b.x, a.y + b.y };
}

vector2 operator-(vector2 a, vector2 b)
{
	return vector2{ a.x - b.x, a.y - b.y };
}

vector2 operator*(vector2 a, vector2 b)
{
	return vector2{ a.x * b.x, a.y * b.y };
}

vector2 operator/(vector2 a, vector2 b)
{
	return vector2{ a.x / b.x, a.y / b.y };
}
