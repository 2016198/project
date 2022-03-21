#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "DxLib.h"
#include <string>
#include "Player.h"
#include "KeyCheck.h"
#include "GameScene.h"

bool Player::Init(void) //インスタンスの生成
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

Vector2 Player::UpDate(void) //インスタンスの更新
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
	Vector2 LiftPosL = liftPos;//リフトの左端
	Vector2 LiftPosR = liftPos;//リフトの右端
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
				//リフトに乗っていたら何もしない
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

	Player::MoveX();//プレイヤーの左右移動処理
	Player::JumpY();//プレイヤーのジャンプ処理
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

void Player::Draw(void) //インスタンスの描画
{
	int image = 0;//プレイヤーの画像の状態確認用変数
	SHOT_STYLE shotValue = Player::SHOT_STYLE::NORMAL;//プレイヤーが弾を発射しているか
	if (mAnimLockCnt > 0)
	{
		shotValue = Player::SHOT_STYLE::SHOT;
	}
	//プレイヤーが向き確認
	bool isDirLeft = false;
	if (mDir == DIR::LEFT)
	{
		isDirLeft = true;
	}

	//走るアニメーション
	if (mIsRun == true)
	{
		mAction = Player::ACTION::RUN;
	}

	//ジャンプのアニメーション
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

bool Player::Release(void) //インスタンスの開放
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

bool Player::LoadImages(PLAYER_TYPE playerType)//画像のロード
{
	//mActionImage[][][]の中身を初期化
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
	//画像のロード
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

DIR Player::GetDir(void)//プレイヤーの向きをもらう
{
	return mDir;
}

void Player::MoveX(void)//左右の移動処理
{
	Vector2 copyPos = mPos;
	mIsRun = false;
	//左に走っているとき
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
	//右に走っているとき
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
	//走っていないとき
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
	Vector2 copyPosL = copyPos;			//コピー中心座標の左側
	Vector2 copyPosR = copyPos;			//コピー中心座標の右側
	copyPosL.x -= mHitLT.x;
	copyPosR.x += mHitRB.x;
	Vector2 copyPosT = copyPos;			//コピー中心座標の上側
	Vector2 copyPosB = copyPos;			//コピー中心座標の下側
	copyPosT.y -= mHitLT.y;
	copyPosB.y += mHitRB.y;
	Vector2 copyPosTL = copyPosT;		//コピー中心座標の左上
	Vector2 copyPosTR = copyPosT;		//コピー中心座標の右上
	copyPosTL.x -= mHitLT.x;
	copyPosTR.x += mHitRB.x;
	Vector2 copyPosBL = copyPosB;		//コピー中心座標の左下
	Vector2 copyPosBR = copyPosB;		//コピー中心座標の右下
	copyPosBL.x -= mHitLT.x;
	copyPosBR.x += mHitRB.x;

	int IdxL = copyPosL.x / CHIP_SIZE_X;//今いるマップのインデックスの左座標
	int IdxR = copyPosR.x / CHIP_SIZE_X;//今いるマップのインデックスの右座標

	//壁にぶつかったら元の座標に戻す。
	switch (mParent->GetEvent(copyPosL))
	{
	case 8:
	case 9:
	case 11:
	case 12:
		//左が壁にぶつかって元の戻す処理
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
			//右が壁にぶつかって元の戻す処理
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
				//右上が壁にぶつかって元の戻す処理
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
					//右下が壁にぶつかって元の戻す処理
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
						//左上が壁にぶつかって元の戻す処理
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
							//左下が壁にぶつかって元の戻す処理
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

void Player::JumpY(void)//ジャンプの処理
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
	Vector2 copyPosT = copyPos;			//コピー中心座標の上側
	Vector2 copyPosB = copyPos;			//コピー中心座標の下側
	copyPosT.y -= mHitLT.y;
	copyPosB.y += mHitRB.y;
	Vector2 copyPosTL = copyPosT;		//コピー中心座標の左上
	Vector2 copyPosTR = copyPosT;		//コピー中心座標の右上
	copyPosTL.x -= mHitLT.x;
	copyPosTR.x += mHitRB.x;
	Vector2 copyPosBL = copyPosB;		//コピー中心座標の左下
	Vector2 copyPosBR = copyPosB;		//コピー中心座標の右下
	copyPosBL.x -= mHitLT.x;
	copyPosBR.x += mHitRB.x;

	int IdxT = copyPosT.y / CHIP_SIZE_Y;//今いるマップのインデックスの上座標
	int IdxB = copyPosB.y / CHIP_SIZE_Y;//今いるマップのインデックスの下座標
	//地面を歩ける ※X座標はそのまま
	switch (mParent->GetEvent(copyPosB))
	{
	case 8:
	case 9:
	case 11:
	case 12:
		//下が地面について埋まらないようにする処理
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
			//上が天井に当たって座標を元に戻す処理
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
				//左上が天井に当たって座標を元に戻す処理
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
					//右上が天井に当たって座標を元に戻す処理
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
						//左下が地面について埋まらないようにする処理
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
							//右下が地面について埋まらないようにする処理
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

bool Player::IsShot(void)	//弾を撃ったかどうか
{
	return mIsShot;
}

bool Player::IsJump(void)//ジャンプをしているかどうか
{
	return mIsJump;
}

Vector2 Player::RiadLift(Vector2 LiftPos,Vector2 copyPosB)//リフトに乗った時の処理
{
	Vector2 LiftPosL = LiftPos;//リフトの左端
	Vector2 LiftPosR = LiftPos;//リフトの右端
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

Vector2 Player::GetShotPos(void)//弾の発射位置
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

Player::Player(GameScene* parent, PLAYER_TYPE playerType) //コンストラスタ
{
	//親のポインタ変数
	mParent = parent;
	//プレイヤーの種別
	mPlayerType = playerType;
	//プレイヤー画像の読み込み
	Player::LoadImages(playerType);
}

Player::~Player(void) //デストラスタ
{

}