#include <sstream>
#include <DxLib.h>
#include "ListMng.h"
#include "../../tmx/rapidxml_utils.hpp"
#include "../../tmx/rapidxml.hpp"
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"
#include "../common/ImageMng.h"

ListMng::ListMng()
{
	
}

ListMng::~ListMng()
{

}

bool ListMng::LoadAnime(std::string flieName, std::string objID)
{
	for (auto objName : checkObj_)
	{
		if (objID == objName) { return true; }
	}
	rapidxml::xml_document<> actDoc;
	rapidxml::file<> file = flieName.c_str();
	actDoc.parse<0>(file.data());
	rapidxml::xml_node<>* actionList = actDoc.first_node("list");

	if (actionList == nullptr) { return false; }

	auto version = actionList->first_attribute("version");
	std::string verStr = version->value();
	if (verStr != "1.5")
	{
		TRACE("アニメーション定義のバージョン非対応");
		return false;
	}
	rapidxml::xml_node<>* actionObj = actionList->first_node("object");
	if (actionObj == nullptr) { return false; }
	std::string objType = actionObj->first_attribute("name")->value();
	while (objType != objID)
	{
		actionObj = actionObj->next_sibling();
		if (actionObj == nullptr) { return false; }
		objType = actionObj->first_attribute("name")->value();//colsizeX
	}
	//if (action == nullptr) { return false; }
	if (colSize_.count(objID) == 0)
	{
		colSize_[objID].x_ = atoi(actionObj->last_attribute("colsizeX")->value());
		colSize_[objID].y_ = atoi(actionObj->last_attribute("colsizeY")->value());
	}

	for (auto action = actionObj->first_node("action"); action; action = action->next_sibling())
	{
		std::string name = action->first_attribute("name")->value();
		lpImageMng.GetID(
			action->first_attribute("source")->value(),
			objID + name,
			Vector2{ atoi(action->first_attribute("sizeX")->value()),
					 atoi(action->first_attribute("sizeY")->value()) },
			Vector2{ atoi(action->first_attribute("cntX")->value()),
					 atoi(action->first_attribute("cntY")->value()) });

		exRate_[objID + name] = atof(action->last_attribute("exrate")->value());

		std::string key = objID + name;
		animTbl_.try_emplace(key);
		auto anime = action->first_node("anime");
		animTbl_[key].first = atoi(anime->first_attribute("loop")->value());
		auto animeData = anime->first_node();

		if (animeData == nullptr) { return false; }

		std::stringstream dataStream;
		dataStream << animeData->value();
		std::string numStr;
		//TRACE("%s\n", key.c_str());
		while (getline(dataStream, numStr, ','))
		{
			auto id = atoi(numStr.c_str());
			getline(dataStream, numStr, ',');
			auto frame = atoi(numStr.c_str());
			animTbl_[key].second.emplace_back(AnimData{ id,frame });
			//TRACE("%d,%d\n", id, frame);
		}
	}
	checkObj_.emplace_back(objID);
	return true;
}


void ListMng::SetAnime(std::string objID, std::string state, AnimeData* animeData)
{
	*animeData = { 
		objID,
		state,
		animTbl_[objID + state].second.begin(),
		0,
		0,
		exRate_[objID + state]};
}

const Vector2& ListMng::GetColSize(std::string objID)
{
	return colSize_[objID];
}

void ListMng::UpDateAnime(std::string objID, std::string state, AnimeData* animeData)
{
	if (animeData->animCnt_++ >= (*animeData->animItr_)[InvLimit])
	{
		animeData->animCnt_ = 0;
		++animeData->animItr_;
		//イテレータは前演算の方が処理が速い
		//animItr_++;
		if (animTbl_[objID + state].second.end() == animeData->animItr_)
		{
			if (++animeData->animPlayCnt_ < animTbl_[objID + state].first || animTbl_[objID + state].first == -1)
			{
				//ループ時
				animeData->animItr_ = animTbl_[objID + state].second.begin();
			}
			else
			{
				//再生終了の時最こマ？をセット
				animeData->animItr_ = --(animTbl_[objID + state].second.end());
			}
		}
	}
}
