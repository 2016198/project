#pragma once
#include<list>
#include<map>
#include<array>
#include "../common/Vector2.h"

#define lpListMng ListMng::GetInstance()

using AnimData = std::array<int, 2U>;
using AnimNode = std::pair<int, std::list<AnimData>>;
using AnimItr = std::list<std::array<int, 2U>>::iterator;

constexpr int GraphHD = 0;
constexpr int InvLimit = 1;

struct AnimeData{

	std::string objID_;
	std::string state_;
	AnimItr animItr_;
	int animCnt_;//1フレーム何回再生するか
	int animPlayCnt_;//何回アニメを再生するか
	double exRate;
};

class ListMng
{
public:
	static ListMng& GetInstance()
	{
		static ListMng s_Instance;
		return s_Instance;
	}
	bool LoadAnime(std::string flieName, std::string objID);
	void SetAnime(std::string objID, std::string state, AnimeData* animeData);
	const Vector2& GetColSize(std::string objID);
	void UpDateAnime(std::string objID, std::string state, AnimeData* animeData);


private:
	ListMng();
	~ListMng();
	std::map<std::string, Vector2> colSize_;		//当たり判定のサイズ
	std::map<std::string, double> exRate_;			//オブジェクトの大きさ
	std::map<std::string, AnimNode> animTbl_;
	std::list<std::string> checkObj_;
};

