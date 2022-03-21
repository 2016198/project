#pragma once
#include "BaseScene.h"

class OptionScene :
    public BaseScene
{

public:
	OptionScene(INPUT_TYPE type, bool clear);	//�R���X�g���N�^
	~OptionScene() override;		//�f�X�g���N�^

	bool Init(void) override;					//����������
	SCENE_ID Update(double delta) override;		//�X�V����
	int Draw(void) override;					//�`�揈��
	void Release(void) override;				//�������
	const int GetNum(void) override;			//�l�킽��
	const SCENE_ID GetScene(void) override;		//�����̃V�[����n��

private:
	void ImgMove(void);							//�摜�̈ړ�����
	bool CheckMoveEnd(void);					//�摜�̈ړ��������I��������

	bool zoom_[2];								//�\���n�̑I�������ꂽ��
	int optionScreen_;							//�I�v�V�����̃X�N���[��
	int helpImage_;								//�O���t�B�b�N�n���h��
	const char* message_[2] = {					//�\�����镶��
		"�Q�[���p�b�h",
		"�L�[�{�[�h"};

	static constexpr int HALF_SCREEN_X = SCREEN_SIZE_X / 2;		//�X�N���[���T�C�YX�̔���
	static constexpr int HALF_SCREEN_Y = SCREEN_SIZE_Y / 2;		//�X�N���[���T�C�YY�̔���
	static constexpr int OFFSET = 100;							//���������炷�l
	double size[2];												//�X�N���[���̃T�C�Y
	double delta_;												//�f���^�^�C��
	int imageOpt_;												//�O���t�B�b�N�n���h��
	bool clear_;												//�`���[�g���A�����[�h���J��������

	bool isSelect_;												//���ڂ�I���������ǂ���
	Color3 lineColor_;											//�I�����Ă���g�̊O���̐F�R�[�h
	int selectOption_;											//�I�v�V�����̑I��
	int soundNum_;												//���ʒ���
	int sound_[2];												//�T�E���h
	void ZoomCommand(double delta);								//zoom����
	void UpdateOption(void);									//�I�v�V�����̍X�V
	void DrawOption(void);										//�I�v�V�����̕`��

	std::array<int, 3U> img_;									//�O���t�B�b�N�n���h��
	std::array<Vector2, 4U> offset_;							//�e�摜�̃I�t�Z�b�g
};

