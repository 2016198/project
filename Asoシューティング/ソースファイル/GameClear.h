//#pragma once
#define TITLE_CLEAR_SIZE_X 320    //�Q�[���N���A�̃T�C�YX
#define TITLE_CLEAR_SIZE_Y 80     //�Q�[���N���A�̃T�C�YY
#define TETE_SIZE_X 16            //����̃T�C�YX
#define TETE_SIZE_Y 16            //����̃T�C�YY

class GameClear
{
private:
	int image;                    //�O���t�B�b�N�n���h���i�^�C�g���j
	int te[2];                    //�O���t�B�b�N�n���h���i����j
	int se;                       //���ʉ��n���h��
	int score;                    //�X�R�A
	int counter;                  //�Q�[���J�E���^�[
	int x;                        //x���W
	int y;                        //y���W
public:
	bool Init(void);              //�C���X�^���X�̐���������
	void UpDate(void);            //�C���X�^���X�̍X�V����
	void Draw(int score);         //�C���X�^���X�̕`�揈��
	bool Release(void);           //�C���X�^���X�̊J������
	void Reset(void);              //�J�E���^�[���Z�b�g����
};
