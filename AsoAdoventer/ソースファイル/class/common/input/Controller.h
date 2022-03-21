#pragma once
#include <array>
#include <map>
#include <chrono>
#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include "../../../_debug/_DebugConOut.h"
#include "../../../_debug/_DebugDispOut.h"
#include "InputID.h"

using ChronoSysClock = std::chrono::system_clock::time_point;

//入力装置の種類
enum class CntType
{
	Key,
	Pad,
	Max
};

//キーのトリガー
enum class Trg
{
	Now,
	Old,
	Max
};

class Controller;

using uniqueInput = std::unique_ptr<Controller>;
using TrgBool = std::array<bool, static_cast<size_t>(Trg::Max)>;
using CntData = std::map<InputID, TrgBool>;
using CmdData = std::vector<std::array<int, 3U>>;
using CmdItr = std::vector<std::vector<std::array<int, 3U>>::iterator>;

//constexpr size_t max = 20U;

class Controller
{
public:
	struct RingBuf
	{
		int value;
		long long limit;
		RingBuf* before = nullptr;
		RingBuf* next = nullptr;
		//InputID id;
		static RingBuf* Create(int no);
		static void Destroy(RingBuf* beginBuf);
	};

	//using CommandData = std::array<RingBuf, max>;

	Controller() {};
	virtual ~Controller() {};

	virtual uniqueInput UpDate(uniqueInput ownInput) = 0;
	virtual CntType GetCntType(void) = 0;

	const CntData& GetCntData(void)
	{
		return cntData_;
	}
	std::string cmd = "empty";
private:
	ChronoSysClock startTime_;
	bool canKey_ = true;
	//bool flag_ = false;				//コマンドがあってる？
	//bool CheckCmd(void);			//コマンドチェック
	//std::vector<std::pair<InputID, int>> cmd;
	//size_t size_ = 0;
	std::vector<std::pair<std::string, CmdData>> cmdList_;//コマンド情報
	std::vector<bool> cmdMiss_;		//コマンドが失敗してる数
	int check_;						//コマンドがまだ作動しているか
	CmdItr cmdItr_;				//コマンドのイテレーター
	void cmdFail(void);
protected:
	CntData cntData_;
	bool LoadCmd(std::string flieName, std::string objName);
	//void Copy(void);
	void WriteCmd(void);		//コマンドの書き込み
	RingBuf* ringBuf_ = nullptr;	//キー情報の保存
	RingBuf* startBuf_ = nullptr;	//最初の位置ringBuf_でキーを放して止まった位置
	//CommandData com;
};

