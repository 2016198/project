//#pragma once
#include "Vector2.h"

//�萔��`
#define PLAYER_SIZE_X 32      //���@�̉��T�C�Y
#define PLAYER_SIZE_Y 32      //���@�̏c�T�C�Y
#define PLAYER_LIFE 3         //���@�̎c�@��

class Player2
{
private:              //�����o�[�ϐ�
	//int pos_x;		  //X���W
	//int pos_y;		  //Y���W
	int Image;        //�O���t�B�b�N�n���h�� (�O:���@�A�P:�n�[�g)
	int Speed;        //����
	bool Alive;       //�����Ă�؋�����
	bool shotFlag;    //�v���C���[�����𔭎˂����true�ɂȂ�ϐ�
	int life;         //�v���C���[�̎c�@
	Vector2 pos;      //�v���C���[���W

public:               //�����o�[�֐�
	bool Init(Vector2 Init);          //�C���X�^���X�̐������̏���
	void Update(void);                //�C���X�^���X�̍X�V����
	void Draw(void);                  //�C���X�^���X�̕`�揈�� 
	void Drawen(void);                //�~�̕`�揈��
	bool Release(void);               //�C���X�^���X�̊J������
	bool IsShot(void);                //�e�𔭎˂��Ă����true��Ԃ�
	Vector2 GetPos(void);             //�v���C���[�̍��W��Ԃ�
	void DeletePlayer(void);          //�v���C���[������
	bool GetAlive(void);              //�v���C���[�������Ă�؋�����
	bool Death(void);                 //�v���C���[�̎c�@��0�ɂȂ����Ƃ�
	int GetLife(void);                //�v���C���[�̃��C�t��Ԃ�
	bool GameInit(Vector2 Init);      //�v���C���[�̏���������
};
