//#pragma once
#include "Vector2.h"
#include "gamecommon.h"

//�萔��`
#define CHIP_IMAGE_MAX 13  //�}�b�v�̃`�b�v�̐�

//�}�b�v�Ǘ��p
enum class MAP_ID
{
	NORMAL,
	FIRE
};

class Stage
{
private:							//�����o�[�ϐ�
	Vector2 mOffset;				//�}�b�v�̃I�t�Z�b�g���W
	int mChipImage[CHIP_IMAGE_MAX];         //�O���t�B�b�N�n���h��
	MAP_ID mMapID;							//�}�b�v�̏��
	Vector2 mMapSize;						//�}�b�v�̃T�C�Y
	int mMap[MAP_Y][MAP_X];					//�}�b�v�̊i�[���

public:
	Stage(void);				//�R���X�g���X�^
	bool Init(void);			//�C���X�^���X�̐���
	Vector2 UpDate(void);		//�C���X�^���X�̍X�V
	void Draw(void);			//�C���X�^���X�̕`��
	bool Release(void);			//�C���X�^���X�̊J��
	~Stage(void);				//�f�X�R���X�g���X�^

	void SetMap(MAP_ID mapID);	//�}�b�v�̐���
	int GetMapChip(Vector2 pos);//�}�b�v�̏���Ԃ�
};
