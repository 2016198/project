#pragma once

#include <string>
#include <map>
#include <vector>
#include <list>
#include "../class/common/Vector2.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "../class/common/Collision.h"

using MapData = std::map<std::string, std::vector<int>>;

class TmxObj
{
public:
	TmxObj();
	~TmxObj();
	bool LoadTSX(std::string fileName);
	bool LoadTMX(std::string fileName);
	bool SetMap(void);
	bool SetColList(void);
	const Vector2& GetWorldArea(void);
	const Vector2& GetTileSize(void);
	const unsigned int GetLayerSize(void);
	const unsigned int GetFirstGID(void);

	const MapData& GetMapData(void);
	ColList& GetColList(void);
	const int GetMapData(std::string layer, Vector2 pos);//posÇÕç¿ïW
	const int GetMapData(std::string layer, int x, int y);//x,yÉ}ÉXñ⁄êî

private:
	bool CheckTiledVersion(rapidxml::xml_node<>* node);

	std::map<std::string, int> virsion_;

	// TMX
	rapidxml::xml_document<> tmxDoc_;
	unsigned int firstGID_;
	unsigned int layerSize_;
	Vector2 worldArea_;
	Vector2 tileSize_;

	MapData mapData_;
	ColList colList_;
	// TSX
	rapidxml::xml_document<> tsxDoc_;
};