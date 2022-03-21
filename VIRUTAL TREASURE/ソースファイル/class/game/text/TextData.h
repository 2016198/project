#pragma once
#include <string>
#include "../../Vector2.h"

class TextData
{
public:

	void Generate(std::string text, Vector2 pos, double life, unsigned int color);			//�������Ďg�p����
	void Draw(double delta, int fontID);													//�`�揈��

	TextData();			//�R���X�g���N�^
	~TextData();		//�f�X�g���N�^

	bool IsAlive();		//�\������Ă�H

private:

	std::string text_;			//�e�L�X�g�f�[�^
	double life_ = -1.0;		//�e�L�X�g�\������
	Vector2 pos_;				//���W
	unsigned int color_;		//�F�R�[�h
};

