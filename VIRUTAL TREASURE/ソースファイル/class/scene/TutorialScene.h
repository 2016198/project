#pragma once
#include <memory>
#include <vector>
#include "../Vector2.h"
#include "../manager/MaterialManager.h"
#include "BaseScene.h"
#include "../game/Player.h"
#include "../game/item/Item.h"
#include "../tutorial/Text.h"
#include "../game/Map.h"

class TutorialScene :
    public BaseScene
{
public:
	TutorialScene(INPUT_TYPE type);		//�R���X�g���N�^
	~TutorialScene() override;			//�f�X�g���N�^

	bool Init(void) override;					//����������
	SCENE_ID Update(double delta) override;		//�X�V����
	int Draw(void) override;					//�`�揈��
	void Release(void) override;				//�������
	const int GetNum(void) override;			//�l�킽��
	const SCENE_ID GetScene(void) override;		//�����̃V�[����n��

private:

	std::unique_ptr<Text> textPtr_;						//�\������e�L�X�g�̃C���X�^���X
	std::vector<std::unique_ptr<Player>> playerPtr_;	//�v���C���[�̃C���X�^���X	
	std::vector<std::unique_ptr<Item>> itemPtr_;		//�A�C�e���̃C���X�^���X
	std::unique_ptr<Map> mapPtr_;						//�}�b�v�̃C���X�^���X

	int screenP_;										//�v���C���[�̃X�N���[��
	int screenM_;										//�}�j���A����ʂ̃X�N���[��
	bool rock[2];										//����������A���ł��Ȃ��悤�Ƀ��b�N����
	double delta_[2];									//�f���^�^�C���A0:���̃f���^�l�A1:�f���^�l�̍��v

	static constexpr double TIP_TIME = 2000.0;			//�q���g���o������

	int bright_;										//��ʂ̖��邳
	void ChackTextMode(TEXT_MODE textMode);				//�e�L�X�g���[�h�̊Ǘ��֐�

	//�t�F�C�h�֌W
	void FadeCommand(void);								//�t�F�C�h����
	bool fadeIn_;										//�t�F�C�h�C��
	bool fadeOut_;										//�t�F�C�A�E�g

	int progressNum_;									//���݂̐i��
	double tipsTime_;									//�q���g�̕\��
	bool CheckProgress(int num);						//�i���`�F�b�N
	void ProgressUpdate(void);							//���ꂼ��i���̍X�V
	void ProgressDraw(void);							//���ꂼ��i���̕`��
	void TipDraw(void);									//�q���g�`��
	double alpha_;										//�F�̃��l

	bool player_[2];									//�v���C���[�̈ړ��I���m�F
};

