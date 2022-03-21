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
	// TMXのロード
	rapidxml::xml_document<> tmxDoc;								//tmxノードの格納
	rapidxml::file<> xmlFlieName = fileName.c_str();				//ファイルの読み込み
	tmxDoc.parse<0>(xmlFlieName.data());							//ファイルデータの格納
	rapidxml::xml_node<>* textNode = tmxDoc.first_node("text");		//先頭ノードの取得

	//バージョンが一致しているか
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
	if (node == nullptr)//nullになっていないか
	{
		TRACE("失敗しました　nodeの値はnullです\n");
		return false;
	}
	auto textVersion = node->first_attribute("textversion");
	//バージョンが一致しているか

	if (!virsion_.count(textVersion->value()) == 1)
	{
		TRACE("非対応バージョンです。\n");
		return false;
	}

	if (!virsion_[textVersion->value()] == 1)
	{
		TRACE("非対応バージョンです。\n");
		return false;
	}

	TRACE("対応バージョンです。\n");
	return true;
}
