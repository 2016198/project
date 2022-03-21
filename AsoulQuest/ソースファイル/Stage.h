//#pragma once
#include "Vector2.h"
#include "GameCommon.h"

//�萔��`
#define CHIP_IMAGE_MAX 81  //�܂��Ղ̃`�b�v�̐�

//�}�b�v�Ǘ��p
enum class MAP_ID
{
	NORMAL,
	MAZE
};

class Stage
{
private:                    //�����o�[�ϐ�
	int mScreenSizeX;              //��ʂ�X�T�C�Y
	int mScreenSizeY;              //��ʂ�Y�T�C�Y
	int mChipImage[CHIP_IMAGE_MAX];         //�O���t�B�b�N�n���h��

	//�}�b�v�Ǘ��p
	MAP_ID mMapID;							//���݂̃}�b�v�̏��
	int mMapX;								//���݂̃}�b�v�̃T�C�YX
	int mMapY;								//���݂̃}�b�v�̃T�C�YY
	int mMap[MAP_X][MAP_Y];					//���݂̃}�b�v�f�[�^

public:                     //�����o�[�֐�
	bool Init(int ScreenSizeX, int ScreenSizeY);        //�C���X�^���X�̏���������
	void UpDate(void);      //�C���X�^���X�̍X�V����
	void Draw(Vector2 Pos);               //�C���X�^���X�̕`�揈��
	bool Release(void);            //�C���X�^���X�̊J������

	void SetMap(MAP_ID mapID);		//�w�肳�ꂽ�}�b�v�����}�b�v�z��Ɋi�[����
	int GetMapChip(Vector2 pos);    //������}�b�v�̔ԍ���Ԃ�
};
