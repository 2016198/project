//#pragma once

//�萔��`
#define HEART_SIZE_X 16       //�n�[�g�̉��T�C�Y
#define HEART_SIZE_Y 16       //�n�[�g�̏c�T�C�Y

class LifeP
{
private:
	int image;        //�O���t�B�b�N�n���h�� (�O:���@�A�P:�n�[�g)
	int posx;         //�n�[�g�̍��W
	int posy;         //�n�[�g�̍��W
	int Speed;        //����
	int count;        //�v���C���[�̎c�@

public:               //�����o�[�֐�
	bool Init(void);                  //�C���X�^���X�̐������̏���
	void Update(void);                //�C���X�^���X�̍X�V����
	void Draw(int lifeP);             //�C���X�^���X�̕`�揈�� 
	bool Release(void);               //�C���X�^���X�̊J������
	bool GameInit(void);              //�n�[�g�̏���������
};
