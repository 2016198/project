//#pragma once
#include "GameScene.h"
#include "TitleScene.h"
#include "GameOver.h"
//#include "GameClear.h"

enum class SCENE_ID {
	TITLE_SCENE,           //0�F�^�C�g���V�[��
	GAME_SCENE,            //1�F�Q�[���V�[��
	GAME_OVER_SCENE,       //2�F�Q�[���I�[�o�[�V�[��
	GAME_CLEAR_SCENE,      //3�F�Q�[���N���A�[�V�[��
	MAX_SCENE              //4�F�V�[���̍ő�l
};

class SceneManager
{
private:                           //�����o�[�ϐ�
	int mScreenSizeX;              //��ʂ�X�T�C�Y
	int mScreenSizeY;              //��ʂ�Y�T�C�Y
	int mColor;                    //�F�̖��邳
	bool mFadeOut;                 //true�FfadeOut��
	bool mFadeIn;                  //true�FfadeIn��
	SCENE_ID mSceneID;             //�V�[���̐�`
	                               //�C���X�^���X�̐���
	GameScene mGamescene;
	TitleScene mTitlescene;
	GameOver mGameover;
	//GameClear gameclear;
	//�����o�[�֐�(�V�[���}�l�[�W���[�������g����)
	bool ScreenEffect(SCENE_ID nextSceneID);      //��ʐ؂�ւ����ɃG�t�F�N�g���s��

public:                                                       //�����o�[�֐�
	bool ScoreReset(void);								      //�X�R�A�̃��Z�b�g
	int mHighScore;		                                      //�n�C�X�R�A
	bool Init(int ScreenSizeX, int ScreenSizeY);              //�C���X�^���X�̐���������
	void Run(void);                                           //�C���X�^���X�̎��s����
	bool Release(void);                                       //�C���X�^���X�̊J������
};