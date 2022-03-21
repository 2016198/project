#pragma once
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Shot.h"
#include "LifeBar.h"
#include "Score.h"
#include "Item.h"
#include "Shop.h"
#include "Vector2.h"
#include "CharOrder.h"

//�e�̃N���X�i�[�ϐ�
class SceneManager;

enum class SceneId //���ǂ��̃V�[����
{
	SCENE_BATTOL,
	SCENE_SHOP
};

class GameScene
{
private:                            //�����o�[�ϐ�
	SceneManager* mParent;          //�e�̊i�[�ϐ�
	int mScreenSizeX;               //��ʂ�X�T�C�Y
	int mScreenSizeY;               //��ʂ�Y�T�C�Y
	int mCounter;                   //�Q�[���J�E���^�[
	bool mFadeOut;                  //true�FfadeOut��
	bool mFadeIn;                   //true�FfadeIn��
	int mColor;                     //�F�̖��邳
	SceneId mScene_id;				//���݂̃V�[��
	int mWay;						//3way�V���b�g�����Ɖ��񌂂Ă邩�ǂ���
	bool ScreenEffect(SceneId nextSceneID);      //��ʐ؂�ւ����ɃG�t�F�N�g���s��

							//�C���X�^���X�̐���
	Stage mStage;			//�}�b�v���̃C���X�^���X����
	Player mPlayer;			//�v���C���[���̃C���X�^���X����
	Shot mShot[SHOT_COUNT]; //�V���b�g���̃C���X�^���X����
	Enemy mEnemy[ENEMY_COUNT]; //�G���̃C���X�^���X����
	LifeBar mLifeBar[ENEMY_COUNT];//���C�t�o�[���̃C���X�^���X����
	Score mPoint[SCORE_COUNT];        //�X�R�A���̃C���X�^���X����
	Item mItem[ITEM_COUNT];			  //�A�C�e�����̃C���X�^���X����
	Shop mShop;						  //�V���b�v���̃C���X�^���X����
	
	Vector2 mOffset;           //�I�t�Z�b�g�̊i�[�ϐ�

	int mScore;			//�X�R�A
	int mFont;			//�X�R�A�̃t�H���g�T�C�Y
	int mFontHigh;		//�n�C�X�R�A�̃t�H���g�T�C�Y
	int mKillCount;		//�G��|������
	int mFontkill;		//�t�H���g�T�C�Y�|������
	int mSeWay;			//�T�E���h�n���h��
	int mSeHit;			//�T�E���h�n���h��
	int mSeKill;		//�T�E���h�n���h��
	int mSePshot;		//�T�E���h�n���h��
	int mSeEshot;		//�T�E���h�n���h��
	int mSeCoin;		//�T�E���h�n���h��
	int mSeDamage;		//�T�E���h�n���h��

	//�L�����N�^�[�̕��ёւ�
	CharOrder mCharOrder[ENEMY_COUNT + 1];  //�L�����N�^�[�̕��ѕς��p�I�[�_�[
	int mCharOrderCount;					//�L�����N�^�[�I�[�_�[�J�E���g

	//�}�b�v�ړ��p�ϐ�
	bool mMapChange;				//�}�b�v�̐؂�ւ�
	MAP_ID mNextMapID;				//���̃}�b�vID
	Vector2 mNextPos;				//���̃}�b�v�̍��W
	Vector2 mNextOffsetPos;			//���̃I�t�Z�b�g�}�b�v�̍��W

	//�����o�[�֐�
	bool LoadEnemyImage(void);			//�G�̉摜�̃��[�h����
	bool LoadShotImage(void);			//�e�̉摜�̃��[�h����
	bool LoadLifeBarImage(void);		//���C�t�o�[�摜�̃��[�h����
	bool LoadItemImage(void);			//�A�C�e���̉摜�̓ǂ݂���
	void AddCharOrder(int bottomPos, int index, CHAR_TYPE charType);	    //�G�̕��ѕς�����
	void Born(Vector2 targetPos, int Index);							//�G���������鏈��
	bool SaveData(void);				//�Z�[�u����
	bool LoadData(void);				//���[�h����
	 
public:                    //�����o�[�֐�
	int mCoin;			//������
	bool ScoreSet(void);   //�X�R�A�̃��Z�b�g����
	bool Init(int ScreenSizeX, int ScreenSizeY, SceneManager * parent);       //�C���X�^���X�̐�������
	bool UpDate(void);     //�C���X�^���X�̍X�V����
	void Draw(void);       //�C���X�^���X�̕`�揈��
	bool Release(void);    //�C���X�^���X�̊J������
	bool GameInit(void);   //�C���X�^���X�̏���������
	int mEnemyImage[ENEMY_TYPE_MAX][ENEMY_ANIM_COUNT * (int)DIR::DIR_MAX];   //�G�̉摜�̊i�[�̈�
	int mP_ShotImage[SHOT_IMAGE_COUNT];                            //�e(���@)�̉摜�̊i�[�̈�
	int mE_ShotImage[SHOT_IMAGE_COUNT];                            //�e(�G)�̉摜�̊i�[�̈�
	int mLifeBarImage[LIFE_ANIM_COUNT];                            //���C�t�o�[�̉摜�̊i�[�̈�
	int mItemImage[ITEM_IMAGE_COUNT];							   //���C�t�o�[�̉摜�̊i�[�̈�
	int mSeBuy;													   //�T�E���h�n���h��
	int mSeDoor;											       //�T�E���h�n���h��

	int GetEvent(Vector2 pos);									   //�v���C���[�̍��W�����Ԃ̃}�b�v�ɂ��邩��Ԃ�
	int GetScore(void);											   //�X�R�A��Ԃ�
	void BuyItem(ITEM_TYPE itemType);							   //�A�C�e�����w���������ǂ���
};