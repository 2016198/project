#include <sstream>
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"
#include "TmxObj.h"

TmxObj::TmxObj()
{
	virsion_["1.6.0"] = 1;
	//virsion_.emplace();
}

TmxObj::~TmxObj()
{

}

bool TmxObj::LoadTMX(std::string fileName, std::string type)
{
	// TMX�̃��[�h
	rapidxml::xml_document<> tmxDoc;								//tmx�m�[�h�̊i�[
	rapidxml::file<> xmlFlieName = fileName.c_str();				//�t�@�C���̓ǂݍ���
	tmxDoc.parse<0>(xmlFlieName.data());							//�t�@�C���f�[�^�̊i�[
	rapidxml::xml_node<>* textNode = tmxDoc.first_node("text");		//�擪�m�[�h�̎擾

	//�o�[�W��������v���Ă��邩
	if (!CheckTiledVersion(textNode))
	{
		return false;
	}

	auto textSet = textNode->first_node("type");
	auto textType = textSet->first_attribute("id");

	while (textType->value() != type)
	{
		textSet = textSet->next_sibling();
		if (textSet == nullptr)
		{
			return false;
		}
		textType = textSet->first_attribute("id");
	}

	auto sizeP = atoi(textSet->first_attribute("size")->value());
	auto id = textType->value();
	text_[id].resize(sizeP);

	auto msgData = textSet->first_node("msg");

	for (auto& dataP : text_[id])
	{
		auto sizeC = atoi(msgData->first_attribute("size")->value());
		dataP.resize(sizeC);
		std::stringstream dataStream;
		auto textData = msgData->first_node("data")->first_node();
		dataStream << textData->value();
		std::string numStr;
		std::string sumStr;
		getline(dataStream, numStr, '\n');

		for (auto& dataC : dataP)
		{
			sumStr = "";
			getline(dataStream, numStr, '\n');
			std::stringstream dataSumStream;
			dataSumStream << numStr;
			while (getline(dataSumStream, numStr, ','))
			{
				sumStr += numStr;
				sumStr += "\n";
			}
			dataC = sumStr;
		}
		msgData = msgData->next_sibling();
	}

	TRACE("%s\n", id);
	for (const auto& dataP : text_[id])
	{
		for (const auto& dataC : dataP)
		{
			TRACE("%s\n", dataC.c_str());
		}
		TRACE("---------------\n");
	}

	return true;
}

const TextMap& TmxObj::GetData()
{
	return text_;
}

bool TmxObj::CheckTiledVersion(rapidxml::xml_node<>* node)
{
	if (node == nullptr)//null�ɂȂ��Ă��Ȃ���
	{
		TRACE("���s���܂����@node�̒l��null�ł�\n");
		return false;
	}
	auto textVersion = node->first_attribute("textversion");
	//�o�[�W��������v���Ă��邩

	if (!virsion_.count(textVersion->value()) == 1)
	{
		TRACE("��Ή��o�[�W�����ł��B\n");
		return false;
	}

	if (!virsion_[textVersion->value()] == 1)
	{
		TRACE("��Ή��o�[�W�����ł��B\n");
		return false;
	}

	TRACE("�Ή��o�[�W�����ł��B\n");
	return true;
}
