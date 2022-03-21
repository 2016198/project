#pragma once
#include "GameCommon.h"
#include "Vector2.h"
class GameScene;

//�萔��`
#define ENEMY_ANIM_COUNT 4       //�G�̃A�j���[�V�����̍ő�l

class Enemy
{

private:
	int mScreenSizeX;              //��ʂ�X�T�C�Y
	int mScreenSizeY;              //��ʂ�Y�T�C�Y
	Vector2 mSizeOffset;           //�L�����N�^�[�̃I�t�Z�b�g�T�C�Y
	GameScene* mParent;                              //�e�̃C���X�^���X�̃|�C���^�ϐ�
	int mMoveSpeed[ENEMY_TYPE_MAX] = {               //�G�̃X�s�[�h
		2, 3, 3, 3, 4, 1
	};
	
	Vector2 mSize;										   //�摜�̃T�C�Y
	Vector2 mPos;                                          //���W����
	DIR mMoveDir;                                          //�L�����N�^�[�̌���
	Vector2 mOffset;                                       //�I�t�Z�b�g�̍��W
	int mLife;									   		   //�L�����N�^�[�̗̑�
	int mLifeMax;									       //�L�����N�^�[�̗͍̑ő�l
	int mAnimCnt;										   //�L�����N�^�[�̃A�j���[�V�����̐�
	int mCharType;                                         //�L�����N�^�[�̎��
	int mLifeDec;                                          //�e���ꔭ���������猸�鐔
	Vector2 mTargetPos;									   //�Ώۂ̍�
	int EnemyMoveX(int* EnemyPosX, int enemySpeed, int targetPosX, DIR* move);								//X���W�����킹��
	int EnemyMoveY(int* EnemyPosX, int enemySpeed, int targetPosY, DIR* move);								//Y���W�����킹��
	int EnemyMoveXY(int* enemyPosX, int* enemyPosY, int targetPosX, int targetPosY, int enemySpeed);        //�����������ق����獇�킹��

public:
	int mPosBottom;																					   //�G�̑����̍��W
	bool Init(GameScene* parent, int enemyType, int ScreenSizeX, int ScreenSizeY, Vector2 pos);        //�C���X�^���X�̐���
	void UpDate(Vector2 PlayerPos);                                                                    //�C���X�^���X�̍X�V����
	void Draw(Vector2 pos);                                                                            //�C���X�^���X�̕`�揈��
	bool Release(void);                                                                                //�C���X�^���X�̊J������
	Vector2 GetPos(void);																			   //���W��Ԃ�
	DIR GetDir(void);																				   //�L�����N�^�[�̌�����ς���
	Vector2 GetSize(void);																			   //�摜�T�C�Y��Ԃ�
	int GetType(void);																				   //�G�̎�ނ�Ԃ�
	void Destroy(void);		      																	   //�摜������
	int IsAlive(void);                                                                                 //�����Ă邩�ǂ���
	bool Collsion(Vector2 targetPos, Vector2 targetSize);											   //�G�̓����蔻��
};