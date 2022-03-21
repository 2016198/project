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

	//1行
	infos.push_back(MakeMsgInfo("Hello! SpaceWorld", infos.size()));

	//2行
	infos.push_back(MakeMsgInfo("AsoSchool", infos.size()));

	//3行
	infos.push_back(MakeMsgInfo("Byebye", infos.size()));

	int len = 0;

	for (auto& info : infos)
	{
		//行ごと位置を移動させる
		info.pos = { -400.0f,
			static_cast<float>(-CHIP_SIZE * (len + 1) - 150.0f),
			static_cast<float>(-CHIP_SIZE * len) - 100.0f };
		info.pos.z += mScroll;
		info.pos.y += mScroll;
		len++;
	}

	//文章
	mTextMap.emplace(mType, infos);

	mScroll = 0.0f;
}

void TextScroll::Update(void)
{
	mScroll += 0.3f;
	//文字列
	auto infos = mTextMap[mType];
	int len = 0;

	for (auto& info : infos)
	{
		//行ごと位置を移動させる
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

	//文章
	for (auto& info : infos)
	{
		VECTOR pos = info.pos;
		//行
		for (auto& msg : info.messages)
		{
			//1文字
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

	//文字を画像配列の要素番号に変換
	std::vector<int> message;

	int ascii;
	int len = msg.size();
	for (int q = 0; q < len; q++)
	{
 		ascii = msg.at(q);

		for (int b = 65; b <= 90; b++)//大文字
		{
			//ASCIIコードを要素番号に変換
			if (ascii == b && !mFinded)
			{
				ascii = b - 65;
				mFinded = true;
				break;
			}
		}

		for (int s = 97; s <= 122; s++)//小文字
		{
			//ASCIIコードを要素番号に変換
			if (ascii == s && !mFinded)
			{
				ascii = s - 71;
				mFinded = true;
				break;
			}
		}

		if (ascii == 32 && !mFinded)//スペース
		{
			//ASCIIコードを要素番号に変換
			ascii = 52;
			mFinded = true;
		}

		if (ascii == 33 && !mFinded)//!　じゃあまず年齢を教えてくれるかな？
		{
			//ASCIIコードを要素番号に変換
			ascii = 56;
			mFinded = true;
		}

		if (ascii == 34 && !mFinded)//は?(威圧)
		{
			//ASCIIコードを要素番号に変換
			ascii = 57;
			mFinded = true;
		}

		if (ascii == 46 && !mFinded)//ドット
		{
			//ASCIIコードを要素番号に変換
			ascii = 53;
			mFinded = true;
		}


		if (ascii == 44 && !mFinded)//カンマ
		{
			//ASCIIコードを要素番号に変換
			ascii = 54;
		}

		//変換した要素番号を追加
		message.push_back(ascii);
		mFinded = false;
	}

	ret.pos = {0.0f, 0.0f, 0.0f};
	ret.messages = message;

	return ret;
}
