//#pragma once

//�萔��`
#define PAI 3.1415926535       //�~���� 
#define TITLE_SIZE_X 320       //�����̃T�C�YX
#define TITLE_SIZE_Y 80        //�����̃T�C�YY

class GameOverScene
{
private:
	int image;                    //�O���t�B�b�N�n���h��
	int PosX;                     //���WX
	int PosY;                     //���WY
	int counter;                  //�Q�[���I�[�o�[�J�E���^�[
	double en;                    //��]���x
public:
	bool Init(void);              //�C���X�^���X�̐���������
	void UpDate(void);            //�C���X�^���X�̍X�V����
	void Draw(void);              //�C���X�^���X�̕`�揈��
	bool Release(void);           //�C���X�^���X�̊J������
};
