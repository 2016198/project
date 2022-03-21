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

//���͑��u�̎��
enum class CntType
{
	Key,
	Pad,
	Max
};

//�L�[�̃g���K�[
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
	//bool flag_ = false;				//�R�}���h�������Ă�H
	//bool CheckCmd(void);			//�R�}���h�`�F�b�N
	//std::vector<std::pair<InputID, int>> cmd;
	//size_t size_ = 0;
	std::vector<std::pair<std::string, CmdData>> cmdList_;//�R�}���h���
	std::vector<bool> cmdMiss_;		//�R�}���h�����s���Ă鐔
	int check_;						//�R�}���h���܂��쓮���Ă��邩
	CmdItr cmdItr_;				//�R�}���h�̃C�e���[�^�[
	void cmdFail(void);
protected:
	CntData cntData_;
	bool LoadCmd(std::string flieName, std::string objName);
	//void Copy(void);
	void WriteCmd(void);		//�R�}���h�̏�������
	RingBuf* ringBuf_ = nullptr;	//�L�[���̕ۑ�
	RingBuf* startBuf_ = nullptr;	//�ŏ��̈ʒuringBuf_�ŃL�[������Ď~�܂����ʒu
	//CommandData com;
};

