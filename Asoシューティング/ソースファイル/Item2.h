//#pragma once
#include "Vector2.h"

//�萔��`
#define ITEM_SIZE_X 32         //�A�C�e���̃T�C�YX
#define ITEM_SIZE_Y 32         //�A�C�e���̃T�C�YY
#define PAI 3.1415926535       //�~����

//�����o�[�ϐ�
class Item2
{
private:
	int image;    //�O���t�B�b�N�n���h��
	int speed;    //�A�C�e���̗����X�s�[�h
	bool alive;   //�A�C�e�����o�����Ă��邩�ǂ���
	int game;     //�Q�[���J�E���^�[
	double en;    //��]���x
	Vector2 pos;  //���W����(����̍��W)


public:  //�����o�[�֐�
	bool Init(void);              //�C���X�^���X�������̏���
	void UpDate(void);            //�C���X�^���X�X�V����
	void Draw(void);              //�C���X�^���X�̕`�揈��
	bool Release(void);           //�C���X�^���X�̊J������
	void SetItem(Vector2 ePos);   //�G�̍��W���A�C�e���ɃZ�b�g����	
	bool GetAlive(void);          //�A�C�e���̍��̏��(true:�o���Afalse:��o��)
	Vector2 GetPos(void);         //�A�C�e���̍��W��������
	void DeleteItem(void);        //�A�C�e��������
	bool GameInit(void);          //�A�C�e���̏���������
};
