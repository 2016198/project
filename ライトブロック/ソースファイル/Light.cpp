#include <DxLib.h>
#include "Light.h"
#include "KeyCheck.h"

bool Light::Init(void)
{
	for (int d = 0; d < P; d++)
	{
		Light[d] = 0;
		color[d] = GetColor(100, 100, 100);
		masu[d].x = 100 * (d % 3 + 1);
		masu[d].y = 100 * (d / 3 + 1);
	}
	clear = 0;
	return true;
}

void Light::UpDate(void)
{
	GetMousePoint(&mouse.x, &mouse.y);
	gameCnt++;
	if (keyTrgDown[MOUSE_RIGHT])//���Z�b�g����
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
			if (keyTrgDown[MOUSE_LEFT])//���N���b�N�����Ƃ��̏���
			{
				Pattan(p);
			}
		}
		else
		{
			Chach[p] = false;
		}
	}
	if (keyTrgDown[MOUSE_MIDDLE])//�Ńo�b�N���[�h
	{
		for (int p = 0; p < P; p++)
		{
			Light[p] = 1;
		}
	}
	for (int t = 0; t < P; t++)//�N���A�`�F�b�N
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
		DrawExtendString(220, 0, 2.0f, 2.0f, "�}�E�X�ő���", GetColor(0, 0, 0));
		DrawExtendString(200, 400, 1.5f, 1.5f, "�E�N���b�N�Ń��Z�b�g", GetColor(0, 0, 0));
		
	}
	DrawString(0, 80, "�z�C�[���N���b�N�Ńf�o�b�N���[�h", GetColor(255, 255, 255));
	if (clear == P)//�N���A�����Ƃ��̏���
	{
		DrawString(0, 0, "\n�Q�[���N���A", 0x00FF00);
		clear = 0;
	}
}

bool Light::Release(void)
{
	return true;
}

void Light::Pattan(int pase) //����p�^�[��
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

bool Light::Check(int x, int y, int size)//�J�[�\���̃`�F�b�N
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

