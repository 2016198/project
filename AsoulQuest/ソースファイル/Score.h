//#pragma once
#include "Vector2.h"
#include "GameCommon.h"

class Score
{
private:
	Vector2 mPos;				     //���W����
	Vector2 mOffset;                 //�I�t�Z�b�g���W����
	int mLife;                       //�X�R�A�̕\������
	int mType;                       //�X�R�A�̎��
	int mFont;                       //�X�R�A�����炷
	unsigned int mColor;             //�F�̃A�h���X�ϐ�
	const int mPoint[ENEMY_TYPE_MAX + 1] //�G���Ƃ̓_���@����ԏ������_���͓G�ɒe�𓖂Ă����̃|�C���g
	{
		20,30,40,50,60,500,10
	};
	int mEnemyLife;                   //�G�̐����m�F
public:
	bool Init(void);	//�C���X�^���X�̐���
	void UpDate(void);	//�C���X�^���X�̍X�V
	void Draw(Vector2 pos);	//�C���X�^���X�̕`��
	bool Release(void); //�C���X�^���X�̊J��
	int AddScore(int enemyType, Vector2 targetPos, int enemyLife);//�X�R�A�̉��Z
	bool IsAlive(void);       //�X�R�A���\������Ă���
};
