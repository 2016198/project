#pragma once
#include <array>
#include <vector>
#include <memory>
#include <type_traits>
#include <string>
#include "../Input/BaseInput.h"

enum class SCENE_ID		//�Q�[���V�[��
{
	CONTINUE,		//������
	RESULT,			//���U���g�V�[��
	TITLE,			//�^�C�g���V�[��
	TUTORIAL,		//�`���[�g���A���V�[��
	GAME_ONE,		//�Q�[���V�[���F��l
	GAME_TWO,		//�Q�[���V�[���F��l
	OPTION,			//�I�v�V�����V�[��
	END,			//�����܂�
	MAX
};

class BaseScene
{
public:
	BaseScene(INPUT_TYPE type);			//�R���X�g���N�^
	virtual ~BaseScene() {};			//�f�X�g���N�^

	virtual bool Init(void) = 0;					//����������
	virtual SCENE_ID Update(double delta) = 0;		//�X�V����
	virtual int Draw(void) = 0;						//�`�揈��
	virtual void Release(void) = 0;					//�������
	virtual const int GetNum(void) = 0;				//�l�킽��
	virtual const SCENE_ID GetScene(void) = 0;		//�O��̃V�[����n��

private:

protected:
	std::array<std::unique_ptr<BaseInput>, 2U> ptr_;	//�|�C���^
	std::array<InputList, 2U> input_;					//���͏��

	static constexpr int BOX_SIZE = 100;		//�{�b�N�X�̃T�C�Y
	static constexpr int OFFSET_POS_X = 170;	//�I�t�Z�b�g���W

	//�X�N���[���T�C�Y
	static constexpr int SCREEN_SIZE_X = 640;
	static constexpr int SCREEN_SIZE_Y = 480;

	INPUT_TYPE inputType_;					//���͏��

	int screen_ = 0;						//�X�N���[���n���h��
	SCENE_ID selectNum_;					//�ǂ��̃V�[���ֈړ����邩
	std::vector<unsigned int> color_;		//�F�R�[�h
	int select_ = 0;						//�V�[���ړ��̑I���J�[�\��

	int image_;								//�O���t�B�b�N�n���h��(�w�i)
	int font_;								//�t�H���g�n���h��
};

static SCENE_ID operator++(SCENE_ID& state)
{
	state = static_cast<SCENE_ID>(std::underlying_type<SCENE_ID>::type(state) + 1);
	return state;
};

static SCENE_ID operator--(SCENE_ID& state)
{
	state = static_cast<SCENE_ID>(std::underlying_type<SCENE_ID>::type(state) - 1);
	return state;
}

static bool operator<(const SCENE_ID stateA, const SCENE_ID stateB)
{
	int a = std::underlying_type<SCENE_ID>::type(stateA);
	int b = std::underlying_type<SCENE_ID>::type(stateB);

	return a < b;
}

static bool operator>(const SCENE_ID stateA, const SCENE_ID stateB)
{
	int a = std::underlying_type<SCENE_ID>::type(stateA);
	int b = std::underlying_type<SCENE_ID>::type(stateB);

	return a > b;
}

