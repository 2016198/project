#include <sstream>
#include <string>
#include "TmxObj.h"
#include "../class/common/ImageMng.h"
#include"../_debug/_DebugConOut.h"
#include"../_debug/_DebugDispOut.h"

TmxObj::TmxObj()
{
	virsion_["1.6.0"] = 1;
	//virsion_.emplace();
}

TmxObj::~TmxObj()
{

}

bool TmxObj::LoadTSX(std::string flieName)
{
	rapidxml::file<> xmlFileName = flieName.c_str();				//�t�@�C���̓ǂݍ���
	tsxDoc_.parse<0>(xmlFileName.data());							//�t�@�C���f�[�^�̊i�[
	rapidxml::xml_node<>* tileset = tsxDoc_.first_node("tileset");	//�擪�m�[�h�̎擾
	//auto tileset = tsxDoc_.first_node("tileset");

	//auto data = tiledversion->value();

	//�o�[�W��������v���Ă��邩
	if (!CheckTiledVersion(tileset))
	{
		return false;
	}

	//auto node = tsxDoc_.first_node();
	/*while (node)
	{
		if (node->name_size())
		{
			TRACE("%s >>", node->name());
		}
		auto atr = node->first_attribute();
		while (atr)
		{
			if (atr->name_size())
			{
				TRACE("%s:", atr->name());
			}
			TRACE("%s ", atr->value());
			atr = atr->next_attribute();
		}
		TRACE("\n");
		node = node->next_sibling();
	}*/
	/*if (node)
	{
		if (node->name_size())
		{
			TRACE("%s >>", node->name());
		}
		auto atr = node->first_node();
		if (atr)
		{
			if (atr->name_size())
			{
				TRACE("%s >>", node->name());
			}
			auto son = atr->first_attribute();
			if (son->name_size())
			{
				TRACE("%s = ", son->name());
				TRACE("%s \n", son->value());
			}
		}	
	}*/
	auto imageNode = tileset->first_node("image");
	std::string name = imageNode->first_attribute("source")->value();		//�t�@�C����
	std::string source = "tmx/" + name;										//�p�X�̏���Ԃ�
	std::string keyName = tileset->first_attribute("name")->value();		//�p�X�̏���Ԃ�
	auto tilewidth = atoi(tileset->first_attribute("tilewidth")->value());	//�`�b�v�̃T�C�Y��
	auto tileheight = atoi(tileset->first_attribute("tileheight")->value());//�`�b�v�̃T�C�Y�c
	auto divCntX = atoi(tileset->first_attribute("columns")->value());		//�`�b�v�̐���
	auto divCntY = atoi(tileset->first_attribute("tilecount")->value());	//�`�b�v�̐��c
	divCntY /= divCntX;
	lpImageMng.GetID(source, keyName, Vector2{ tilewidth,tileheight }, Vector2{ divCntX,divCntY });

	return true;
}

bool TmxObj::LoadTMX(std::string fileName)
{
	rapidxml::file<> xmlFlieName = fileName.c_str();			//�t�@�C���̓ǂݍ���
	tmxDoc_.parse<0>(xmlFlieName.data());						//�t�@�C���f�[�^�̊i�[
	rapidxml::xml_node<>* mapNode = tmxDoc_.first_node("map");	//�擪�m�[�h�̎擾

	//�o�[�W��������v���Ă��邩
	if (!CheckTiledVersion(mapNode))
	{
		return false;
	}

	auto tiledversion = mapNode->first_attribute("tiledversion");

	auto tileset = mapNode->first_node("tileset");
	auto source = tileset->first_attribute("source");

	std::string pass = fileName.substr(0, fileName.find_last_of("/") + 1);
	std::string tsxName = pass + source->value();//path = "./txm/"
	if (!LoadTSX(tsxName.c_str()))
	{
		return false;
	}

	//�K�v�ȏ�����
	firstGID_ = atoi(tileset->first_attribute("firstgid")->value());
	layerSize_ = atoi(mapNode->last_attribute("nextlayerid")->value()) - 1;
	worldArea_ = {
		atoi(mapNode->last_attribute("width")->value()),
		atoi(mapNode->last_attribute("height")->value()) };
	tileSize_ = {
		atoi(mapNode->last_attribute("tilewidth")->value()),
		atoi(mapNode->last_attribute("tilewidth")->value()) };

	//width="64" height="64" tilewidth="16" tileheight="16"
	if (!SetColList()) { return false; }
	return SetMap();
}

bool TmxObj::SetMap(void)
{
	rapidxml::xml_node<>* mapNode = tmxDoc_.first_node("map");//�擪�m�[�h�̎擾
	if (!CheckTiledVersion(mapNode)) { return false; }//�o�[�W��������v���Ă��邩

	/*for(auto layerNode = mapNode->first_node("layer");
		layerNode != nullptr;
		layerNode = layerNode->next_sibling())*/
	for (auto layerNode = mapNode->first_node("layer");
		layerNode != nullptr;
		layerNode = layerNode->next_sibling("layer"))
	{
		/*if (layerNode == nullptr)
		{
			TRACE("map�m�[�h�擾�ł���\n");
			return false;
		}*/
		if (static_cast<std::string>(layerNode->first_attribute("name")->value()) == "col") //col��������J�b�g���悤�I
		{ continue; }
		auto layer = mapData_.try_emplace(layerNode->first_attribute("name")->value());
		if (layer.second)
		{
			layer.first->second.resize(worldArea_.x_ * worldArea_.y_);
		}

		auto layerData = layerNode->first_node("data")->first_node();

		std::stringstream dataStream;
		dataStream << layerData->value();

		for (auto& data : layer.first->second)
		{
			std::string numStr;
			getline(dataStream, numStr, ',');
			data = atoi(numStr.c_str());
		}
		/*TRACE("%s\n",layer.first->first.c_str());
		for (const auto& data : layer.first->second)
		{
			TRACE("%d,", data);
		}
		TRACE("\n");*/
	}
	return true;

	//while (layerNode)
	//{
	//	if (layerNode == nullptr)
	//	{
	//		TRACE("map�m�[�h --> ���C���[�擾�ł���\n");
	//		return false;
	//	}
	//	auto layer = mapData_.try_emplace(layerNode->first_attribute("name")->value());
	//	if (layer.second)
	//	{
	//		layer.first->second.resize(worldArea_.x_ * worldArea_.y_);
	//	}
	//	auto layerData = layerNode->first_node("data")->first_node();
	//	std::string path = layerData->value();

	//	//TRACE("%s\n", layerData->value());
	//	for (int t = 0; t < worldArea_.x_ * worldArea_.y_; t++)
	//	{
	//		std::string num = path.substr(0, path.find_first_of(","));
	//		path = path.substr(path.find_first_of(",") + 1);
	//		//TRACE("%s\n", num.c_str());
	//		mapData_[layerNode->first_attribute("name")->value()][t] = { atoi(num.c_str()) };
	//	}
	//	auto a = layerNode->first_attribute("name")->value();
	//	TRACE("%s\n", a);
	//	for (auto num : mapData_[layerNode->first_attribute("name")->value()])
	//	{
	//		TRACE("%d,",num);
	//	}
	//	TRACE("\n");
	//	layerNode = layerNode->next_sibling("layer");
	//}
	//return true;
}

bool TmxObj::SetColList(void)
{
	rapidxml::xml_node<>* mapNode = tmxDoc_.first_node("map");//�擪�m�[�h�̎擾
	if (!CheckTiledVersion(mapNode)) { return false; }//�o�[�W��������v���Ă��邩

	auto colNode = mapNode->last_node("objectgroup");

	if (colNode == nullptr) { return false; }//null�`�F�b�N

	if (static_cast<std::string>(colNode->first_attribute("name")->value()) != "col") {//col�Ȃ́H
		return false;
	}

	for (auto objectNode = colNode->first_node("object");
		objectNode != nullptr;
		objectNode = objectNode->next_sibling())
	{
		/*int id = atoi(objectNode->first_attribute("id")->value());
		Vector2 pos = {
			atoi(objectNode->first_attribute("x")->value()),
			atoi(objectNode->first_attribute("y")->value())
		};
		Vector2 size = {
			atoi(objectNode->first_attribute("width")->value()),
			atoi(objectNode->first_attribute("height")->value())
		};*/
		colList_.push_back({ {
			atoi(objectNode->first_attribute("x")->value()),
			atoi(objectNode->first_attribute("y")->value())},
			{
			atoi(objectNode->first_attribute("width")->value()),
			atoi(objectNode->first_attribute("height")->value())}});
	}
	return true;
}

const Vector2& TmxObj::GetWorldArea(void)
{
	return worldArea_;
}

const Vector2& TmxObj::GetTileSize(void)
{
	return tileSize_;
}

const unsigned int TmxObj::GetLayerSize(void)
{
	return layerSize_;
}

const unsigned int TmxObj::GetFirstGID(void)
{
	return firstGID_;
}

const MapData& TmxObj::GetMapData(void)
{
	return mapData_;
}

ColList& TmxObj::GetColList(void)
{
	return colList_;
}

const int TmxObj::GetMapData(std::string layer, Vector2 pos)//pos���W
{
	auto chipPos = pos / tileSize_;
	return GetMapData(layer, chipPos.x_, chipPos.y_);
}

const int TmxObj::GetMapData(std::string layer, int x, int y)//xy�}�X��
{
	/*try 
	{
		mapData_.at(layer);
		int point = x * y * worldArea_.x_;
		if (point >= 0 && point < mapData_.at(layer).size())
		{
			return mapData_[layer][point];
		}
		else
		{
			return -1;
		}
	}
	catch (...)
	{
		return;
	}*/
	if (mapData_.count(layer))
	{
		return 0;//�ǂ�Ȑ����ł�OK
	}
	int point = x + y * worldArea_.x_;
	if (point < 0 || point >= mapData_[layer].size())
	{
		return 0;//�ǂ�Ȑ����ł�OK
	}
	return mapData_[layer][point];
}

bool TmxObj::CheckTiledVersion(rapidxml::xml_node<>* node)
{
	if (node == nullptr)//null�ɂȂ��Ă��Ȃ���
	{
		TRACE("���s���܂����@node�̒l��null�ł�\n");
		return false;
	}
	auto tiledversion = node->first_attribute("tiledversion");
	//�o�[�W��������v���Ă��邩
	if (!virsion_.count(tiledversion->value()) == 1)
	{
		TRACE("��Ή��o�[�W�����ł��B\n");
		return false;
	}
	if (!virsion_[tiledversion->value()] == 1)
	{
		TRACE("��Ή��o�[�W�����ł��B\n");
		return false;
	}
	TRACE("�Ή��o�[�W�����ł��B\n");
	return true;
}
