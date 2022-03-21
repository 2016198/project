#pragma once
#include "../item/Item.h"
#include "../../Vector2.h"

class ItemBox
{

public:

	static constexpr size_t ANIM_COUNT = 6U;					//�摜�̃A�j���[�V�����̐�

	void Generate(int point, ITEM type, unsigned int color);	//��������
	void Draw(double delta);									//�`�揈��

	ItemBox(std::vector<int> image);	//�R���X�g���N�^
	~ItemBox();							//�f�X�g���N�^

	int IsGetItem(Vector2 pos1, Vector2 pos2);	//�v���C���[�ƃA�C�e�����Ԃ�������(�����Ȃ��Ă��邩)�F�_�u��
	int IsGetItem(Vector2 pos);					//�v���C���[�ƃA�C�e�����Ԃ�������(�����Ȃ��Ă��邩)�F�V���O��
	void Distroy(double delta);					//�j������
	Vector2 GetDrawPos(void);					//���W�̏��
	ITEM GetItemInfo(void);						//����A�C�e���̏��

private:

	bool alive_ = false;		//���݂̏��
	unsigned int color_;		//�F�R�[�h
	double delta_;				//�f���^�^�C��
	Vector2 pos_;				//�`����W
	ITEM type_;					//�A�C�e���̎��
	std::vector<int> image_;	//�O���t�B�b�N�n���h��
	int fream_;					//�摜�̃A�j���[�V�����ϐ�
};

