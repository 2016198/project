#pragma once
#include <memory>
#include <list>

struct vector2
{
	int x, y;
};

class Lock
{
private:

	vector2 mouse = {};
	int cake;											//�O���t�B�b�N�n���h��
	const size_t pass_size = 6;							//�p�X���[�h�̒���
	const size_t pass_max_size = 20;					//���͂̍ő�l
	std::list<int> pass;								//�p�X���[�h
	int word[6] = {										//�͔͉�(�����̃p�X���[�h)
		4,7,1,3,5,6
	};

	bool CheckBox(int x, int y, int sizeX, int sizeY);	//�����蔻��l�p
	bool CheckCircle(vector2 sub, int size);			//�����蔻��~
	bool PassCheck(void);								//���̂܂��
	bool canOpen;										//�J������?
	bool open;											//�J���Ă�H
	bool check;											//�p�X���[�h�������Ă��邩�̃`�F�b�N
	int time;											//�����̕\������
	int error;											//�G���[�̕\������
	const vector2 pos = { 290, 155 };					//���������̍�����W
	const int size = 40;								//���������̘g
	unsigned int color[12];								//�F
	const char* num[12] = {								//��������
		"1", "2", "3",
		"4", "5", "6",
		"7", "8", "9",
		"C", "0", "E"
	};
	
public:

	bool Init();
	void UpDate();
	void Draw();
	bool Release();
};

vector2 operator+(vector2 a, vector2 b);
vector2 operator-(vector2 a, vector2 b);
vector2 operator*(vector2 a, vector2 b);
vector2 operator/(vector2 a, vector2 b);

