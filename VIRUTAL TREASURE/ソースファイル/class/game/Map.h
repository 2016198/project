#pragma once
#include <string>
#include <vector>
#include "../Vector2.h"

//�}�b�v�̏��
static constexpr int MAP_COUNT = 6;								//���̐�
static constexpr int MAP_SIZE = MAP_COUNT * MAP_COUNT;			//�}�X�̃T�C�Y
static constexpr int OFFSET_X = 150;							//����X
static constexpr int OFFSET_Y = 70;								//����Y
static constexpr int OFFSET_SIZE = 75;							//�Ԋu
static constexpr int POINT_COUNT = 5;							//�n�}�̈��̐�
static constexpr int POINT_SIZE = POINT_COUNT * POINT_COUNT;	//�n�}�̐�

class Map
{	
public:
	//��l���[�h
	bool Init(int point1, int point2);	//����������
	void Draw(int point1, int point2);	//�`�揈��

	//�\�����[�h
	bool Init(int point);				//����������
	void Draw(int point);				//�`�揈��

	void Release(void);					//�������

	void SetMap(int map, int num);		//�}�b�v�̍X�V

	Map();								//�R���X�g���N�^
	~Map();								//�f�X�g���N�^

private:
	std::vector<int> map_;				//�ړI�n
	int image_[POINT_SIZE];				//�O���t�B�b�N�n���h��
	unsigned int color_;				//�F�R�[�h
	std::string fileNameG_[POINT_SIZE];	//�t�@�C���̖��O
	Vector2 drawPos_;					//�`����W
};

