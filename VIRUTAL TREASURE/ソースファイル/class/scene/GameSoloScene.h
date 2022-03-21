#pragma once
#include <memory>
#include "../Vector2.h"
#include <list>
#include "../manager/MaterialManager.h"
#include "BaseScene.h"
#include "../game/Player.h"
#include "../game/item/Item.h"
#include "../game/Map.h"
#include "../game/Fire.h"

class GameSoloScene :
	public BaseScene
{
public:
	GameSoloScene(INPUT_TYPE type);		//�R���X�g���N�^
	~GameSoloScene() override;			//�f�X�g���N�^

	bool Init(void) override;					//����������
	SCENE_ID Update(double delta) override;		//�X�V����
	int Draw(void) override;					//�`�揈��
	void Release(void) override;				//�������
	const int GetNum(void) override;			//�l�킽��
	const SCENE_ID GetScene(void) override;		//�����̃V�[����n��

private:
	std::unique_ptr<Player> playerPtr_;				//�v���C���[�̃C���X�^���X	
	std::unique_ptr<Item> itemPtr_;					//�A�C�e���̃C���X�^���X
	std::unique_ptr<Map> mapPtr_;					//�}�b�v�̃C���X�^���X
	std::list<std::unique_ptr<Fire>> firePtrPool_;	//�\���̉��̃C���X�^���X
	std::list<std::unique_ptr<Fire>> firePtrList_;	//�g�p���鉊�̃C���X�^���X

	int screenP_;									//�v���C���[�̃X�N���[��
	bool rock;										//����������A���ł��Ȃ��悤�Ƀ��b�N����
	double delta_;									//�f���^�^�C��
	int makeFire_;									//�t�@�C�A�̐����m��
};

