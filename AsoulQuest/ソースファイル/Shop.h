#pragma once
#include "Vector2.h"
class GameScene;

//�萔��`
#define SERIHU_COUNT 7

//�A�C�e���̎��
enum class ITEM_TYPE
{
	SHIELD,
	HEART,
	WAY
};

class Shop
{
private:					//�����o�[�ϐ�
	int mImage;				//�O���t�B�b�N�n���h��
	int mArrowImage;		//�O���t�B�b�N�n���h��
	GameScene* mParent;		//�e�̃C���X�^���X�ϐ�
	int mCnt;				//�Q�[���J�E���g
	int mPosX;				//�Z���t�̖ډB�����W
	bool mBack;				//shop���o�����ǂ���
	bool mPush;				//�����{�^������������
	bool mBuy;				//���i�𔃂������ǂ���
	bool mNoBuy;			//����������Ȃ��Ƃ�
	const char* mSerihu[SERIHU_COUNT] =
	{ 
		"��������Ⴂ�܂��`",
		"���������� �Ȃ��ł�",
		"3way�V���b�g10��(30�񕪂܂ł��Ă�)",
		"��ꂽ�炱��ŉ񕜂����`",
		"���Ȃ������������U��������܂�",
		"�����A�����Ⴄ�́H",
		"�܂��ǂ���`"
	};	//�X��̃Z���t

public:                     //�����o�[�֐�
	bool Init(GameScene* parent, int ScreenSizeX, int ScreenSizeY);        //�C���X�^���X�̏���������
	int mScreenSizeX;       //��ʂ�X�T�C�Y
	int mScreenSizeY;       //��ʂ�Y�T�C�Y
	bool UpDate(void);      //�C���X�^���X�̍X�V����
	void Draw(void);	    //�C���X�^���X�̕`�揈��
	bool Release(void);     //�C���X�^���X�̊J������
	bool GameInit(GameScene* parent);	//�Q�[���̏�����
	int mShopImage;			//�O���t�B�b�N�n���h��
};
