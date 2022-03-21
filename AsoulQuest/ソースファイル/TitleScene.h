#pragma once

//�萔��`
#define TITLE_SIZE_X 600
#define TITLE_SIZE_Y 250

//�e�̃C���X�^���X����
class SceneManager;

class TitleScene   //�N���X��
{
private:				 //�����o�[�ϐ�
	SceneManager* mParent;
	int mScreenSizeX;    //��ʂ�X�T�C�Y
	int mScreenSizeY;    //��ʂ�Y�T�C�Y
	int mImage;			 //�^�C�g���C���[�W
	int mCounter;        //�^�C�g���J�E���^�[
	bool mReset;         //���Z�b�g�������ǂ���

public:
	bool Init(int ScreenSizeX, int ScreenSizeY, SceneManager* parent);       //�C���X�^���X�̐�������
	bool UpDate(void);     //�C���X�^���X�̍X�V����
	void Draw(void);       //�C���X�^���X�̕`�揈��
	bool Release(void);    //�C���X�^���X�̊J������
	bool GameInit(void);   //�C���X�^���X�̏���������
};
