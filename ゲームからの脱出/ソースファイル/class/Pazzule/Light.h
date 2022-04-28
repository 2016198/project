#pragma once
#include "../GameCommon.h"
#include "../Vector2.h"

//�萔
static const int P = 9;			//�s�[�X�̐�
#define SIZE 50		//�s�[�X�̑傫��


class Light
{
private:
	//�ϐ�
	Vector2 masu[P];		//�}�X�̍��W
	Vector2 mouse;			//�}�E�X�̍��W
	int gameCnt = 0;	//�Q�[���J�E���g
	int clear;			//�N���A����
	bool Chach[P];		//�J�[�\�����G��Ă��邩
	int Light[P];		//�����Ă��邩�ǂ���
	unsigned int color[P];//�F

	void Pattan(int pase);				//����p�^�[��
	bool Check(int x, int y, int size);	//�J�[�\���̃`�F�b�N

	bool clearFlag_;
	bool backFlag;

	int font_;

public:
	bool Init(void);
	void Update(void);
	void Draw(void);
	bool Release(void);
	bool ReturnFlag(void);

	//��������ɖ߂�
	bool Back(void);

};

