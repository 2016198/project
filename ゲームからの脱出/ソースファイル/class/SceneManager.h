//#pragma once
#include "GameScene.h"
#include "GameClearScene.h"
#include "TitleScene.h"

#define lpSceneManager SceneManager::GetInstance()	//�V���O���g�[��

enum class SCENE_ID
{
	TITLE,
	GAME,
	CLEAR,
	MAX
};

class SceneManager
{
public:
	bool Init(void);			//����������
	bool Run(void);				//���s����
	bool Release(void);			//�������

	bool FadeInOut(SCENE_ID next);

	static SceneManager& GetInstance()	//�V���O���g�[��
	{
		static SceneManager mSceneManger;
		return mSceneManger;
	}

private:
	SCENE_ID now;	//���݂̃V�[��

	TitleScene mTitleScene;
	GameScene mGameScene;
	GameClearScene mClearScene;
	Stage mStage;

	int brightValue_;	//�P�x�l�̊i�[�̈�
	bool fadeOut_;		//true:�t�F�[�h�A�E�g��
	bool fadeIn_;		//true:�t�F�[�h�C����

	double count;

	//���y�i�[�p�ϐ�
	int title;
	int clear;
	int escapeSE;
	int notSafeKey;
	int solveSE;

	void SoundInit(void);			//�T�E���h�̃��[�h��������
	void ReleaseSound(void);		//�T�E���h�n���h���̊J��
};