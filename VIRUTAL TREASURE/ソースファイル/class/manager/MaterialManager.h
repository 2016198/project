#pragma once
#include <string>
#include <map>
#include <vector>
#include "../Vector2.h"

using VecInt = std::vector<int>;		//グラフィックハンドル				

#define lpMaterialMng MaterialManager::GetInstance()//シングルトーン

class MaterialManager
{
private:
	std::map<std::string, VecInt> map_;	//読み込み用変数
	
public:
	static MaterialManager& GetInstance()	//インスタンスの入手
	{
		static MaterialManager s_Instance;
		return s_Instance;
	}

	//スクリーンのロードをする
	const int& LoadScreenic(std::string key, int sizeX, int sizeY);
	

	//画像のロードをする：すでに読み込んでいたら、その値を返す
	const int& LoadGraphHandle(std::string key);

	//音のロードをする：すでに読み込んでいたら、その値を返す
	const int& LoadSoundHandle(std::string key);

	//フォントデータをロードする：すでに読み込んでいたら、その値を返す
	const int& LoadFontHandle(std::string key);

	//画像のロードをする：すでに読み込んでいたら、その値を返す
	const VecInt& LoadDivGraphic(std::string key, Vector2 count);

	void DeleteGraphHandle(std::string key);		//画像の開放
	void DeleteSoundHandle(std::string key);		//サウンドの開放
	void DeleteFontHandle(std::string key);			//フォントデータの開放
};

