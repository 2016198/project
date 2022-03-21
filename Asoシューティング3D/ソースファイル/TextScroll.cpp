#include "TextScroll.h"

TextScroll::TextScroll(SceneManager* manager)
{
	mSceneManager = manager;
}

void TextScroll::Init(void)
{
	LoadDivGraph(
		"Image/Alphabet.png",
		NUM_IMAGE, NUM_X_IMAGE, NUM_Y_IMAGE,
		CHIP_SIZE, CHIP_SIZE, &mImages[0], true
	);

	mType = TYPE::TITLE;

	mFinded = false;

	std::vector<MsgInfo> infos;

	//1�s
	infos.push_back(MakeMsgInfo("Hello! SpaceWorld", infos.size()));

	//2�s
	infos.push_back(MakeMsgInfo("AsoSchool", infos.size()));

	//3�s
	infos.push_back(MakeMsgInfo("Byebye", infos.size()));

	int len = 0;

	for (auto& info : infos)
	{
		//�s���ƈʒu���ړ�������
		info.pos = { -400.0f,
			static_cast<float>(-CHIP_SIZE * (len + 1) - 150.0f),
			static_cast<float>(-CHIP_SIZE * len) - 100.0f };
		info.pos.z += mScroll;
		info.pos.y += mScroll;
		len++;
	}

	//����
	mTextMap.emplace(mType, infos);

	mScroll = 0.0f;
}

void TextScroll::Update(void)
{
	mScroll += 0.3f;
	//������
	auto infos = mTextMap[mType];
	int len = 0;

	for (auto& info : infos)
	{
		//�s���ƈʒu���ړ�������
		info.pos = { -400.0f,
			static_cast<float>(-CHIP_SIZE * (len + 1) - 150.0f),
			static_cast<float>(-CHIP_SIZE * len) - 100.0f};
		info.pos.z += mScroll;
		info.pos.y += mScroll;
		len++;
	}
	mTextMap[mType] = infos;
}

void TextScroll::Draw(void)
{
	auto infos = mTextMap[mType];

	//����
	for (auto& info : infos)
	{
		VECTOR pos = info.pos;
		//�s
		for (auto& msg : info.messages)
		{
			//1����
			DrawBillboard3D(
				pos, 0.5f, 0.5f, 20.0f, 0.0f,
				mImages[msg], true
			);
			pos.x += CHIP_SIZE;
		}
	}
}

void TextScroll::Release(void)
{
	for (const auto& img : mImages)
	{
		DeleteGraph(img);
	}
}

TextScroll::MsgInfo TextScroll::MakeMsgInfo(std::string msg, int mapCount)
{
	MsgInfo ret;

	//�������摜�z��̗v�f�ԍ��ɕϊ�
	std::vector<int> message;

	int ascii;
	int len = msg.size();
	for (int q = 0; q < len; q++)
	{
 		ascii = msg.at(q);

		for (int b = 65; b <= 90; b++)//�啶��
		{
			//ASCII�R�[�h��v�f�ԍ��ɕϊ�
			if (ascii == b && !mFinded)
			{
				ascii = b - 65;
				mFinded = true;
				break;
			}
		}

		for (int s = 97; s <= 122; s++)//������
		{
			//ASCII�R�[�h��v�f�ԍ��ɕϊ�
			if (ascii == s && !mFinded)
			{
				ascii = s - 71;
				mFinded = true;
				break;
			}
		}

		if (ascii == 32 && !mFinded)//�X�y�[�X
		{
			//ASCII�R�[�h��v�f�ԍ��ɕϊ�
			ascii = 52;
			mFinded = true;
		}

		if (ascii == 33 && !mFinded)//!�@���Ⴀ�܂��N��������Ă���邩�ȁH
		{
			//ASCII�R�[�h��v�f�ԍ��ɕϊ�
			ascii = 56;
			mFinded = true;
		}

		if (ascii == 34 && !mFinded)//��?(�Ј�)
		{
			//ASCII�R�[�h��v�f�ԍ��ɕϊ�
			ascii = 57;
			mFinded = true;
		}

		if (ascii == 46 && !mFinded)//�h�b�g
		{
			//ASCII�R�[�h��v�f�ԍ��ɕϊ�
			ascii = 53;
			mFinded = true;
		}


		if (ascii == 44 && !mFinded)//�J���}
		{
			//ASCII�R�[�h��v�f�ԍ��ɕϊ�
			ascii = 54;
		}

		//�ϊ������v�f�ԍ���ǉ�
		message.push_back(ascii);
		mFinded = false;
	}

	ret.pos = {0.0f, 0.0f, 0.0f};
	ret.messages = message;

	return ret;
}
