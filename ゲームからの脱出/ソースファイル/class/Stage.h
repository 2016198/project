#pragma once
#include "Vector2.h"

//�萔
constexpr int CHIP_IMAGE_MAX = 384;	//�}�b�v�`�b�v�̐�
constexpr int MAP_X = 18;			//�}�b�v�̉��T�C�Y
constexpr int MAP_Y = 13;			//�}�b�v�̏c�T�C�Y

class Stage
{
public:

	int mMapImage[CHIP_IMAGE_MAX];	//MapChip�̊i�[�̈�

	//�G�t�F�N�g�̊i�[�̈�
	int pazzuleImage[3][3];
	int escapeImage[3][3];

	int animCnt;

	bool Init(void);			
	bool Update(void);			
	void PassDraw(void);			
	void NotPassDraw(void);			
	bool Release(void);			

	int GetMapChip(Vector2 pos);
	int GetEventChip(Vector2 pos);

	//�G�t�F�N�g�̕`��
	void EventDraw(Vector2 pos);
	void EscapeDraw(Vector2 pos);

private:
	Vector2 mOffset;		//�}�b�v�̃I�t�Z�b�g

	int image;
};
