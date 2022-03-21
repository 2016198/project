//#pragma once

//�萔��`
#define TITLE_SIZE_X 600
#define TITLE_SIZE_Y 250

class TitleScene   //�N���X��
{
private:				 //�����o�[�ϐ�
	int mScreenSizeX;    //��ʂ�X�T�C�Y
	int mScreenSizeY;    //��ʂ�Y�T�C�Y
	int mImage;			 //�^�C�g���C���[�W
	int mStartImage;     //�O���t�B�b�N�n���h��
	int mCounter;        //�^�C�g���J�E���^�[

public:
	bool Init(void);       //�C���X�^���X�̐�������
	bool UpDate(void);     //�C���X�^���X�̍X�V����
	void Draw(void);       //�C���X�^���X�̕`�揈��
	bool Release(void);    //�C���X�^���X�̊J������
	bool GameInit(void);   //�C���X�^���X�̏���������
};