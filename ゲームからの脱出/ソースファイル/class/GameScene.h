#pragma once
#include "Stage.h"
#include "Player.h"
#include "Pazzule/Slide.h"
#include "Pazzule/Light.h"
#include "Pazzule/Bucket.h"
#include "Pazzule/Safe.h"
#include "Pazzule/Tips.h"

class GameScene
{
public:
	bool Init(void);
	bool Update(void);
	void Draw(void);
	bool Release(void);

	int GetEvent(Vector2 pos);
	int GetCol(Vector2 pos);	//�����蔻��擾�֐�
	bool SafeCheck(void);		//���ɂ��J�����邩�m�F
	bool ClearCheck(void);		//�e�p�Y���̃N���A�m�F

	struct Frag
	{
		bool slide;
		bool light;
		bool bucket;
		bool safe;
	};

	Frag flag;		//true�F�N���A�ς�
	Frag mSflag;	//true�F�p�Y���J�n

	bool escapeFlag;//true�F�E�o�\

private:
	Stage mStage;
	Player mPlayer;

	//�p�Y���N���X
	Slide mSlide;
	Light mLight;
	Bucket mBucket;
	Safe mSafe;

	Tips mTips;	//���ɂ̃p�X���[�h

	int count;

	bool safeCheck;	//���ɂ��J�����邩�H
};