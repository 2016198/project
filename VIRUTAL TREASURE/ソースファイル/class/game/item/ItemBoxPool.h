#pragma once
#include <memory>
#include <list>
#include "ItemBox.h"

#define lpItemBoxPool ItemBoxPool::GetInstance()//�V���O���g�[��

class ItemBoxPool
{

public:
	static ItemBoxPool& GetInstance()	//�C���X�^���X�̓���
	{
		static ItemBoxPool s_Instance;
		return s_Instance;
	}

	std::list<ItemBox*> itemBoxList_;	//�g�����̗v�f
	std::list<ItemBox*> itemBoxPool_;	//�\���̗v�f

	void Init(void);					//����������
	void Generate(int pos, 
		ITEM type,
		unsigned int color);			//Pool����g�p�����������ė���
	void Get(Vector2 pos1, Vector2 pos2, bool full1, bool full2);	//�`�揈��
	void Get(Vector2 pos, bool full);								//�`�揈��
	void Draw(double delta);										//�`�揈��
	void Release(void);												//�������

private:
	
	static const int pool_count_ = 20;					//���������ɂ̐�

	std::string item_name[static_cast<int>(ITEM::MAX)]	//�\�����镶��
	{
		"���ʎ��΂���ɓ��ꂽ�I",
		"�����T�m�@����ɓ��ꂽ�I",
		"���΂���ɓ��ꂽ�I",
		"�낤��������ɓ��ꂽ�I",
		"�A�C�e���������ς��Ȃ̂ł�����߂��c"
	};

	int sound_;											//�T�E���h�n���h��
};

