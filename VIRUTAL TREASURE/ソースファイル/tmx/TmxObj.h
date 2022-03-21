#pragma once
#include <string>
#include <vector>
#include <map>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#define lpTextMng TmxObj::GetInstance()

using TextMap = std::map<std::string, std::vector<std::vector<std::string>>>;

class TmxObj
{
public:

	static TmxObj& GetInstance()
	{
		static TmxObj s_Instance;
		return s_Instance;
	}

	bool LoadTMX(std::string fileName, std::string type);	//TMXのロード
	const TextMap& GetData();

private:
	TmxObj();				//コンストラクタ
	~TmxObj();				//デストラクタ

	bool CheckTiledVersion(rapidxml::xml_node<>* node);		//バージョンチェック

	std::map<std::string, int> virsion_;					//バージョン変数

	TextMap text_;	//テキスト格納変数
};