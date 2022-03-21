#pragma once
#include <memory>
#include <vector>
#include "../Vector2.h"
#include "../manager/MaterialManager.h"
#include "BaseScene.h"
#include "../game/Player.h"
#include "../game/item/Item.h"
#include "../game/Map.h"

class GameTwoScene:
	public BaseScene
{			
public:
	GameTwoScene(INPUT_TYPE type);		//�R���X�g���N�^
	~GameTwoScene() override;			//�f�X�g���N�^

	bool Init(void) override;					//����������
	SCENE_ID Update(double delta) override;		//�X�V����
	int Draw(void) override;					//�`�揈��
	void Release(void) override;				//�������
	const int GetNum(void) override;			//�l�킽��
	const SCENE_ID GetScene(void) override;		//�����̃V�[����n��
		
private:
	std::vector<std::unique_ptr<Player>> playerPtr_;	//�v���C���[�̃C���X�^���X	
	std::vector<std::unique_ptr<Item>> itemPtr_;		//�A�C�e���̃C���X�^���X
	std::unique_ptr<Map> mapPtr_;						//�}�b�v�̃C���X�^���X

	int screenP_;										//�v���C���[�̃X�N���[��
	int winPlayer_;										//�������v���C���[
	bool rock[2];										//����������A���ł��Ȃ��悤�Ƀ��b�N����
	double delta_;										//�f���^�^�C��

};

