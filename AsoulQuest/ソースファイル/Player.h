#pragma once
#include "Vector2.h"
#include "GameCommon.h"
class GameScene;

//�萔��`	
#define PLAYER_ANIM_COUNT 4 //���@�̃A�j���̍ő�l

class Player
{
private:                              //�����o�[�ϐ�
	GameScene* mParent;               //�e�̃C���X�^���X�̃|�C���^�ϐ�
	int mScreenSizeX;                 //��ʂ�X�T�C�Y
	int mScreenSizeY;                 //��ʂ�Y�T�C�Y
	int mImage[(int)DIR::DIR_MAX][PLAYER_ANIM_COUNT];    //�O���t�B�b�N�n���h��
	int mDeathImage[3];				  //�O���t�B�b�N�n���h��
	Vector2 mOffset;                  //�I�t�Z�b�g�̍��W
	DIR mKeyDir;                      //�L�[�̐���
	int mCharType;                    //�L�����N�^�[�̎��
	DIR mMoveDir;                     //�L�����N�^�[�̌���
	Vector2 mPos;                     //�L�����N�^�[�̒n�}��̍��W
	Vector2 mSizeOffset;              //�L�����N�^�[�̃I�t�Z�b�g�T�C�Y
	Vector2 mSize;                    //�L�����N�^�[�̉摜�̃T�C�Y
	int mMoveSpeed;                   //�L�����N�^�[�̈ړ��X�s�[�h
	int mLifeMax;                     //�L�����N�^�[�̗͍̑ő�l
	int mLifeTime;					  //�ŏ��ɂ��鎞��
	int mAnimCnt;                     //�L�����N�^�[�̃A�j���[�V�����̐�

	Vector2 mCopyPos;				  //�P�t���[���O�̃v���C���[�̍��W
	int mPush;                        //�L�[�������Ă��鎞��
	bool mShotFlag;					  //�v���C���[�����𔭎˂������itrue:���ˁj
	bool mWayShotFlag;				  //�v���C���[��3way�𔭎˂������itrue:���ˁj

public:                        //�����o�[�֐�
	int mPosBottom;            //���@�̑����̍��W
	bool Init(GameScene* parent, int ScreenSizeX, int ScreenSizeY);           //�C���X�^���X�̐���
	void UpDate(void);         //�C���X�^���X�̍X�V����
	void Draw(void);           //�C���X�^���X�̕`�揈��
	bool Release(void);        //�C���X�^���X�̊J������
	Vector2 GetOffsetPos(void);//���W(�w�i)��Ԃ�
	Vector2 GetPos(void);      //���W��Ԃ�
	Vector2 GetSize(void);     //�摜�̃T�C�Y��Ԃ�
	DIR GetDir(void);          //���@�̌�����Ԃ�
	bool IsShot(void);         //�v���C���[�����𔭎˂������ǂ���
	bool IsWayShot(void);	   //3way����������
	int IsAlive(void);         //�����Ă�؋�����
	void SetPos(Vector2 pos, Vector2 offsetPos);  //�v���C���[�̍��W���Z�b�g
	void Destroy(void);								//�v���C���[�̃��C�t�����炷
	void S_Destroy(void);							//�V�[���h�̑ϋv�l�����炷
	bool Collsion(Vector2 targetPos, Vector2 targetSize); //�Փ˔���
	bool GameInit(void);							//�v���C���[�̏�����
	void GetShield(void);				//������ɓ��ꂽ��
	void GetHeart(void);			//�n�[�g����ɓ��ꂽ��
	void UndoPos(void);				//�v���C���[�̍��W��߂�
	int mLife;                        //�L�����N�^�[�̗̑� 
	int mShield;					//�V�[���h�ϋv�l
};