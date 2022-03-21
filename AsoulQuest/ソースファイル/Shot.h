#pragma once
#include "Vector2.h"
#include "GameCommon.h"
#include "CharOrder.h"
class GameScene;

//�萔��`
#define SHOT_IMAGE_COUNT 2     //�V���b�g�̃A�j���̐�

class Shot
{
private:                              //�����o�[�ϐ�
	GameScene* mParent;               //�e�̃C���X�^���X�̃|�C���^�ϐ�
	int mScreenSizeX;                 //��ʂ�X�T�C�Y
	int mScreenSizeY;                 //��ʂ�Y�T�C�Y
	Vector2 mOffset;                  //�I�t�Z�b�g�̍��W
	DIR mKeyDir;                      //�L�[�̐���
	DIR mMoveDir;                     //�L�����N�^�[�̌���
	Vector2 mPos;                     //�L�����N�^�[�̒n�}��̍��W
	Vector2 mSizeOffset;              //�L�����N�^�[�̃I�t�Z�b�g�T�C�Y
	Vector2 mSize;                    //�L�����N�^�[�̉摜�̃T�C�Y
	int mMoveSpeed;                   //�L�����N�^�[�̈ړ��X�s�[�h
	int mLife;                        //�L�����N�^�[�̗̑� 
	int mLifeMax;                     //�L�����N�^�[�̗͍̑ő�l
	int mAnimCnt;                     //�L�����N�^�[�̃A�j���[�V�����̐�
	int mWay;						  //3way�̌X��

public:                         //�����o�[�֐�
	CHAR_TYPE mCharType;		//�L�����N�^�[�̎��
	bool Init(GameScene* parent, int ScreenSizeX, int ScreenSizeY);           //�C���X�^���X�̐�������
	void UpDate(void);         //�C���X�^���X�̍X�V����
	void Draw(Vector2 pos);    //�C���X�^���X�̕`�揈��
	bool Release(void);        //�C���X�^���X�̊J������
	void CreateShot(Vector2 PlayerPos, DIR PlayerDir, CHAR_TYPE charType, int way);     //�e�̍��W�ƌ������^�[�Q�b�g�ɃZ�b�g
	int IsAlive(void);       //�e�����˂���Ă��邩
	Vector2 GetPos(void);     //�e�̍��W��Ԃ�
	Vector2 GetSize(void);	  //�摜�T�C�Y��Ԃ�
	void Destroy(void);		  //�摜������
};