#include <cmath>
#include <DxLib.h>
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "Water.h"
#include "KeyCheck.h"

bool Water::Init(void)//����������
{
	for (int b = 0; b < BUTTON_CNT; b++)
	{
		button[b].x = 450;
		button[b].y = 100 + 40 * b;
		button[b].canPush = true;
	}
	button[0].size = 0;
	button[1].size = 2;
	button[2].size = 6;
	button[3].size = 5;
	button[4].size = 4;
	button[5].size = 3;

	fontColor[10] = 0xff00ff;
	for (int l = 1; l < 10; l++) 
	{
		fontColor[l] = 0xffffff;
	}
	fontColor[0] = 0x666666;
	timer = 0;

	GetMousePoint(&mouse.x, &mouse.y);
	return true;
}

bool Water::UpDate(void)//�X�V����
{
	bool flag = false;	//���̃V�[���ւ̈ړ��p�Ґ�
	if (lock == false)
	{
		for (int c = 1; c < BUTTON_CNT; c++)
		{
			add ?//�v���X�H�}�C�i�X�H
				button[c].size + water > 10 ?//������H�����Ȃ��H
				button[c].canPush = false :
				button[c].canPush = true :
				button[c].size - water > 0 ?//������H�����Ȃ��H
				button[c].canPush = false :
				button[c].canPush = true;
			button[c].canPush ?//�F�`�F���W
				button[c].color = 0xffffff :
				button[c].color = 0x114514;
		}
		add ?//�v���X�H�}�C�i�X�H
			button[0].color = 0xaa0000 :
			button[0].color = 0x0000aa;
	}
	GetMousePoint(&mouse.x, &mouse.y);
	if (Check(250, 390 - memory, KEY_SIZE))
	{
		if (keyTrgDown[MOUSE_LEFT])
		{
			timer = 30;
		}
	}

	isGetKey = water == 10;
	flag = water == 10 && timer == 1;
	return flag;
}

void Water::Draw(void)//�`�揈��
{
	for (int w = 0; w < BUTTON_CNT; w++)
	{
		if (lock == false)
		{
			if (button[w].canPush)//�����邩�ǂ����`�F�b�N
			{
				if (Check(button[w].x, button[w].y, 15))//�}�E�X�J�[�\���`�F�b�N
				{
					DrawCircle(button[w].x, button[w].y, 20, button[w].color);
					if (keyTrgDown[MOUSE_LEFT])
					{
						w == 0 ?
							add = !add :
							add ?
							water += button[w].size :
							water -= button[w].size;	//���̑����F���炷
					}
				}
			}
		}

		if (w != 0)
		{
			DrawCircle(button[w].x, button[w].y, 15, button[w].color);
			DrawFormatString(button[w].x - 8, button[w].y - 8, 0x000000, "%d", button[w].size * 10);
		}
	}

	DrawCircle(button[0].x, button[0].y, 15, button[0].color);
	add ?
		DrawString(button[0].x - 4, button[0].y - 8, "+", 0x000000) ://�v���X�̎�
		DrawString(button[0].x - 4, button[0].y - 8, "-", 0x000000); //�}�C�i�X�̎�
	DrawLine(100, 70, 100, 400, 0xffff00, 5);
	DrawLine(400, 400, 100, 400, 0xffff00, 5);
	DrawLine(400, 400, 400, 70, 0xffff00, 5);
	//DrawFormatString(0, 0, 0xffffff, "%d %d", mouse.x, mouse.y);
	if (water * WATER_SIZE > memory)
	{
		memory += WATER_SIZE / 10;
		lock = true;
	}
	else
	{
		if (water * WATER_SIZE < memory)
		{
			memory -= WATER_SIZE / 10;
			lock = true;
		}
		else
		{
			lock = false;
		}
	}

	DrawBox(399, 399, 102, 390 - memory, 0x1111ff, 1);
	DrawCircle(250, 390 - memory - keyOffsetPos, KEY_SIZE, 0xff0000);//�J�M
	if (timer > 0)
	{
		isGetKey ?
			DrawString(0, 0, "�J�M���Q�b�g����", 0xffffff),
			keyOffsetPos += 6 :
			DrawString(0, 0, "�肪�͂��Ȃ�", 0xffffff);
		timer--;
	}
	int width;
	for (int p = 0; p <= 10; p++)
	{
		width = GetDrawFormatStringWidth("%d", p * 10);
		DrawFormatString(90 - width, 380 - p * WATER_SIZE , fontColor[p], "%d",p * 10);
	}
}

bool Water::Release(void)//�������
{
	return true;
}

int Water::Magnitude(int x, int y) const//�~�̓����蔻��
{
	return (int)(hypot(x, y));
}

bool Water::Check(int x, int y, int size)//�J�[�\���̃`�F�b�N
{
	/*if (x <= mouse.x &&
		x + size >= mouse.x &&
		y <= mouse.y &&
		y + size >= mouse.y)*/
	if (Magnitude(mouse.x - x, mouse.y - y) <= size)
	{
		return true;
	}
	return false;
}
