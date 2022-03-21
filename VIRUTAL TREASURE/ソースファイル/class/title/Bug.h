#pragma once
#include "../Vector2.h"

class Bug
{
public:

	Bug(int image);		//�R���X�g���N�^
	~Bug() {};			//�f�X�g���N�^

	void Generate(Vector2 pos, double angle, double life);
	void Update(double delta);		//�X�V����
	void Draw(void);				//�`�揈��

	bool IsAlive(void);				//�������Ă��邩�ǂ���

private:

	int image_;			//�O���t�B�b�N�n���h��
	double life_;		//�\������
	Vector2 pos_;		//���W
	double angle_;		//�p�x
};
