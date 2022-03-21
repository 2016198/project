#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include <string>
#include "Player.h"
#include "KeyCheck.h"
#include "GameScene.h"

bool Player::Init(void) //�C���X�^���X�̐���
{
	mIsLift = false;
	mIsDrop = false;
	mIsJump = false;
	mIsJump = false;
	mJumpPower = 0;
	mJumpSpeed = 0.0f;
	mHitLT = Vector2(20, 16);
	mHitRB = Vector2(20, 32);
	if (mPlayerType == PLAYER_TYPE::PLAYER1)
	{
		mPos = Vector2(80, 32 * 11);
	}
	else
	{
		mPos = Vector2(380, 32 * 11);
	}
	mMoveSpeed = 0;
	mIsShot = false;
	mAction = Player::ACTION::IDLE;
	mDir = DIR::RIGHT;
	mAnimCount = 0;
	mAnimLockCnt = 0;

	return true;
}

Vector2 Player::UpDate(void) //�C���X�^���X�̍X�V
{
	Vector2 liftPos = mParent->GetLiftPos();
	if (mIsLift == true)
	{
		mPos.y = liftPos.y;
		mPos.y -= mHitRB.y;
		mJumpSpeed = 0;
		mIsJump = false;
		mJumpPower = 0;
	}
	Vector2 copyPosB = mPos;
	copyPosB.y += mHitRB.y;
	Vector2 LiftPosL = liftPos;//���t�g�̍��[
	Vector2 LiftPosR = liftPos;//���t�g�̉E�[
	LiftPosL.x -= LIFT_SIZE_X / 2;
	LiftPosR.x += LIFT_SIZE_X / 2;
	Vector2 copyPosL = copyPosB;
	Vector2 copyPosR = copyPosB;
	copyPosL.x -= 20;
	copyPosR.x += 20;
	if (mParent->GetLiftAlive())
	{
		if (LiftPosL.x <= copyPosL.x || LiftPosL.x <= copyPosR.x)
		{
			if (LiftPosR.x >= copyPosL.x || LiftPosR.x >= copyPosR.x)
			{
				//���t�g�ɏ���Ă����牽�����Ȃ�
			}
			else
			{
				mIsLift = false;
			}
		}
		else
		{
			mIsLift = false;
		}
	}
	else
	{
		mIsLift = false;
	}
	/*int action = (int)mAction;
	if (KeyTrgDown[KEY_P1_UP])
	{
		action++;
		if (action >= (int)Player::ACTION::MAX)
		{
			action = 0;
		}
		mAction = (Player::ACTION)action;
	}*/
	mAction = Player::ACTION::IDLE;
	/*if (KeyTrgDown[KEY_P1_A])
	{
		if (mShot == STYLE_NORMAL)
		{
			mShot = STYLE_SHOT;
		}
		else
		{
			mShot = STYLE_NORMAL;
		}
	}*/
	if (KeyTrgDown[KEY_P1_A])
	{
		mIsShot = true;
		mAnimLockCnt = ANIM_LOCK_FLAME;
	}
	else
	{
		mIsShot = false;
	}

	Player::MoveX();//�v���C���[�̍��E�ړ�����
	Player::JumpY();//�v���C���[�̃W�����v����
	if ((int)mJumpSpeed > 0)
	{
		mIsDrop = true;
	}
	else 
	{
		mIsDrop = false;
	}
	mAnimCount++;
	mAnimLockCnt--;
	return mPos;
}

void Player::Draw(void) //�C���X�^���X�̕`��
{
	int image = 0;//�v���C���[�̉摜�̏�Ԋm�F�p�ϐ�
	SHOT_STYLE shotValue = Player::SHOT_STYLE::NORMAL;//�v���C���[���e�𔭎˂��Ă��邩
	if (mAnimLockCnt > 0)
	{
		shotValue = Player::SHOT_STYLE::SHOT;
	}
	//�v���C���[�������m�F
	bool isDirLeft = false;
	if (mDir == DIR::LEFT)
	{
		isDirLeft = true;
	}

	//����A�j���[�V����
	if (mIsRun == true)
	{
		mAction = Player::ACTION::RUN;
	}

	//�W�����v�̃A�j���[�V����
	if (mIsJump == true)
	{
		mAction = Player::ACTION::JUMP;
	}

	switch (mAction)
	{
	case Player::ACTION::DAMAGED:
		image = mActionImage[static_cast<int>(mAction)][0][0];
		break;
	case Player::ACTION::JUMP:
	case Player::ACTION::IDLE:
		image = mActionImage[static_cast<int>(mAction)][static_cast<int>(shotValue)][0];
		break;
	case Player::ACTION::RUN:
		image = mActionImage[static_cast<int>(mAction)][static_cast<int>(shotValue)][mAnimCount / 15 % 4];
		break;
	case Player::ACTION::MAX:
		break;
	default:
		break;
	}
	//double pai = 3.14159265358979;
	DrawRotaGraph(mPos.x, mPos.y, 1.0f, 0.0f, image, true, isDirLeft, false);
	DrawLine(0, mPos.y, 800, mPos.y, GetColor(0, 0, 0));
	DrawLine(mPos.x, 0, mPos.x, 420, GetColor(0, 0, 0));
	//DrawFormatString(0, 0, GetColor(0, 0, 0), "%d   %d", mPos.x, mPos.y);
	DrawBox(mPos.x - mHitLT.x, mPos.y - mHitLT.y, mPos.x + mHitRB.x, mPos.y + mHitRB.y, GetColor(255, 255, 0), false);
}

bool Player::Release(void) //�C���X�^���X�̊J��
{
	for (int z = 0; z < (int)Player::ACTION::MAX; z++)
	{
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < ANIM_MAX; x++)
			{
				if (mActionImage[z][y][x] != -1)
				{
					DeleteGraph(mActionImage[z][y][x]);
				}
			}
		}
	}
	return true;
}

bool Player::LoadImages(PLAYER_TYPE playerType)//�摜�̃��[�h
{
	//mActionImage[][][]�̒��g��������
	for (int z = 0; z < (int)Player::ACTION::MAX; z++)
	{
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < ANIM_MAX; x++)
			{
				mActionImage[z][y][x] = -1;
			}
		}
	}

	std::string path = "Image/Player/";

	if (playerType == PLAYER_TYPE::PLAYER1)
	{
		path += "P1/";
	}
	else
	{
		path += "P2/";
	}
	//�摜�̃��[�h
	if ((mActionImage[static_cast<int>(Player::ACTION::DAMAGED)][static_cast<int>(SHOT_STYLE::NORMAL)][0] = 
		LoadGraph((path + "Damaged.png").c_str())) == -1)
	{
		return false;
	}
	if ((mActionImage[static_cast<int>(Player::ACTION::IDLE)][static_cast<int>(SHOT_STYLE::NORMAL)][0] = 
		LoadGraph((path + "Idle.png").c_str())) == -1)
	{
		return false;
	}
	if ((mActionImage[static_cast<int>(Player::ACTION::IDLE)][static_cast<int>(SHOT_STYLE::SHOT)][0] = 
		LoadGraph((path + "IdleShot.png").c_str())) == -1)
	{
		return false;
	}
	if ((mActionImage[static_cast<int>(Player::ACTION::JUMP)][static_cast<int>(SHOT_STYLE::NORMAL)][0] = 
		LoadGraph((path + "Jump.png").c_str())) == -1)
	{
		return false;
	}
	if ((mActionImage[static_cast<int>(Player::ACTION::JUMP)][static_cast<int>(SHOT_STYLE::SHOT)][0] = 
		LoadGraph((path + "JumpShot.png").c_str())) == -1)
	{
		return false;
	}
	if ((LoadDivGraph((path + "Run.png").c_str(),
		ANIM_MAX,
		ANIM_MAX,
		1,
		96,
		64,
		&mActionImage[(int)Player::ACTION::RUN][static_cast<int>(SHOT_STYLE::NORMAL)][0])) == -1)
	{
		return false;
	}
	if ((LoadDivGraph((path + "RunShot.png").c_str(),
		ANIM_MAX,
		ANIM_MAX,
		1,
		96,
		64,
		&mActionImage[(int)Player::ACTION::RUN][static_cast<int>(SHOT_STYLE::SHOT)][0])) == -1)
	{
		return false;
	}	
	return true;
}

DIR Player::GetDir(void)//�v���C���[�̌��������炤
{
	return mDir;
}

void Player::MoveX(void)//���E�̈ړ�����
{
	Vector2 copyPos = mPos;
	mIsRun = false;
	//���ɑ����Ă���Ƃ�
	if (KeyNow[KEY_P1_LEFT])
	{
		mIsRun = true;
		mDir = DIR::LEFT;
		if ((int)mMoveSpeed > -MAX_MOVE_SPEED)
		{
			//mMoveSpeed -= 0.2f;
			mMoveSpeed -= MOVE_ADD;
		}
	}
	//�E�ɑ����Ă���Ƃ�
	else if (KeyNow[KEY_P1_RIGHT])
	{
		mIsRun = true;
		mDir = DIR::RIGHT;
		if ((int)mMoveSpeed < MAX_MOVE_SPEED)
		{
			//mMoveSpeed += 0.2f;
			mMoveSpeed += MOVE_ADD;
		}
	}
	//�����Ă��Ȃ��Ƃ�
	if (mIsRun == false)
	{
		if ((int)mMoveSpeed < 0)
		{
			//mMoveSpeed += 0.3f;
			mMoveSpeed += MOVE_DEC;
		}
		else if ((int)mMoveSpeed > 0)
		{
			//mMoveSpeed -= 0.3f;
			mMoveSpeed -= MOVE_DEC;
		}
		else if ((int)mMoveSpeed == 0)
		{
			mMoveSpeed = 0.0f;
		}
	}
	copyPos.x += (int)mMoveSpeed;
	Vector2 copyPosL = copyPos;			//�R�s�[���S���W�̍���
	Vector2 copyPosR = copyPos;			//�R�s�[���S���W�̉E��
	copyPosL.x -= mHitLT.x;
	copyPosR.x += mHitRB.x;
	Vector2 copyPosT = copyPos;			//�R�s�[���S���W�̏㑤
	Vector2 copyPosB = copyPos;			//�R�s�[���S���W�̉���
	copyPosT.y -= mHitLT.y;
	copyPosB.y += mHitRB.y;
	Vector2 copyPosTL = copyPosT;		//�R�s�[���S���W�̍���
	Vector2 copyPosTR = copyPosT;		//�R�s�[���S���W�̉E��
	copyPosTL.x -= mHitLT.x;
	copyPosTR.x += mHitRB.x;
	Vector2 copyPosBL = copyPosB;		//�R�s�[���S���W�̍���
	Vector2 copyPosBR = copyPosB;		//�R�s�[���S���W�̉E��
	copyPosBL.x -= mHitLT.x;
	copyPosBR.x += mHitRB.x;

	int IdxL = copyPosL.x / CHIP_SIZE_X;//������}�b�v�̃C���f�b�N�X�̍����W
	int IdxR = copyPosR.x / CHIP_SIZE_X;//������}�b�v�̃C���f�b�N�X�̉E���W

	//�ǂɂԂ������猳�̍��W�ɖ߂��B
	switch (mParent->GetEvent(copyPosL))
	{
	case 8:
	case 9:
	case 11:
	case 12:
		//�����ǂɂԂ����Č��̖߂�����
		mPos.x = (IdxL + 1) * CHIP_SIZE_X + mHitLT.x;
		mMoveSpeed = 0;
		break;
	default:
		switch (mParent->GetEvent(copyPosR))
		{
		case 8:
		case 9:
		case 11:
		case 12:
			//�E���ǂɂԂ����Č��̖߂�����
			mPos.x = IdxR * CHIP_SIZE_X - mHitRB.x - 1;
			mMoveSpeed = 0;
			break;
		default:
			switch (mParent->GetEvent(copyPosTR))
			{
			case 8:
			case 9:
			case 11:
			case 12:
				//�E�オ�ǂɂԂ����Č��̖߂�����
				mPos.x = IdxR * CHIP_SIZE_X - mHitRB.x - 1;
				mMoveSpeed = 0;
				break;
			default:
				switch (mParent->GetEvent(copyPosBR))
				{
				case 8:
				case 9:
				case 11:
				case 12:
					//�E�����ǂɂԂ����Č��̖߂�����
					mPos.x = IdxR * CHIP_SIZE_X - mHitRB.x - 1;
					mMoveSpeed = 0;
					break;
				default:
					switch (mParent->GetEvent(copyPosTL))
					{
					case 8:
					case 9:
					case 11:
					case 12:
						//���オ�ǂɂԂ����Č��̖߂�����
						mPos.x = (IdxL + 1) * CHIP_SIZE_X + mHitLT.x;
						mMoveSpeed = 0;
						break;
					default:
						switch (mParent->GetEvent(copyPosBL))
						{
						case 8:
						case 9:
						case 11:
						case 12:
							//�������ǂɂԂ����Č��̖߂�����
							mPos.x = (IdxL + 1) * CHIP_SIZE_X + mHitLT.x;
							mMoveSpeed = 0;
							break;
						default:
							mPos = copyPos;
							break;
						}
						break;
					}
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

void Player::JumpY(void)//�W�����v�̏���
{
	Vector2 copyPos = mPos;
	if (mJumpPower < JUMP_POWER_MAX)
	{
		if ((int)mJumpSpeed <= 0)
		{
			if (KeyNow[KEY_P1_UP])
			{
				mIsLift = false;
				mIsJump = true;
				mJumpSpeed = -V0;
				mJumpPower++;
			}
		}
	}
	if (KeyTrgUp[KEY_P1_UP])
	{
		mJumpPower = JUMP_POWER_MAX;
	}
	
	mJumpSpeed += GRAVITY;

	copyPos.y += (int)mJumpSpeed;
	Vector2 copyPosT = copyPos;			//�R�s�[���S���W�̏㑤
	Vector2 copyPosB = copyPos;			//�R�s�[���S���W�̉���
	copyPosT.y -= mHitLT.y;
	copyPosB.y += mHitRB.y;
	Vector2 copyPosTL = copyPosT;		//�R�s�[���S���W�̍���
	Vector2 copyPosTR = copyPosT;		//�R�s�[���S���W�̉E��
	copyPosTL.x -= mHitLT.x;
	copyPosTR.x += mHitRB.x;
	Vector2 copyPosBL = copyPosB;		//�R�s�[���S���W�̍���
	Vector2 copyPosBR = copyPosB;		//�R�s�[���S���W�̉E��
	copyPosBL.x -= mHitLT.x;
	copyPosBR.x += mHitRB.x;

	int IdxT = copyPosT.y / CHIP_SIZE_Y;//������}�b�v�̃C���f�b�N�X�̏���W
	int IdxB = copyPosB.y / CHIP_SIZE_Y;//������}�b�v�̃C���f�b�N�X�̉����W
	//�n�ʂ������ ��X���W�͂��̂܂�
	switch (mParent->GetEvent(copyPosB))
	{
	case 8:
	case 9:
	case 11:
	case 12:
		//�����n�ʂɂ��Ė��܂�Ȃ��悤�ɂ��鏈��
		mPos.y = IdxB * CHIP_SIZE_Y - mHitRB.y - 1;
		mIsJump = false;
		mJumpSpeed = 0.0f;
		mJumpPower = 0;
		break;
	default:
		switch (mParent->GetEvent(copyPosT))
		{
		case 8:
		case 9:
		case 11:
		case 12:
			//�オ�V��ɓ������č��W�����ɖ߂�����
			mPos.y = (IdxT + 1) * CHIP_SIZE_Y + mHitLT.y;
			mJumpSpeed = 0.0f;
			mJumpPower = JUMP_POWER_MAX;
			break;
		default:
			switch (mParent->GetEvent(copyPosTL))
			{
			case 8:
			case 9:
			case 11:
			case 12:
				//���オ�V��ɓ������č��W�����ɖ߂�����
				mPos.y = (IdxT + 1) * CHIP_SIZE_Y + mHitLT.y;
				mJumpSpeed = 0.0f;
				mJumpPower = JUMP_POWER_MAX;
				break;
			default:
				switch (mParent->GetEvent(copyPosTR))
				{
				case 8:
				case 9:
				case 11:
				case 12:
					//�E�オ�V��ɓ������č��W�����ɖ߂�����
					mPos.y = (IdxT + 1) * CHIP_SIZE_Y + mHitLT.y;
					mJumpSpeed = 0.0f;
					mJumpPower = JUMP_POWER_MAX;
					break;
				default:
					switch (mParent->GetEvent(copyPosBL))
					{
					case 8:
					case 9:
					case 11:
					case 12:
						//�������n�ʂɂ��Ė��܂�Ȃ��悤�ɂ��鏈��
						mPos.y = IdxB * CHIP_SIZE_Y - mHitRB.y - 1;
						mIsJump = false;
						mJumpSpeed = 0.0f;
						mJumpPower = 0;
						break;
					default:
						switch (mParent->GetEvent(copyPosBR))
						{
						case 8:
						case 9:
						case 11:
						case 12:
							//�E�����n�ʂɂ��Ė��܂�Ȃ��悤�ɂ��鏈��
							mPos.y = IdxB * CHIP_SIZE_Y - mHitRB.y - 1;
							mIsJump = false;
							mJumpSpeed = 0.0f;
							mJumpPower = 0;
							break;
						default:
							if (mParent->GetLiftAlive() && mIsDrop == true)
							{
								Vector2 pos = Player::RiadLift(mParent->GetLiftPos(), copyPosB);
								copyPos.y = pos.y;
								copyPos.y -= mHitRB.y;
							}
							mPos = copyPos;
							break;
						}
						break;
					}
					break;
				}
				break;
			}
			break;
		}
		break;
	}
}

bool Player::IsShot(void)	//�e�����������ǂ���
{
	return mIsShot;
}

bool Player::IsJump(void)//�W�����v�����Ă��邩�ǂ���
{
	return mIsJump;
}

Vector2 Player::RiadLift(Vector2 LiftPos,Vector2 copyPosB)//���t�g�ɏ�������̏���
{
	Vector2 LiftPosL = LiftPos;//���t�g�̍��[
	Vector2 LiftPosR = LiftPos;//���t�g�̉E�[
	LiftPosL.x -= LIFT_SIZE_X / 2;
	LiftPosR.x += LIFT_SIZE_X / 2;
	Vector2 copyPosL = copyPosB;
	Vector2 copyPosR = copyPosB;
	copyPosL.x -= 20;
	copyPosR.x += 20;
	if (LiftPosL.x <= copyPosL.x || LiftPosL.x <= copyPosR.x)
	{
		if (LiftPosR.x >= copyPosL.x || LiftPosR.x >= copyPosR.x)
		{
			if ((copyPosB.y >= LiftPos.y && mPos.y <= LiftPos.y) || mIsLift == true)
			{
				mIsLift = true;
				return LiftPos;
			}
		}
	}
			
	mIsLift = false;
	return copyPosB;
}

Vector2 Player::GetShotPos(void)//�e�̔��ˈʒu
{
	Vector2 shotPos = mPos;
	if (mDir == DIR::LEFT)
	{
		shotPos.x -= 38;
		if (mIsJump == true)
		{
			shotPos.y -= 6;
		}
		else
		{
			shotPos.y += 6;
		}
	}
	else
	{
		shotPos.x += 38;
		if (mIsJump == true)
		{
			shotPos.y -= 6;
		}
		else
		{
			shotPos.y += 6;
		}
	}
	return shotPos;
}

Player::Player(GameScene* parent, PLAYER_TYPE playerType) //�R���X�g���X�^
{
	//�e�̃|�C���^�ϐ�
	mParent = parent;
	//�v���C���[�̎��
	mPlayerType = playerType;
	//�v���C���[�摜�̓ǂݍ���
	Player::LoadImages(playerType);
}

Player::~Player(void) //�f�X�g���X�^
{

}