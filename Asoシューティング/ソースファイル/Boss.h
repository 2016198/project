//#pragma once
#include "Vector2.h"

//�萔�̒�`
#define BOSS_SIZE_X 64
#define BOSS_SIZE_Y 64

class Boss
{
private:							   //�����o�[�ϐ�
	int life;                          //boss�̎c�@
	int bossLR;                        //�����E��
	int ySpeed;                        //�ړ���Y
	int Image[3];                      //�O���t�B�b�N�n���h��
	int xSpeed;                        //�ړ���X
	int gamecounter;                   //�Q�[���J�E���^�[
	bool Alive;                        //(�G��true�̎�)�����Ă�؋�����
	bool hunt;                         //boss���|���ꂽ���ǂ���
	int huntTime;                      //�|����Ă���̎���
	int stayTime;                      //�҂�����
	bool shotFlag;                     //�e�����������ǂ���
	Vector2 Pos;                       //���W

public:								     //�����o�[�֐�
	bool Init(void);                     //�C���X�^���X�̐������̏���
	void UpDate(void);                   //�C���X�^���X�̍X�V����
	void Draw(void);                     //�C���X�^���X�̕`�揈��
	bool Release(void);                  //�C���X�^���X�̊J������
	void InBoss(void);                   //Boss�̓o��
	int IsStay(void);                    //boss�����G���ǂ���
	bool IsHit(void);                    //Boss�ɓ�����������
	void DeleteBoss(void);               //boss������
	bool GetAlive(void);                 //boss�������Ă�؋�����
	bool IsHunt(void);                   //boss���|���ꂽ��
	bool Death(void);                    //�Q�[���N���A����
	Vector2 GetPos(void);                //boss�̍��W��Ԃ�
	bool GameInit(void);                 //boss�̏���������
};
