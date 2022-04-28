#pragma once
#include "Vector2.h"
#include "GameCommon.h"

class GameScene;

class Player
{
public:
	bool Init(GameScene* parent);				
	Vector2 Update(void);					
	void Draw(void);					
	void Release(void);					

	//�p�Y�����n�߂邩���ׂ�
	bool CheckSlide(void);	
	bool CheckLight(void);
	bool CheckBucket(void);
	bool CheckSafe(void);

	bool ClearFlag(void);	//true�F���@�w��������GameClear�V�[���ɑJ�ڂ��鏀�����ł���

	bool back;

	//�p�Y���̊Ǘ��t���O
	struct Flag
	{
		bool DrawFlag;
		bool start;
		bool slide;
		bool light;
		bool bucket;
		bool safe;
		bool escape;
	};

	//�p�Y���J�n�p�t���O
	struct startFlag
	{
		bool slide;
		bool light;
		bool bucket;
		bool safe;
	};

	Flag mFlag;
	startFlag mSFlag;

private:

	//GameScene�̏��i�[�p
	GameScene* mParent;

	int mImage[static_cast<int>(DIR::MAX)][ANIM_MAX];	//�v���C���[�摜�i�[�p

	int mSpeed;

	//�v���C���[���W�n
	Vector2 mPos;	
	Vector2 mRayPos;	//�����蔻��̃`�F�b�N�p
	Vector2 mOffset;	//Stage�ɏ��悤���W�����炵�ĕ`�悳����

	int mANIM;
	DIR mMoveDir;							
	int mAnimCnt;							

	bool flag_;

};