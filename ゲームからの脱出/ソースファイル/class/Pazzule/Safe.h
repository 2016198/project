#pragma once
#include <DxLib.h>
#include <memory>
#include <list>
#include "../Vector2.h"


class Safe
{
private:
	int image = LoadGraph("yaju.png");
	Vector2 mouse = {};
	const size_t pass_size = 6;			//�p�X���[�h�̒���
	const size_t pass_max_size = 20;	//���͂̌��E�l
	std::list<int> pass;				//�p�X���[�h
	int word[6] = {						//�����̃p�X���[�h
		1,9,2,4,9,4
	};

	bool CheckBox(int x, int y, int sizeX, int sizeY);	//�����蔻��l�p
	bool CheckCircle(Vector2 sub, int size);			//�����蔻��~
	bool PassCheck(void);								//�J�����ǂ����̔���
	bool canOpen;										//�J������H
	bool open;											//�J����
	bool check;											//�p�X���[�h�������Ă��邩�̃`�F�b�N
	int time;											//�����̕\������
	int error;											//�G���[�̕\������
	const Vector2 pos = { 290,155 };					//�����̍�����W
	const int size = 40;								//�����̘g
	unsigned int color[12];								//�F�̊i�[
	const char* num[12] = {								//���ɂɕ`�悷�镶��
		"1", "2", "3",
		"4", "5", "6",
		"7", "8", "9",
		"C", "0", "E"
	};

	bool clearFlag_;
	bool backFlag;
	int count;
	int font_;

public:
	bool Init(void);
	void Update();
	void Draw();
	bool Release();
	bool ReturnFlag(void);

	//��������ɖ߂�
	bool Back(void);

};

Vector2 operator+(Vector2 a, Vector2 b);
Vector2 operator-(Vector2 a, Vector2 b);
Vector2 operator*(Vector2 a, Vector2 b);
Vector2 operator/(Vector2 a, Vector2 b);
