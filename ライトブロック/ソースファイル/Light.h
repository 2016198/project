#include "main.h"
#pragma once

//�萔
#define P 9			//�s�[�X�̐�
#define SIZE 50		//�s�[�X�̑傫��

class Vec  //���W
{
public:
	int x;
	int y;
};

class Light
{
private:
	//�ϐ�
	Vec masu[P];		//�}�X�̍��W
	Vec mouse;			//�}�E�X�̍��W
	int gameCnt = 0;	//�Q�[���J�E���g
	int clear;			//�N���A����
	bool Chach[P];		//�J�[�\�����G��Ă��邩
	int Light[P];		//�����Ă��邩�ǂ���
	unsigned int color[P];//�F

	void Pattan(int pase);				//����p�^�[��
	bool Check(int x, int y, int size);	//�J�[�\���̃`�F�b�N

public:
	bool Init(void);
	void UpDate(void);
	void Draw(void);
	bool Release(void);
};

