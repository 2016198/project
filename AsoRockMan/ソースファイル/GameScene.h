//#pragma once
//#include "Stage.h"
//#include "Player.h"
#include "Vector2.h"
#include "gamecommon.h"
class Player;
class Stage;
class Shot;
class Lift;

//�萔��`

class GameScene 
{
private:                    //�����o�[�ϐ�
	int mCounter;           //�Q�[���J�E���^�[

	Stage *mStage;			//"�X�e�[�W"�̃C���X�^���X�����p
	Player *mPlayer[static_cast<int>(PLAYER_TYPE::MAX)];		//"�v���C���["�̃C���X�^���X�����p
	Shot *mShot;			//"�V���b�g"�̃C���X�^���X����
	Lift *mLift;			//"���t�g"�̃C���X�^���X����

	 
public:                    //�����o�[�֐�
	bool Init(void);       //�C���X�^���X�̐�������
	bool UpDate(void);     //�C���X�^���X�̍X�V����
	void Draw(void);       //�C���X�^���X�̕`�揈��
	bool Release(void);    //�C���X�^���X�̊J������
	bool GameInit(void);   //�C���X�^���X�̏���������

	int GetEvent(Vector2 pos);//�}�b�v�̃C�x���g����Ԃ�
	bool GetLiftAlive(void);//���t�g�̏���Ԃ��B
	Vector2 GetLiftPos(void);//���t�g�̏���Ԃ��B
};