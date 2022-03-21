//#pragma once
#include "Vector2.h"

//�萔��`
#define P_SHOT_SIZE_X 32        //�e�̉��T�C�Y
#define P_SHOT_SIZE_Y 32        //�e�̏c�T�C�Y

class Shot2 
{
private:
	int Image;        //�O���t�B�b�N�n���h��
	int Speed;        //����
	bool Alive;       //�����Ă�؋�����
	Vector2 pos;      //���W����
public:			      //�����o�[�֐�
	bool Init(void);              //�C���X�^���X�������̏���
	void Setup(Vector2 pPos);     //�C���X�^���X�𗘗p���鏈��
	void UpDate(int i);           //�C���X�^���X�̍X�V����
	void Draw(void);              //�C���X�^���X�̕`�揈��
	bool Release(void);           //�C���X�^���X�̊J������
	Vector2 GetPos(void);         //���W��^����
	bool GetAlive(void);          //�e�������Ă邩
	void DeleteShot(void);        //�e��ł�
	bool GameInit(void);          //�e�̏���������
};
