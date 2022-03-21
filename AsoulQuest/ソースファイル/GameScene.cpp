#include "GameScene.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"
#include "SceneManager.h"

//�萔��`
#define HIGH_SCORE 500

//�ϐ���`
const char* mFlieName = "data.dat";   //�t�@�C���̖��O�p�ϐ�

bool GameScene::Init(int ScreenSizeX, int ScreenSizeY, SceneManager* parent)  //�C���X�^���X�̐�������
{
	SetTransColor(255, 0, 255);
	//���ʉ��̓ǂݍ���
	if ((mSeWay = LoadSoundMem("sound/3way.wav")) == -1)
	{
		return false;
	}
	if ((mSeKill = LoadSoundMem("sound/kill.wav")) == -1)
	{
		return false;
	}
	if ((mSeHit = LoadSoundMem("sound/hit.wav")) == -1)
	{
		return false;
	}
	if ((mSePshot = LoadSoundMem("sound/p_shot.wav")) == -1)
	{
		return false;
	}
	if ((mSeEshot = LoadSoundMem("sound/e_shot.wav")) == -1)
	{
		return false;
	}
	if ((mSeCoin = LoadSoundMem("sound/coin.wav")) == -1)
	{
		return false;
	}
	if ((mSeBuy = LoadSoundMem("sound/buy.wav")) == -1)
	{
		return false;
	}
	if ((mSeDoor = LoadSoundMem("sound/door.wav")) == -1)
	{
		return false;
	}
	if ((mSeDamage = LoadSoundMem("sound/damage.wav")) == -1)
	{
		return false;
	}
	//�e�̉摜�̓ǂݍ���
	if (!LoadShotImage()) return false;
	//�G�̉摜�̓ǂݍ���
	if (!LoadEnemyImage()) return false;
	//���C�t�o�[�摜�̓ǂݍ���
	if (!LoadLifeBarImage()) return false;
	//�A�C�e���摜�̓ǂݍ���
	if (!LoadItemImage()) return false;

	mScene_id = SceneId::SCENE_BATTOL;
	mFadeOut = false;
	mFadeIn = false;
	mWay = 10;
	mCoin = 0;
	mKillCount = 0;
	mNextMapID = MAP_ID::MAZE;
	mMapChange = false;
	mParent = parent;
	Vector2 enemyPos;     //�G�̍��W
	int enemyType;
	LoadData();
	mScore = 0;
	mFont = GetDrawFormatStringWidth("%d", mScore);
	mFontHigh = GetDrawFormatStringWidth("%d", mParent->mHighScore);
	mFontkill = GetDrawFormatStringWidth("%d", mKillCount);
	mCharOrderCount = 0;

	mScreenSizeX = ScreenSizeX;
	mScreenSizeY = ScreenSizeY;
	mCounter = 0;
	mColor = 255;
	if (!mStage.Init(mScreenSizeX, mScreenSizeY)) return false; //�}�b�v�̏�����
	for (int s = 0; s < SHOT_COUNT; s++)
	{
		if (!mShot[s].Init(this, mScreenSizeX, mScreenSizeY)) return false; //�e�̏�����
	}
	if (!mPlayer.Init(this, mScreenSizeX, mScreenSizeY)) return false; //�v���C���[�̏�����
	AddCharOrder(mPlayer.mPosBottom, mCharOrderCount, CHAR_TYPE::PLAYER); //�v���C���[�̑������W
	for (int e = 0; e < ENEMY_COUNT; e++)
	{
		mCharOrder[e + 1].mCharType = CHAR_TYPE::ENEMY;
		enemyPos.x = rand() % 500 + 200;
		enemyPos.y = rand() % 500 + 200;
		enemyType = rand() % (ENEMY_TYPE_MAX - 1);
		if (!mEnemy[e].Init(this, enemyType, mScreenSizeX, mScreenSizeY, enemyPos)) return false;  //�G�̏�����
		if (!mLifeBar[e].init(this, enemyType)) return false;                       //HP(�G)�o�[�̏�����
		AddCharOrder(mEnemy[e].mPosBottom, e, CHAR_TYPE::ENEMY); //�G�̕��ёւ�
	} 
	for (int b = 0; b < SCORE_COUNT; b++) //�|�C���g�̏�����
	{
		if (!mPoint[b].Init()) return false;
	}
	for (int i = 0; i < ITEM_COUNT; i++)
	{
		if (!mItem[i].Init(this)) return false;
	}
	if (!mShop.Init(this, mScreenSizeX, mScreenSizeY)) return false;

	return true;
}

bool GameScene::UpDate(void)  //�C���X�^���X�̍X�V����
{
	mCharOrderCount = 0;
	mCounter++;
	mFont = GetDrawFormatStringWidth("%d", mScore);
	mFontHigh = GetDrawFormatStringWidth("%d", mParent->mHighScore);
	mFontkill = GetDrawFormatStringWidth("%d", mKillCount);
	if (mMapChange == true)
	{
		ScreenEffect(SceneId::SCENE_BATTOL);
		return false;
	}
	if (mScene_id == SceneId::SCENE_BATTOL && GameScene::ScreenEffect(SceneId::SCENE_SHOP))
	{
		mPlayer.UpDate();  //���@�̍X�V
		AddCharOrder(mPlayer.mPosBottom, mCharOrderCount, CHAR_TYPE::PLAYER); //�v���C���[�̑������W
		for (int e = 0; e < ENEMY_COUNT; e++)
		{
			mEnemy[e].UpDate(mPlayer.GetPos());
			AddCharOrder(mEnemy[e].mPosBottom, e, CHAR_TYPE::ENEMY); //�G�̕��ёւ�
		}

		for (int s = 0; s < SHOT_COUNT; s++)
		{
			mShot[s].UpDate();//�e�̍X�V
		}

		for (int i = 0; i < ITEM_COUNT; i++)
		{
			mItem[i].UpDate(mPlayer.GetOffsetPos());
		}

		mStage.UpDate();   //�}�b�v�̍X�V
		if (mPlayer.IsShot())
		{
			for (int m = 0; m < SHOT_COUNT; m++)
			{
				if (mShot[m].IsAlive() == 0)
				{
					mShot[m].CreateShot(mPlayer.GetPos(), mPlayer.GetDir(), CHAR_TYPE::PLAYER, 0);
					PlaySoundMem(mSePshot, DX_PLAYTYPE_BACK);
					break;
				}
			}
		}
		if (mPlayer.IsWayShot() && mWay > 0)
		{
			for (int m = 0; m < SHOT_COUNT; m++)
			{
				if (mShot[m].IsAlive() == 0)
				{
					mShot[m].CreateShot(mPlayer.GetPos(), mPlayer.GetDir(), CHAR_TYPE::PLAYER, 0);
					mShot[m % SHOT_COUNT + 1].CreateShot(mPlayer.GetPos(), mPlayer.GetDir(), CHAR_TYPE::PLAYER, 1);
					mShot[m % SHOT_COUNT + 2].CreateShot(mPlayer.GetPos(), mPlayer.GetDir(), CHAR_TYPE::PLAYER, 2);
					mWay--;
					PlaySoundMem(mSeWay, DX_PLAYTYPE_BACK);
					break;
				}
			}
		}
		for (int r = 0; r < ENEMY_COUNT; r++)
		{
			if (rand() % 300 == 0)
			{
				for (int m = 0; m < SHOT_COUNT; m++)
				{
					if (mShot[m].IsAlive() == 0)
					{
						PlaySoundMem(mSeEshot, DX_PLAYTYPE_BACK);
						mShot[m].CreateShot(mEnemy[r].GetPos(), mEnemy[r].GetDir(), CHAR_TYPE::ENEMY, 0);
						break;
					}
				}
			}
		}
		for (int r = 0; r < ENEMY_COUNT; r++)
		{
			mLifeBar[r].UpDate(mEnemy[r].GetPos());//HP�o�[(�G)�̍X�V
		}
		for (int g = 0; g < ENEMY_COUNT; g++) //�e�ƓG�̓����蔻��
		{
			for (int s = 0; s < SHOT_COUNT; s++)
			{
				if (mShot[s].IsAlive() > 0 && mEnemy[g].IsAlive() > 0 && mShot[s].mCharType == CHAR_TYPE::PLAYER)
				{
					if (mEnemy[g].Collsion(mShot[s].GetPos(), mShot[s].GetSize()))
					{
						mShot[s].Destroy();
						mEnemy[g].Destroy();
						PlaySoundMem(mSeHit, DX_PLAYTYPE_BACK);
						if (mEnemy[g].IsAlive() <= 0)
						{
							PlaySoundMem(mSeKill, DX_PLAYTYPE_BACK);
							for (int i = 0; i < ITEM_COUNT; i++)
							{
								if (!mItem[i].IsAlive()/* && rand() % 10*/)
								{
									mKillCount++;
									mItem[i].SetItem(mEnemy[g].GetPos());
									break;
								}
							}
						}
						for (int y = 0; y < SCORE_COUNT; y++)
						{
							if (!mPoint[y].IsAlive())
							{
								mScore += mPoint[y].AddScore(mEnemy[g].GetType(), mEnemy[g].GetPos(), mEnemy[g].IsAlive());
								break;
							}
						}
					}
				}
			}
		}
		for (int s = 0; s < SHOT_COUNT; s++)
		{
			if (mPlayer.IsAlive() > 0 && mShot[s].IsAlive() > 0 && mShot[s].mCharType == CHAR_TYPE::ENEMY)
			{
				if (mPlayer.Collsion(mShot[s].GetPos(), mShot[s].GetSize()))
				{
					mShot[s].Destroy();
					PlaySoundMem(mSeDamage, DX_PLAYTYPE_BACK);
					if (mPlayer.mShield <= 0)
					{
						mPlayer.Destroy();
					}
					else
					{
						mPlayer.S_Destroy();
					}
					break;
				}
			}
		}
		for (int s = 0; s < ITEM_COUNT; s++)
		{
			if (mPlayer.IsAlive() > 0 && mItem[s].IsAlive() == true)
			{
				if (mPlayer.Collsion(mItem[s].GetPos(), mItem[s].GetSize()))
				{
					PlaySoundMem(mSeCoin, DX_PLAYTYPE_BACK);
					mCoin += rand() % 200 + 100;
					mItem[s].Destroy();
					break;
				}
			}
		}
		for (int b = 0; b < SCORE_COUNT; b++)
		{
			mPoint[b].UpDate();
		}
		Vector2 enemyPos;
		if (mNextMapID == MAP_ID::NORMAL)
		{
			enemyPos = { 610, 200 };
			for (int g = 0; g < ENEMY_COUNT; g++)
			{
				if (mEnemy[g].IsAlive() <= 0)
				{
					Born(enemyPos, g);   // 700 640
					break;
				}
			}
		}
		else if (mNextMapID == MAP_ID::MAZE)
		{
			enemyPos = { 690, 440 };
			for (int g = 0; g < ENEMY_COUNT; g++)
			{
				if (mEnemy[g].IsAlive() <= 0)
				{
					Born(enemyPos, g);   // 700 640
					break;
				}
			}
		}
	}
	else if (mScene_id == SceneId::SCENE_SHOP && ScreenEffect(SceneId::SCENE_BATTOL))
	{
		if (mShop.UpDate())
		{
			mFadeOut = true;
		}
	}
	Vector2 shopPos = { 1270 ,400 };
	Vector2 shopSize = { 64 ,64 };
	if (mPlayer.Collsion(shopPos, shopSize))
	{
		PlaySoundMem(mSeDoor, DX_PLAYTYPE_BACK);
		mPlayer.UndoPos();
		mFadeOut = true;
	}
	if (mPlayer.IsAlive() <= 0)
	{
		return true;
	}
	return false;
}

void GameScene::Draw(void)  //�C���X�^���X�̕`�揈��
{
	SetDrawScreen(DX_SCREEN_BACK);                  //�o�b�N�o�b�t�@�ɐݒ�
	ClsDrawScreen();                                //��ʏ���
	//DrawBox(50, 50, 600, 440, GetColor(0, 255, 0), 1);
	if (mScene_id == SceneId::SCENE_BATTOL)
	{
		mOffset = mPlayer.GetOffsetPos();
		mStage.Draw(mOffset);//�}�b�v�̕`��
		for (int s = 0; s < SHOT_COUNT; s++)
		{
			mShot[s].Draw(mOffset);//�e�̕`��
		}

		for (int c = 0; c < ENEMY_COUNT + 1; c++)
		{
			switch (mCharOrder[c].mCharType)   //�L�����N�^�[�̕`��
			{
			case CHAR_TYPE::PLAYER:
				mPlayer.Draw();
				break;
			case CHAR_TYPE::ENEMY:
				mEnemy[mCharOrder[c].mCharIndex].Draw(mOffset);
				break;
			default:
				break;
			}
		}

		for (int r = 0; r < ENEMY_COUNT; r++)
		{
			mLifeBar[r].Draw(mEnemy[r].IsAlive(), mOffset);//HP�o�[�̕`��
		}
		for (int i = 0; i < ITEM_COUNT; i++)
		{
			mItem[i].Draw();
		}
		if (mScore > mParent->mHighScore)
		{
			mParent->mHighScore = mScore;
		}
		for (int b = 0; b < SCORE_COUNT; b++)
		{
			mPoint[b].Draw(mOffset);//���_�̕`��
		}
		DrawExtendGraph(1270 - mOffset.x - 32, 400 - mOffset.y - 32, 1270 - mOffset.x + 32, 400 - mOffset.y + 32, mShop.mShopImage, true); //1230 390
		if (mWay > 0)
		{
			DrawGraph(mPlayer.GetPos().x - mOffset.x - mPlayer.GetSize().x, mPlayer.GetPos().y - mOffset.y - mPlayer.GetSize().y - 10, mItemImage[0], true);
			DrawFormatString(mPlayer.GetPos().x - mOffset.x - mPlayer.GetSize().x + 17, mPlayer.GetPos().y - mOffset.y - mPlayer.GetSize().y - 10, GetColor(255, 255, 0), "%d", mWay);
		}
	}
	else if (mScene_id == SceneId::SCENE_SHOP)
	{
		mShop.Draw();
	}
	DrawBox(585, 50, 640, 66, GetColor(25, 25, 25), true);
	DrawBox(mScreenSizeX - mFont - 5, 96, mScreenSizeX, 80, GetColor(25, 25, 25), true);
	DrawString(590, 50, "Score", GetColor(213, 115, 50));
	DrawFormatString(mScreenSizeX - mFont, 80, GetColor(213, 115, 50), "%d", mScore);
	DrawBox(555, 100, 640, 116, GetColor(25, 25, 25), true);
	DrawBox(mScreenSizeX - mFontHigh - 5, 130, mScreenSizeX, 146, GetColor(25, 25, 25), true);
	DrawString(560, 100, "HighScore", GetColor(63, 115, 150));
	DrawFormatString(mScreenSizeX - mFontHigh, 130, GetColor(63, 115, 150), "%d", mParent->mHighScore);
	DrawBox(570, 158, mScreenSizeX, 178, GetColor(25, 25, 25), 1);
	DrawString(570, 160, "�|������", GetColor(133, 3, 133));
	DrawBox(mScreenSizeX - mFontkill - 5, 180, mScreenSizeX, 196, GetColor(25, 25, 25), 1);
	DrawFormatString(mScreenSizeX - mFontkill, 180, GetColor(133, 3, 133), "%d", mKillCount);
	DrawBox(mScreenSizeX / 4, 0, mScreenSizeX / 4 * 3 - 20, 16, GetColor(25, 25, 25), 1);
	DrawGraph(mScreenSizeX / 4 + 5, 0, mItemImage[1], true);
	DrawGraph(mScreenSizeX / 4 + 110, 0, mItemImage[2], true);
	DrawGraph(mScreenSizeX / 4 + 200, 0, mItemImage[3], true);
	DrawFormatString(mScreenSizeX / 4 + 5, 0, GetColor(200, 0, 0), "   * %d", mPlayer.mLife);
	DrawFormatString(mScreenSizeX / 4 + 110, 0, GetColor(200, 0, 0), "   * %d", mPlayer.mShield);
	DrawFormatString(mScreenSizeX / 4 + 200, 0, GetColor(200, 0, 0), "   * %d", mCoin);
	if (mWay > 30)//3way��30��܂�
	{
		mWay = 30;
	}
}

bool GameScene::Release(void) //�C���X�^���X�̊J������
{
	if (!mShop.Release()) return false;
	for (int b = 0; b < SCORE_COUNT; b++)
	{
		if (!mPoint[b].Release()) return false;
	}
	for (int e = 0; e < ENEMY_COUNT; e++)
	{
		if (!mLifeBar[e].Release()) return false;
		if (!mEnemy[e].Release()) return false;
	}
	if (!mPlayer.Release()) return false;
	for (int s = 0; s < SHOT_COUNT; s++)
	{
		if (!mShot[s].Release()) return false;
	}
	if (!mStage.Release()) return false;
	//�A�C�e���摜�̊J��
	for (int i = 0; i < ITEM_IMAGE_COUNT; i++)
	{
		DeleteGraph(mItemImage[i]);
	}
	//���C�t�o�[�摜�̊J��
	for (int r = 0; r < LIFE_ANIM_COUNT; r++)
	{
		DeleteGraph(mLifeBarImage[r]);
	}
	//�G�̉摜�̊J��
	for (int s = 0; s < ENEMY_TYPE_MAX; s++)
	{
		for (int e = 0; e < ENEMY_ANIM_COUNT * (int)DIR::DIR_MAX; e++)
		{
			DeleteGraph(mEnemyImage[s][e]);
		}
	}
	//�e�̉摜�̊J��
	for (int s = 0; s < SHOT_IMAGE_COUNT; s++)
	{
		DeleteGraph(mP_ShotImage[s]);
		DeleteGraph(mE_ShotImage[s]);
	}
	DeleteSoundMem(mSeWay);
	DeleteSoundMem(mSeHit);
	DeleteSoundMem(mSeKill);
	DeleteSoundMem(mSePshot);
	DeleteSoundMem(mSeEshot);
	DeleteSoundMem(mSeCoin);
	DeleteSoundMem(mSeBuy);
	DeleteSoundMem(mSeDoor);
	DeleteSoundMem(mSeDamage);
	SaveData();
	return true;
}

int GameScene::GetEvent(Vector2 pos)//�v���C���[��������}�b�v�̏��
{
	int mapChipID;

	mapChipID = mStage.GetMapChip(pos);
	if (mapChipID == 15) //�v���C���[���K�i�ɏ������
	{
		mNextPos.x = 100;
		mNextPos.y = 100;
		mNextOffsetPos.y = 0;
		mNextOffsetPos.x = 0;
		mMapChange = true;
		mFadeOut = true;
		ScreenEffect(SceneId::SCENE_BATTOL);
	}

	return mapChipID;
}

void GameScene::Born(Vector2 targetPos, int Index)//�G�������Ԃ�
{
	int enemyType;
	enemyType = rand() % ENEMY_TYPE_MAX;
	mEnemy[Index].Init(this, enemyType, mScreenSizeX, mScreenSizeY, targetPos);  //�G�̏�����
}

bool GameScene::LoadEnemyImage(void)//�G�̉摜�̓ǂݍ���
{
	const char* ENEMY_NAME[ENEMY_TYPE_MAX] = {
		"image/enemy0.bmp",    //�X���C��
		"image/enemy1.bmp",    //�I
		"image/enemy2.bmp",    //��
		"image/enemy3.bmp",    //�h���S����
		"image/enemy4.bmp",    //�h���S����
		"image/enemy5.bmp"     //�{�X
	};
	const int SizeX[ENEMY_TYPE_MAX] = {                   //�G�̉��T�C�Y
		24,24,24,24,48,96
	};
	const int SizeY[ENEMY_TYPE_MAX] = {                   //�G�̏c�T�C�Y
		32,32,32,32,64,128
	};
	for (int e = 0; e < ENEMY_TYPE_MAX; e++)
	{
		if ((LoadDivGraph(ENEMY_NAME[e], ENEMY_ANIM_COUNT * (int)DIR::DIR_MAX, ENEMY_ANIM_COUNT, (int)DIR::DIR_MAX, SizeX[e], SizeY[e], &mEnemyImage[e][0])) == -1)
		{
			return false;
		}
	}
	return true;
}

bool GameScene::LoadShotImage(void)  //�e�̉摜�̓ǂݍ���
{
	const int sizeX = 12;
	const int sizeY = 12;

	if ((LoadDivGraph("image/shot.bmp", SHOT_IMAGE_COUNT, SHOT_IMAGE_COUNT, 1, sizeX, sizeY, &mP_ShotImage[0])) == -1)
	{
		return false;
	}
	if ((LoadDivGraph("image/bullet.bmp", SHOT_IMAGE_COUNT, SHOT_IMAGE_COUNT, 1, sizeX, sizeY, &mE_ShotImage[0])) == -1)
	{
		return false;
	}
	return true;
}

bool GameScene::LoadLifeBarImage(void) //���C�t�o�[�̉摜�̓ǂݍ���
{
	const int sizeX = 24;
	const int sizeY = 10;

	if ((LoadDivGraph("image/bar.png", LIFE_ANIM_COUNT, 1, LIFE_ANIM_COUNT, sizeX, sizeY, &mLifeBarImage[0])) == -1)
	{
		return false;
	}
	return true;
}

bool GameScene::GameInit(void) //�Q�[���̏�����
{
	mWay = 10;
	mScene_id = SceneId::SCENE_BATTOL;
	mFadeOut = false;
	mFadeIn = false;
	mCoin = 0;
	mKillCount = 0;
	mNextMapID = MAP_ID::MAZE;
	mMapChange = false;
	Vector2 enemyPos;     //�G�̍��W
	int enemyType;
	LoadData();
	mScore = 0;
	mFont = GetDrawFormatStringWidth("%d", mScore);
	mFontHigh = GetDrawFormatStringWidth("%d", mParent->mHighScore);
	mCharOrderCount = 0;

	mCounter = 0;
	mColor = 255;
	mStage.SetMap(MAP_ID::NORMAL); //�}�b�v�̏�����
	for (int s = 0; s < SHOT_COUNT; s++)
	{
		if (!mShot[s].Init(this, mScreenSizeX, mScreenSizeY)) return false; //�e�̏�����
	}
	if (!mPlayer.GameInit()) return false; //�v���C���[�̏�����
	AddCharOrder(mPlayer.mPosBottom, mCharOrderCount, CHAR_TYPE::PLAYER); //�v���C���[�̑������W
	if (!mLifeBar[0].init(this, 0)) return false;  //HP�o�[�i�v���C���[�j�̏�����
	for (int e = 0; e < ENEMY_COUNT; e++)
	{
		mCharOrder[e + 1].mCharType = CHAR_TYPE::ENEMY;
		enemyPos.x = rand() % 500 + 200;
		enemyPos.y = rand() % 500 + 200;
		enemyType = rand() % (ENEMY_TYPE_MAX - 1);
		if (!mEnemy[e].Init(this, enemyType, mScreenSizeX, mScreenSizeY, enemyPos)) return false;  //�G�̏�����
		if (!mLifeBar[e + 1].init(this, enemyType)) return false;                       //HP(�G)�o�[�̏�����
		AddCharOrder(mEnemy[e].mPosBottom, e, CHAR_TYPE::ENEMY); //�G�̕��ёւ�
	}
	for (int b = 0; b < SCORE_COUNT; b++) //�|�C���g�̏�����
	{
		if (!mPoint[b].Init()) return false;
	}
	for (int i = 0; i < ITEM_COUNT; i++)
	{
		if (!mItem[i].Init(this)) return false;
	}

	return true;
}

bool GameScene::LoadItemImage(void) //�A�C�e���̉摜�̓ǂݍ���
{
	if ((LoadDivGraph("image/item.png", ITEM_IMAGE_COUNT, ITEM_IMAGE_COUNT, 1, 16, 16, &mItemImage[0])) == -1)
	{
		return false;
	}
	return true;
}

bool GameScene::SaveData(void)//�Z�[�u����
{
	//�f�[�^�̕ۑ�
	//�Z�[�u����
	errno_t err;
	FILE* fp;
	int numwritten;

	// Open for write
	err = fopen_s(&fp, mFlieName, "w");
	if (err == 0)
	{
		//printf("The file 'data2' was opened\n");
		//�I�[�v������
		err = 10;

		//�f�[�^�̏�������
		//numwritten = fwrite("abcd", 5, 1, fp);
		//�X�R�A�̕ۑ�
		numwritten = fwrite(&mParent->mHighScore, 4, 1, fp);

		err = fclose(fp);
		if (err == 0)
		{
			//�N���[�Y����
			return true;
			///printf("The file 'crt_fopen_s.c' was closed\n");
		}
		else
		{
			//�N���[�Y���s
			return false;
			///printf("The file 'crt_fopen_s.c' was not closed\n");
		}
	}
	else
	{
		//�I�[�v�����s
		//printf("The file 'data2' was not opened\n");
		err = 100;
		return false;
	}
	return true;
}

bool GameScene::LoadData(void)//�ǂݍ��ݏ���
{
	//�f�[�^�̓ǂݍ���
	//���[�h����
	errno_t err;
	FILE* fp;
	int numread;

	// Open for read
	err = fopen_s(&fp, mFlieName, "r");
	if (err == 0)
	{
		//printf("The file 'data2' was opened\n");
		//�I�[�v������
		err = 10;

		//�f�[�^�̓ǂݍ���
		//numwritten = fwrite("abcd", 5, 1, fp);
		//�X�R�A�̕ۑ�
		numread = fread(&mParent->mHighScore, 4, 1, fp);

		err = fclose(fp);
		if (err == 0)
		{
			//�N���[�Y����
			///printf("The file 'crt_fopen_s.c' was closed\n");
			return true;
		}
		else
		{
			//�N���[�Y���s
			///printf("The file 'crt_fopen_s.c' was not closed\n");
			return false;
		}
	}
	else
	{
		//printf("The file 'data2' was not opened\n");
		err = 100;
		return false;
	}
	return true;
}

void GameScene::AddCharOrder(int bottomPos, int index, CHAR_TYPE charType)   //�G�̕��ѕς�����
{
	//�l�̎擾
	mCharOrder[mCharOrderCount].mCharType = charType;
	mCharOrder[mCharOrderCount].mCharIndex = index;
	mCharOrder[mCharOrderCount].mPosBottom = bottomPos;
	//���ёւ�
	CharOrder wk;
	for (int g = mCharOrderCount; g > 0; g--)
	{
		if (mCharOrder[g].mPosBottom < mCharOrder[g - 1].mPosBottom)
		{
			wk = mCharOrder[g];
			mCharOrder[g] = mCharOrder[g - 1];
			mCharOrder[g - 1] = wk;
		}
		else
		{
			break;
		}
	}
	mCharOrderCount++;
}

bool GameScene::ScoreSet(void)//�X�R�A�̃��Z�b�g
{
	//�n�C�X�R�A�̃��Z�b�g
	mParent->mHighScore = HIGH_SCORE;

	//�f�[�^�̕ۑ�
	//�Z�[�u����
	errno_t err;
	FILE* fp;
	int numwritten;

	// Open for write
	err = fopen_s(&fp, mFlieName, "w");
	if (err == 0)
	{
		//printf("The file 'data2' was opened\n");
		//�I�[�v������
		err = 10;

		//�f�[�^�̏�������
		//numwritten = fwrite("abcd", 5, 1, fp);
		//�X�R�A�̕ۑ�
		numwritten = fwrite(&mParent->mHighScore, 4, 1, fp);

		err = fclose(fp);
		if (err == 0)
		{
			//�N���[�Y����
			return true;
			///printf("The file 'crt_fopen_s.c' was closed\n");
		}
		else
		{
			//�N���[�Y���s
			return false;
			///printf("The file 'crt_fopen_s.c' was not closed\n");
		}
	}
	else
	{
		//�I�[�v�����s
		//printf("The file 'data2' was not opened\n");
		err = 100;
		return false;
	}
	return true;
}

int GameScene::GetScore(void) //�X�R�A��Ԃ�
{
	return mScore;
}

bool GameScene::ScreenEffect(SceneId nextSceneID)
{
	SetDrawBright(mColor, mColor, mColor);              //����  nextSceneID�F���̃V�[���h�c
	if (mFadeOut == false && mFadeIn == false)
	{
		return true;
	}
	if (mFadeIn == true)
	{
		mColor += 5;
	}
	if (mFadeOut == true)
	{
		mColor -= 5;
	}
	if (mColor <= 0)
	{
		if (mMapChange == true)//�}�b�v�̐؂�ւ����K�v���ǂ������`�F�b�N����
		{
			switch (mNextMapID)
			{
			case MAP_ID::NORMAL:
				mStage.SetMap(mNextMapID);
				mNextMapID = MAP_ID::MAZE;
				break;
			case MAP_ID::MAZE:
				mStage.SetMap(mNextMapID);
				mNextMapID = MAP_ID::NORMAL;
				break;
			default:
				break;
			}
			mPlayer.SetPos(mNextPos, mNextOffsetPos);
		}
		mShop.GameInit(this);
		mFadeOut = false;
		mFadeIn = true;
		mScene_id = nextSceneID;
	}
	if (mColor >= 255)
	{
		if (mMapChange == true)
		{
			mMapChange = false;
		}
		mFadeIn = false;
	}
	return false;
}

void GameScene::BuyItem(ITEM_TYPE itemType)//�A�C�e���̍w������
{
	switch (itemType)
	{
	case ITEM_TYPE::SHIELD:
		mPlayer.GetShield();
		break;
	case ITEM_TYPE::HEART:
		mPlayer.GetHeart();
		break;
	case ITEM_TYPE::WAY:
		mWay += 10;
		break;
	default:
		break;
	}
}