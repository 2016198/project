#include <DxLib.h>			
#include "KeyCheck.h"
#include "SceneManager.h"

bool SceneManager::Init(void)
{
	now = SCENE_ID::TITLE;
	brightValue_ = 0;		
	fadeOut_ = false;			
	fadeIn_ = true;		

	SoundInit();

	if (!mTitleScene.Init())
	{
		return false;
	}

	if (!mGameScene.Init())
	{
		return false;
	}	

	if (!mClearScene.Init())
	{
		return false;
	}	

	return true;

}
bool SceneManager::Run(void)
{
	SetDrawScreen(DX_SCREEN_BACK);	//�`�悷���ʂ𗠂̉�ʂɐݒ�
	ClearDrawScreen();				//�`�悷���ʂ̓��e������

	switch (now)
	{
	case SCENE_ID::TITLE:

		if (!FadeInOut(SCENE_ID::GAME))
		{
			if (!mTitleScene.Update())
			{
				fadeOut_ = true;
				mGameScene.Init();
			}
		}
		SetDrawBright(brightValue_, brightValue_, brightValue_);

		mTitleScene.Draw();
		break;
	case SCENE_ID::GAME:

		if (!FadeInOut(SCENE_ID::CLEAR))
		{
			if (!mGameScene.Update())
			{
				StopSoundMem(title);
				PlaySoundMem(escapeSE, DX_PLAYTYPE_BACK, true);

				WaitTimer(500);	//0.5�b�҂�

				PlaySoundMem(clear, DX_PLAYTYPE_LOOP, true);

				fadeOut_ = true;
			}
		}
		SetDrawBright(brightValue_, brightValue_, brightValue_);

		if (mGameScene.SafeCheck())
		{
			PlaySoundMem(notSafeKey, DX_PLAYTYPE_BACK, true);
		}

		if (mGameScene.ClearCheck())
		{
 			PlaySoundMem(solveSE, DX_PLAYTYPE_BACK, true);
		}

		mGameScene.Draw();

		break;
	case SCENE_ID::CLEAR:
		if (!FadeInOut(SCENE_ID::TITLE))
		{
			if (!mClearScene.Update())
			{
				fadeOut_ = true;
				StopSoundMem(clear);
				if (CheckSoundMem(title) == 0)
				{
					PlaySoundMem(title, DX_PLAYTYPE_BACK, true);
				}
			}
		}

		SetDrawBright(brightValue_, brightValue_, brightValue_);
		mClearScene.Draw();

		break;
	}

	ScreenFlip();	//���̉�ʂ�\�̉�ʂɏu�ԃR�s�[

	return true;
}
bool SceneManager::Release(void)
{
	mTitleScene.Release();
	mGameScene.Release();
	mClearScene.Release();
	ReleaseSound();
	return true;

}

void SceneManager::SoundInit(void)
{
	title = LoadSoundMem("sound/bgm/�����v�̋u.mp3");
	ChangeVolumeSoundMem(100, title);
	PlaySoundMem(title, DX_PLAYTYPE_LOOP, true);

	clear = LoadSoundMem("sound/bgm/�Ȃ�Ƃ������Ƃ͂Ȃ�����.mp3");
	ChangeVolumeSoundMem(100, clear);

	escapeSE = LoadSoundMem("sound/se/���[�v.mp3");
	ChangeVolumeSoundMem(100, escapeSE);

	notSafeKey = LoadSoundMem("sound/se/�G���[.mp3");
	ChangeVolumeSoundMem(100, notSafeKey);

	solveSE = LoadSoundMem("sound/se/�s���|��.mp3");
	ChangeVolumeSoundMem(100, solveSE);

}

void SceneManager::ReleaseSound(void)
{
	DeleteSoundMem(solveSE);
	DeleteSoundMem(notSafeKey);
	DeleteSoundMem(escapeSE);
	DeleteSoundMem(clear);
	DeleteSoundMem(title);
}

bool SceneManager::FadeInOut(SCENE_ID next)
{
	bool returnValue = true;
	if (fadeIn_)
	{
		brightValue_ += 5;
		if (brightValue_ > 255)
		{
			fadeIn_ = false;
			returnValue = false;
		}
	}
	else if (fadeOut_)
	{
		brightValue_ -= 5;
		if (brightValue_ < 0)
		{
			fadeOut_ = false;
			now = next;
			fadeIn_= true;
			returnValue = false;
		}
	}
	else
	{
		returnValue = false;
	}
	return returnValue;

}
