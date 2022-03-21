#pragma once
#include <type_traits>
#include <array>
#include <map>

//��`�̐錾
enum class INPUT_LIST			//���͊Ǘ����
{
	//�V�X�e���֘A�̃L�[���
	START,
	SELECT,

	//�}�E�X
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,

	//���͏��
	UP,
	DOWN,
	LEFT,
	RIGHT,
	A,
	B,

	MAX
};

enum class KEY
{
	//�L�[�̏��
	NOW,				//���̃t���[��
	OLD,				//1�t���[���O
	TRG_DOWN,			//�������u��
	TRG_UP				//�������u��
};

enum class INPUT_TYPE	//���͏��̃^�C�v
{
	KEY,
	PAD
};

using InputList = std::map<INPUT_LIST, std::map<KEY, bool>>;

class BaseInput
{
public:
	BaseInput() {};										//�R���X�g���N�^
	virtual ~BaseInput() {};							//�f�X�g���N�^	
	virtual void SetKeyList(INPUT_TYPE type) = 0;		//�L�[�̏�Ԃ�ύX

	void CheckInputList(void);							//�L�[�̏�Ԃ��`�F�b�N
	void CheckTrgList(void);							//�L�[�̏�Ԃ��`�F�b�N

	const InputList& GetCntData(void)					//�L�[�̏���^����
	{
		return input_;
	}

private:

protected:
	InputList input_ = {};
};

static INPUT_LIST begin(INPUT_LIST) { return INPUT_LIST::START; };
static INPUT_LIST end(INPUT_LIST) { return INPUT_LIST::MAX; };
static INPUT_LIST operator++(INPUT_LIST& state)
{
	state = static_cast<INPUT_LIST>(std::underlying_type<INPUT_LIST>::type(state) + 1);
	return state;
};
static INPUT_LIST operator*(const INPUT_LIST& state) { return state; };

