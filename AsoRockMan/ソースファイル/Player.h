//#pragma once
#include "Vector2.h"
#include "gamecommon.h"

//�e�̃C���X�^���X
class GameScene;

class Player
{
	enum class ACTION	//�v���C���[�̃A�N�V����
	{
		IDLE,		//0
		JUMP,		//1
		RUN,		//2
		DAMAGED,	//3
		MAX			//4
	};

	//�e�̔��ˏ��
	enum class SHOT_STYLE
	{
		NORMAL,		//���˂��Ă��Ȃ�
		SHOT,		//���˂��Ă���
		MAX
	};

	//�v���C���[�̃X�s�[�h
	static constexpr float MAX_MOVE_SPEED = 3.5f;	//�ő�l
	static constexpr float MOVE_ADD = 0.25f;		//����
	static constexpr float MOVE_DEC = 0.05f;		//����

	//�W�����v
	static constexpr float GRAVITY = 0.5f;		//�d�͉����x
	static constexpr float V0 = 10.0f;			//����
	static constexpr int JUMP_POWER_MAX = 10;	//�W�����v�͂̍ő�l

	//�A�j���[�V����
	static constexpr int ANIM_MAX = 4;			//�A�j���[�V�����̐�
	static constexpr int ANIM_LOCK_FLAME = 60;	//�A�j���[�V�����p�ϐ�

private:						//�����o�[�ϐ�
	GameScene* mParent;			//�e�̃C���X�^���X�i�[�ϐ�
	PLAYER_TYPE mPlayerType;	//�v���C���[�̎��(PLAYER1 or PLAYER2)
	Vector2 mPos;				//�v���C���[�̍��W
	ACTION mAction;				//�v���C���[�̏��
	//int mShot;					//�v���C���[�����˂������ǂ���
	DIR mDir;					//�v���C���[�̌���
	Vector2 mHitLT;				//mHitLeftTop�v���C���[�̓����蔻��̍���
	Vector2 mHitRB;				//mHitRightBottom�v���C���[�̓����蔻��̉E��
	float mMoveSpeed;			//�v���C���[�̑���
	int mAnimCount;				//�A�j���[�V�����ϐ�
	int mAnimLockCnt;			//�A�j���[�V�������b�N�ϐ�
	//					���A�N�V�����@�@						���V���b�g�@			���A�j��
	int mActionImage[static_cast<int>(ACTION::MAX)][static_cast<int>(SHOT_STYLE::MAX)][ANIM_MAX]; //�v���C���[�̉摜

	bool mIsDrop;				//���������ǂ���
	float mJumpSpeed;			//�W�����v�̃X�s�[�h
	int mJumpPower;				//�W�����v�̃p���[
	bool mIsJump;				//�W�����v���Ă��邩�ǂ���
	bool mIsRun;				//�����Ă��邩�ǂ���

	bool mIsLift;				//���t�g�ɏ���Ă��邩
	bool mIsShot;				//�e�����������ǂ���
	//�֐�
	bool LoadImages(PLAYER_TYPE playerType);		//�v���C���[�̉摜�̓ǂݍ���
	void MoveX(void);			//���E�ړ��̏���
	void JumpY(void);			//�W�����v�̏���

public:
	Player(GameScene* parent, PLAYER_TYPE playerType);	//�R���X�g���X�^

	bool IsShot(void);			//�e�����������ǂ���
	bool IsJump(void);			//�W�����v�����Ă��邩�ǂ���
	DIR GetDir(void);			//�v���C���[�̌��������炤
	Vector2 RiadLift(Vector2 liftPos, Vector2 copyPosB);	//���t�g�ɏ�������̏���
	Vector2 GetShotPos(void);	//�e�̔��˒��S�ʒu

	bool Init(void);			//�C���X�^���X�̐���
	Vector2 UpDate(void);		//�C���X�^���X�̍X�V
	void Draw(void);			//�C���X�^���X�̕`��
	bool Release(void);			//�C���X�^���X�̊J��

	~Player(void);				//�f�X�g���X�^

};
