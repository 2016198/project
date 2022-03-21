#pragma once
#include <string>
#include <vector>
#include <map>
#include <DxLib.h>

class SceneManager;

class TextScroll
{

public:

	static constexpr int NUM_X_IMAGE = 10;
	static constexpr int NUM_Y_IMAGE = 6;
	static constexpr int NUM_IMAGE = NUM_X_IMAGE * NUM_Y_IMAGE;

	static constexpr int CHIP_SIZE = 32;

	enum class TYPE
	{
		TITLE,
		ENDLE
	};

	struct MsgInfo
	{
		VECTOR pos;
		std::vector<int> messages;	//�v�f�ԍ�
	};

	TextScroll(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	SceneManager* mSceneManager;

	//�摜
	int mImages[NUM_IMAGE];

	//�Đ�����e�L�X�g�X�N���[��
	TYPE mType;

	//�����𔭌������烍�b�N����
	bool mFinded;

	//�e�L�X�g�Ǘ�
	std::map<TYPE, std::vector<MsgInfo>> mTextMap;

	//�e�L�X�g�̃X�N���[������
	float mScroll;

	//string�̕�����̂��摜�z��̗v�f�ԍ��̕ϊ�
	TextScroll::MsgInfo MakeMsgInfo(std::string msg, int mapCount);
};

