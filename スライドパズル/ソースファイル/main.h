//#pragma once

//�萔��`
#define SCREEN_SIZE_X 640
#define SCREEN_SIZE_Y 480

class XY  //���W�ƃ}�X�l
{
public:
	int x;
	int y;
	int masu;
};

void Pattan(int num);//	����
void Move(int pase);//�s�[�X�̈ړ�
bool Check(int x, int y, int size);//�J�[�\���̃`�F�b�N

enum class GAMEMODE
{
	PUZZLE,
	LIGHT
};
