#pragma once
#include <memory>
#include "../Vector2.h"
#include "BaseScene.h"

#define lpSceneMng SceneManager::GetInstance()	//�V���O���g�[��

class SceneManager
{
public:
	static SceneManager& GetInstance()			//�C���X�^���X�̓���
	{
		static SceneManager s_Instance;
		return s_Instance;
	}

	bool Init(void);		//����������
	void Run(void);			//���s����
	void Release(void);		//�������

private:

	static constexpr double deltaTime = 500.0;		//�t�F�C�h�̒���
	double delta_ = deltaTime;						//�t�F�C�h�p�̕ϐ�
	static constexpr int fadeSpeed_ = 3;			//�t�F�C�h�̑���
	bool fadeIn_ = false;							//�t�F�[�h�C��
	bool fadeOut_ = false;							//�t�F�[�h�A�E�g
	bool gameEnd_ = false;							//�Q�[�������܂�

	std::unique_ptr<BaseScene> uniqueScene_;	//�V�[���̃��j�[�N�|�C���^

	SCENE_ID nextScene_;						//���̃V�[��
	int image_;									//�O���t�B�b�N�n���h��
	double angle_;								//�摜�̊p�x
	double num_;								//��]�p�ϐ�
	bool clear_;								//�`���[�g���A�����[�h���N���A�������ǂ���

	void FadeCommand(SCENE_ID nextScene, double chor);	//fade�̎��s

	//�X�N���[���T�C�Y
	static constexpr int SCREEN_SIZE_X = 640;
	static constexpr int SCREEN_SIZE_Y = 480;

	//�X�N���[��ID
	int screen_;

	//�V�[���؂�ւ��̌��ʉ�
	int sound_;									//���ʉ��n���h��

	//�G�t�F�N�g�n
	Vector2 mousePos_[2];						//�}�E�X�̍��W
	int effect_[2];								//�G�t�F�N�g�n���h���F�P=�m�[�}���G�Q=�Đ���
	double animCnt;								//�A�j���[�V�������Z�b�g�ϐ�

	//�����ȊO�̃V�|���ɒl��n���ϐ�
	int sceneNum_;								//���̃V�[���ɓn���l
	SCENE_ID sceneID_;							//���̃V�[����ID
	INPUT_TYPE inputType_;						//���͂̎��

	//�t�H���g�n���h��
	std::string fontFile_[5] = {			//�t�H���g�̃t�@�C���p�X
		"font/font1.dft",
		"font/font2.dft",
		"font/font3.dft",
		"font/font4.dft",
		"font/font5.dft"
	};
};

