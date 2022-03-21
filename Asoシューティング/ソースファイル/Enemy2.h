//#pragma once
#include "Vector2.h"

//�萔��`
#define ENEMY_SIZE_X 32       //�G�̉��T�C�Y
#define ENEMY_SIZE_Y 32       //�G�̏c�T�C�Y

class Enemy2
{
private:							   //�����o�[�ϐ�	
	int Image;                         //�O���t�B�b�N�n���h��
	//int PosX;                          //X���W
	//int PosY;                          //Y���W
	int Speed;                         //�ړ���
	int gamecounter;                   //�Q�[���J�E���^�[
	bool Alive;                        //(�G��true�̎�)�����Ă�؋�����
	bool shotFlag;                     //�e�����������ǂ���
	Vector2 Pos;                       //���W

public:
	bool Init(void);                         //�C���X�^���X�̐������̏���
	void UpDate(bool bossMode,bool bossHunt);//�C���X�^���X�̍X�V����
	void Draw(void);                         //�C���X�^���X�̕`�揈��
	bool Release(void);                      //�C���X�^���X�̊J������
	Vector2 GetPos(void);                    //�e�̍��W��^���܂�
	bool IsShot(void);                       //�G�����������ǂ���
	void DeleteEnemy(void);                  //�G������
	bool GetAlive(void);                     //�G�������Ă�؋�����
	bool GameInit(void);                     //�G�̏���������
};