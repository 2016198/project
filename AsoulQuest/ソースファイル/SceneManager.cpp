#include "SceneManager.h"
#include "DxLib.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "KeyCheck.h"

bool SceneManager::Init(int ScreenSizeX, int ScreenSizeY)  //�C���X�^���X�̐���
{
	//�e�평��������
	mScreenSizeX = ScreenSizeX;
	mScreenSizeY = ScreenSizeY;
	mSceneID = SCENE_ID::TITLE_SCENE;
	mColor = 0;
	mFadeOut = false;
	mFadeIn = true;
	//�C���X�^���X�̏�����
	if (!mGamescene.Init(mScreenSizeX, mScreenSizeY, this)) return false;
	if (!mTitlescene.Init(mScreenSizeX, mScreenSizeY, this)) return false;
	if (!mGameover.Init(mScreenSizeX, mScreenSizeY)) return false;
	//if (!gameclear.Init()) return false;
	return true;
}
 
void SceneManager::Run(void)   //�C���X�^���X�̎��s����
{
	//if (gamescene.GameOver())
	//{
	//	sceneID = GAME_OVER_SCENE;
	//	if (!gamescene.GameInit()) return -1;           //�Q�[���I�[�o�[��̏���
	//	if (!titlescene.GameInit()) return -1;
	//}
	switch (mSceneID)
	{
	case  SCENE_ID::TITLE_SCENE:
		if (ScreenEffect(SCENE_ID::GAME_SCENE))
		{
			if (mTitlescene.UpDate() && mFadeIn == false && mFadeOut == false)                        //�^�C�g���V�[���X�V����
			{
				mColor = 255;
				mGameover.GameInit();
				mFadeOut = true;
			}
		}
		mTitlescene.Draw();                              //�^�C�g���V�[���`�揈��
		break;
	case  SCENE_ID::GAME_SCENE:
		if (ScreenEffect(SCENE_ID::GAME_OVER_SCENE))
		{
			if (mGamescene.UpDate() && mFadeIn == false && mFadeOut == false)                         //�Q�[���V�[���X�V����
			{
				mColor = 255;
				mTitlescene.GameInit();
				mFadeOut = true;
			}
		}
		mGamescene.Draw();                  //�Q�[���V�[���`�揈��
		break;
	case  SCENE_ID::GAME_OVER_SCENE:
		if (ScreenEffect(SCENE_ID::TITLE_SCENE))
		{
			if (mGameover.UpDate() && mFadeIn == false && mFadeOut == false)                          //�Q�[���I�[�o�[�V�[���X�V����
			{
				mColor = 255;
				mGamescene.GameInit();
				mFadeOut = true;
			}
		}
		mGameover.Draw(mGamescene.GetScore());                                //�Q�[���I�[�o�[�V�[���`�揈��
		break;
		//case GAME_CLEAR_SCENE:
		//	gameclear.UpDate();
		//	gameclear.Draw(gamescene.Score());
		//	if (gameclear.SceneChenge())
		//	{
		//		gameclear.Reset();
		//		if (!gamescene.GameInit()) return -1;           //�Q�[���N���A�[��̏���
		//		if (!titlescene.GameInit()) return -1;
		//		sceneID = TITLE_SCENE;
		//	}
		//	break;
	default:
		break;
	}
}

bool SceneManager::Release(void)  //�C���X�^���X�̊J������
{
	//if (!gameclear.Release()) return false;
	if (!mGameover.Release()) return false;
	if (!mTitlescene.Release())return false;
	if (!mGamescene.Release()) return false;
	return true;
}

bool SceneManager::ScreenEffect(SCENE_ID nextSceneID)   //��ʐ؂�ւ����ɃG�t�F�N�g���s��
{                                                       //�G�t�F�N�g���s���F�߂�l = true
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
		mFadeOut = false;
		mFadeIn = true;
		mSceneID = nextSceneID;
	}
	if (mColor >= 255)
	{
		mFadeIn = false;
	}
	return false;
}

bool SceneManager::ScoreReset(void)
{
	if (!mGamescene.ScoreSet()) return false;
	return true;
}
