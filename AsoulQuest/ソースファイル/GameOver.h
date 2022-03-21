//#pragma once

//�萔��`
#define GAME_OVER_SIZE_X 457
#define GAME_OVER_SIZE_Y 81

class GameOver
{
private:                   //�����o�[�ϐ�
	int mScreenSizeX;              //��ʂ�X�T�C�Y
	int mScreenSizeY;              //��ʂ�Y�T�C�Y
	int mImage;            //�O���t�B�b�N�n���h��
	int mPlayer[3];        //�O���t�B�b�N�n���h��
	int mCounter;          //�Q�[���I�[�o�[�J�E���^�[
	int mScore;			   //�X�R�A
	bool mInput;		   //�X�R�A��������ꂽ���ǂ���
	int mSe;			   //���ʉ��n���h��

public:                    //�����o�[�֐�
	bool Init(int ScreenSizeX, int ScreenSizeY);       //�C���X�^���X�̐�������
	bool UpDate(void);     //�C���X�^���X�̍X�V����
	void Draw(int score);       //�C���X�^���X�̕`�揈��
	bool Release(void);    //�C���X�^���X�̊J������
	bool GameInit(void);   //�C���X�^���X�̏���������
};
