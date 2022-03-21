//#pragma once
constexpr int BUTTON_CNT = 6;	//�{�^���̐�
constexpr int WATER_SIZE = 30;	//���̖ڐ���T�C�Y
constexpr int KEY_SIZE = 7;	//�J�M�̃T�C�Y

struct Button
{
	int x;				//x���W
	int y;				//y���W
	int size;			//�����鐅�̗�
	bool canPush;		//������H�����Ȃ��H
	unsigned int color;	//�{�^���̐F
};

class Water
{
private:
	Button mouse;							//�}�E�X�̍��W
	Button button[BUTTON_CNT];				//�{�^���̍��W
	int Magnitude(int x, int y)const;		//�}�E�X�Ɖ~�̓����蔻��
	int water = 0;							//���̗�
	int memory = 0;							//���݂̃������̈ʒu
	bool add = true;						//�v���Xtrue:�}�C�i�Xfalse
	bool lock = false;						//���̈ړ����̓{�^���������Ȃ�
	unsigned int fontColor[11];				//�����̐F
	bool Check(int x, int y, int size);		//�}�E�X�̃`�F�b�N
	bool isGetKey = false;					//�J�M���Ƃ�邩
	int keyOffsetPos = 0;					//�J�M������̍��W
	int timer;								//�t�H���g�̕\������

public:
	bool Init(void);						//����������
	bool UpDate(void);						//�X�V����
	void Draw(void);						//�`�揈��
	bool Release(void);						//�������
};

