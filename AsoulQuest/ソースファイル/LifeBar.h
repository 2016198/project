#pragma once
#include "Vector2.h"
#include "GameCommon.h"
class GameScene;

//�萔��`
#define LIFE_ANIM_COUNT 4 //���C�t�o�[�̃A�j���̐�

class LifeBar {
private:
	Vector2 mPos;		  //���W����
	GameScene* mParent;   //�e�̃C���X�^���X�|�C���^�ϐ�
	Vector2 mSizeOffset;  //�L�����N�^�[�̃I�t�Z�b�g�T�C�Y
	Vector2 mOffset;      //�I�t�Z�b�g�̍��W
	int mType;            //�L�����N�^�[�̎��

public:
	bool init(GameScene* parent, int type);     //�C���X�^���X�̐���
	void UpDate(Vector2 pos);		  //�C���X�^���X�̍X�V
	void Draw(int life, Vector2 pos); //�C���X�^���X�̕`��
	bool Release(void);               //�C���X�^���X�̊J��
};
