#pragma once
#include "Vector2.h"
#include "GameCommon.h"

//�萔��`
#define ITEM_IMAGE_COUNT 4     //�A�C�e���̎�ނ̐�
class GameScene;			   //�e�̃C���X�^���X

class Item
{
private:
	Vector2 mPos;			//���W����
	GameScene *mParent;		//�e�̃C���X�^���X
	int mImage[2];			//�O���t�B�b�N�n���h��
	int mAnimCnt;			//�A�j���J�E���g
	bool mAlive;			//�o�����Ă��邩�ǂ���
	Vector2 mOffset;        //�I�t�Z�b�g�̍��W
	Vector2 mSizeOffset;    //�L�����N�^�[�̃I�t�Z�b�g�T�C�Y
	Vector2 mSize;          //�L�����N�^�[�̉摜�̃T�C�Y
public:
	bool Init(GameScene* parent);		//�C���X�^���X�̏���������
	void UpDate(Vector2 pos);		//�C���X�^���X�̍X�V����
	void Draw(void);		//�C���X�^���X�̕`�揈��
	bool Release(void);		//�C���X�^���X�̊J������
	void SetItem(Vector2 targetPos); //�A�C�e���̃Z�b�g
	bool IsAlive(void);		//�A�C�e�����o�����Ă邩�ǂ���
	void Destroy(void); //�A�C�e�����o�����Ă邩�ǂ���
	Vector2 GetSize(void);  //�摜�̃T�C�Y��Ԃ�
	Vector2 GetPos(void);   //���W��Ԃ�
};
