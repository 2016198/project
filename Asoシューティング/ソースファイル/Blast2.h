//#pragma once
#include "Vector2.h"

//�萔��`
#define BLAST_SIZE_X 96       //�����̃T�C�YX
#define BLAST_SIZE_Y 96       //�����̃T�C�YY
#define BLAST_COUNT_X 6       //�A�j���̐�X
#define BLAST_COUNT_Y 4       //�A�j���̐�Y

class Blast2
{
private:
	int Image[BLAST_COUNT_X * BLAST_COUNT_Y];       //�O���t�B�b�N�n���h��
	int PosX;                                       //X���W
	int PosY;                                       //Y���W
	bool Alive;                                     //(�G��true�̎�)�����Ă�؋�����
	int No;                                         //�u���X�g�̂̃A�j���[�V����
	Vector2 Pos;                                    //���W����

public:
	bool Init(void);                 //�C���X�^���X�������̏���
	void UpDate(void);               //�C���X�^���X�̍X�V����
	void Setup(Vector2 Pos);         //�C���X�^���X�𗘗p��������
	void Draw(void);                 //�C���X�^���X�̕`�揈��
	bool Release(void);              //�C���X�^���X�̊J������
	bool GetAlive(void);             //�����̃A�j���[�V�����\��
	bool GameInit(void);             //�����̏���������
};