//#pragma once

//�萔��`
#define PAI 3.1415926535       //�~����
#define TITLE_SIZE_X 320       //�����̃T�C�YX
#define TITLE_SIZE_Y 80        //�����̃T�C�YY

class TitleScene
{
private:
	int tImage;                   //�O���t�B�b�N�n���h���i�^�C�g���j
	int RImage;                   //�O���t�B�b�N�n���h���i���v���j
	int LImage;                   //�O���t�B�b�N�n���h���i�����v���j
	double en;                    //��]�̑��x
	int plus;                     //�Q�[���J�E���^�[(+)
	int	minus;                    //�Q�[���J�E���^�[(-)

public:
	bool Init(void);              //�C���X�^���X�̐���������
	void UpDate(void);            //�C���X�^���X�̍X�V����
	void Draw(void);              //�C���X�^���X�̕`�揈��
	bool Release(void);           //�C���X�^���X�̊J������
	bool GameInit(void);          //�Q�[���I�[�o�[��̏���������
};
