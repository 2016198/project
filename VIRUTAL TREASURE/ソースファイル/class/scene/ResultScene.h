#pragma once
#include "BaseScene.h"
class ResultScene : 
	public BaseScene
{

public:
	ResultScene(INPUT_TYPE type, const int num, const SCENE_ID beforeScene);	//�R���X�g���N�^
	~ResultScene() override;													//�f�X�g���N�^

	bool Init(void) override;					//����������
	SCENE_ID Update(double delta) override;		//�X�V����
	int Draw(void) override;					//�`�揈��
	void Release(void) override;				//�������
	const int GetNum(void) override;			//�l�킽��
	const SCENE_ID GetScene(void) override;		//�����̃V�[����n��

private:
	int winPlayer_;								//���������v���C���[�̔ԍ�
	SCENE_ID beforeScene_;						//�O�̃Q�[���V�[��
	const char* str_[2] =						//�\������t�H���g�N
	{ 
		"������x���" ,
		"TitleScene"
	};
	int offsetFont_;							//�t�H���g�̃I�t�Z�b�g
};

