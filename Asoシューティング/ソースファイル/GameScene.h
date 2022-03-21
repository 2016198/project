//#pragma once
#include "Player2.h"
#include "Enemy2.h"
#include "Boss.h"
#include "Shot2.h"
#include "Eshot.h"
#include "Bg2.h"
#include "Blast2.h"
#include "Item2.h"
#include "LifeP.h"
#include "Score.h"
#include "main.h"

//�萔�̐�`
#define SHOT_MAX 20     //�e�̍ő�l
#define BLAST_MAX 6     //�����̍ő�l
#define SHOT_TIME 2     //�e�̃X�e�C�^�C��
#define FONT_MAX 50     //�X�R�A�\���̍ő�l

class GameScene
{
private:
	int gamecounter;              //�Q�[�����n�܂��Ă���̎���
	int push;                     //�X�y�[�X�L�[�������Ă���̎���
	int point;                    //���_
	bool getItem;                 //�A�C�e������ɓ��ꂽ�Ƃ�
	int itemCount;                //�A�C�e���̌��ʌp������
	int fontType;                 //���_�̎��
	Vector2 shotAdd[SHOT_MAX];    //�G�̍��W �| �v���C���[�̍��W
	Vector2 shotAdd2[SHOT_MAX];   //�G�̍��W �| �v���C���[�̍��W(��Βl)
	Vector2 playerInit;           //�v���C���[�̏�����
	Vector2 pPos;                 //�v���C���[�̍��W
	Vector2 ePos;                 //�G�̍��W	
	Vector2 bPos;                 //boss�̍��W
	Vector2 iPos;                 //�A�C�e���̍��W
	Vector2 sPos[SHOT_MAX][3];    //���@�̒e�̍��W
	Vector2 SPos[SHOT_MAX];       //�G�̒e�̍��W
	Player2 player2;
	Enemy2 enemy2;
	Boss boss;
	Item2 item2;
	Shot2 shot2[SHOT_MAX][3];
	Blast2 blast2[BLAST_MAX];
	Bg2 bg2;
	LifeP lifeP;
	Score score[FONT_MAX];
	Eshot eshot[SHOT_MAX];

public:
	bool Init(void);              //�C���X�^���X�̐���������
	void UpDate(void);            //�C���X�^���X�̍X�V����
	void Draw(void);              //�C���X�^���X�̕`�揈��
	bool Release(void);           //�C���X�^���X�̊J������
	bool GameInit(void);          //�Q�[���̏���������
	int Score(void);              //�Q�[���̃X�R�A��������ĕԂ��B
	bool GameClear(void);         //�Q�[���N���A�[����
	bool GameOver(void);          //�Q�[���I�[�o�[�V�[���Ɉڂ鏈��
};
