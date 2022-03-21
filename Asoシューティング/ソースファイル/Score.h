//#pragma once
#include "Vector2.h"

//�萔�̒�`
#define SCORE_POINT 100           //�G�̓��_
#define ITEM_POINT 300            //�A�C�e���̓��_
#define BOSS_POINT 500            //�{�X�̓��_
#define SCORE_MAX 9999            //�G�̓��_�̍ő�l

class Score  //�����o�[�ϐ�
{
private:
	int posx;                     //X���W
	int posy;                     //Y���W
	int score;                    //�X�R�A�̕\��
	int highscore;                //�n�C�X�R�A�̕\��
	int font;                     //�X�R�A�̃t�H���g��
	int fonthigh;                 //�n�C�X�R�A�̃t�H���g��
	bool alive;                   //true:�\�� false:��\��
	int fontCount;                //�t�H���g�̕\������

public:		//�����o�[�֐�
	bool Init(void);              //�C���X�^���X�̐���������
	void UpDate(void);            //�C���X�^���X�̍X�V����
	void PointDraw(int type);     //�C���X�^���X�̕`�揈��
	void ScoreDraw(void);         //���_�̕`�揈��
	void SetUp(Vector2 pos);      //�G�̂Ƃ���ɃX�R�A��\��
	bool GetAlive(void);          //�t�H���g���\������Ă��邩�ǂ�����Ԃ�
	void AddScore(int type);      //�X�R�A�����Z����
	int GetScore(void);           //�X�R�A��Ԃ�
	bool GameInit(void);          //�X�R�A�̏���������
};
