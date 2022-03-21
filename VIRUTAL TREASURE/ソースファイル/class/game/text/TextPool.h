#pragma once
#include <memory>
#include <list>
#include "TextData.h"

#define lpTextPool TextPool::GetInstance()//�V���O���g�[��

class TextPool
{
public:
	static TextPool& GetInstance()	//�C���X�^���X�̓���
	{
		static TextPool s_Instance;
		return s_Instance;
	}

	std::list<TextData*> textList_;		//�g�����̗v�f
	std::list<TextData*> textPool_;		//�\���̗v�f

	void Init(void);					//����������
	void Generate(std::string str,
		Vector2 pos,
		double lifeTime,
		unsigned int color);			//Pool����g�p�����������ė���
	void Draw(double delta);			//�`�揈��
	void Release(void);					//�������

	int font_ = -1;						//�t�H���g�n���h��

private:

	static const int pool_count_ = 20;	//���������ɂ̐�
};
