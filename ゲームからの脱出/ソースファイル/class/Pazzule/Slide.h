#pragma once
class Slide
{
	class XY  //���W�ƃ}�X�l
	{
	public:
		int x;
		int y;
		int masu;
	};

	void Pattan(int num);				//�s�[�X�̃p�^�[��(�����g�p)
	void Move(int pase);				//�s�[�X�̈ړ�
	bool Check(int x, int y, int size);	//�J�[�\���̃`�F�b�N

	enum class GAMEMODE
	{
		PUZZLE,
		LIGHT
	};

	//�萔
	static const int P = 8;	//�s�[�X�̐�
	#define SIZE 50			//�s�[�X�̑傫��


public:
	bool Init(void);
	void Update(void);
	void Draw(void);
	bool ReturnFlag(void);

	//��������ɖ߂�
	bool Back(void);


private:

//�ϐ�
	XY p[P];			//�s�[�X�̍��W
	XY masu[P + 1];		//�}�X�̍��W
	int emptyMasu;		//��̃}�X
	int X, Y, cnt;		//�}�E�X�̍��W
	int gameCnt = 0;	//�Q�[���J�E���g
	XY Random[P + 1];	//����
	bool Chach[P + 1];	//�J�[�\�����G��Ă��邩
	int num_;			//����

	bool clearFlag_;
	bool backFlag;

	int font_;

};

