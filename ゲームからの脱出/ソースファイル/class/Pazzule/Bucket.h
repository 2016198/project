#pragma once

constexpr int BUTTON_CNT = 6;	//�{�^���̐�
constexpr int WATER_SIZE = 30;	//���̖ڐ���T�C�Y
constexpr int KEY_SIZE = 7;		//�J�M�̃T�C�Y

class Bucket
{
public:
	struct Button
	{
		int x;				//x���W
		int y;				//y���W
		int size;			//�����鐅�̗�
		bool canPush;		//������H�����Ȃ��H
		unsigned int color;	//�{�^���̐F

	};
	bool Init(void);						
	void Update(void);						
	void Draw(void);						
	bool Release(void);						
	bool ReturnFlag(void);

	//��������ɖ߂�
	bool Back(void);
	bool backFlag;


private:
	struct Water
	{
		Button mouse;							//�}�E�X�̍��W
		Button button[BUTTON_CNT];				//�{�^���̍��W
		int Magnitude(int x, int y)const;		//�}�E�X�Ɖ~�̓����蔻��
		int water;								//���̗�
		int memory;								//���݂̃������̈ʒu
		bool add = true;						//�v���Xtrue:�}�C�i�Xfalse
		bool lock = false;						//���̈ړ����̓{�^���������Ȃ�
		unsigned int fontColor[11];				//�����̐F
		bool Check(int x, int y, int size);		//�}�E�X�̃`�F�b�N
		bool isGetKey = false;					//�J�M���Ƃ�邩
		int keyOffsetPos;						//�J�M������̍��W
		int timer;								//�t�H���g�̕\������
	};

	bool clearFlag_;
	Water water_;
	int font_;
	int count;
};

