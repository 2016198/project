//#pragma once

//�萔��`
#define BG_SIZE_X 640          //�w�i�̃T�C�YX
#define BG_SIZE_Y 960          //�w�i�̃T�C�YY

class Bg2  //�����o�[�ϐ�
{
private:
	int Image;               //�O���t�B�b�N�n���h��
	int PosY1;               //�w�i�P��Y���W
	int PosY2;               //�w�i�Q��Y���W
	int Speed;               //�w�i�̈ړ����x

public:		//�����o�[�֐�
	bool Init(void);              //�C���X�^���X�̐���������
	void UpDate(void);            //�C���X�^���X�̍X�V����
	void Draw(void);              //�C���X�^���X�̕`�揈��
	bool Release(void);           //�C���X�^���X�̊J������
	bool GameInit(void);          //�w�i�̏���������
};
