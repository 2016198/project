#include <Dxlib.h>
#include <sstream>
#include "Controller.h"
#include "../../../tmx/rapidxml_utils.hpp"
#include "../../../tmx/rapidxml.hpp"

/*Controller::RingBuf* //���O��Ԃ���Ȃ��ƃG���[
{
	return nullptr;
}*/

Controller::RingBuf* Controller::RingBuf::Create(int no)//���O��Ԃ���Ȃ��ƃG���[
{
	int count = 1;
	auto beginBuf = new RingBuf{ 0,0,nullptr,nullptr };
	auto beforeBuf = beginBuf;
	auto nowBuf = beginBuf;
	for (int g = 1; g < no; g++)
	{
		count++;
		nowBuf = new RingBuf{ 0,0,beforeBuf,nullptr };
		beforeBuf->next = nowBuf;
		beforeBuf = nowBuf;
	}
	beginBuf->before = nowBuf;
	nowBuf->next = beginBuf;
	return beginBuf;
}

void Controller::RingBuf::Destroy(RingBuf* buf)
{
	/*auto nowBuf = beginBuf->before->next;
	auto nextBuf = nowBuf->next;
	while (nextBuf)
	{
		nextBuf = nextBuf->next;
		delete  nowBuf;
		nowBuf = nullptr;
		nowBuf = nextBuf->before;
	}*/
	if (buf->before == nullptr) { return; }//�����O�o�b�t�@�o�Ȃ��Ƃ��ȏ������Ȃ�

	buf->before->next = nullptr;//�O�̎��̃A�h���X�������B
	while (buf->next != nullptr)
	{
		buf = buf->next;
		delete buf->before;
		buf->before = nullptr;
	}//���̈ʒu�ɍs���Ă���O�̃A�h���X���폜����
	delete buf;
	buf = nullptr;
}

void Controller::cmdFail(void)
{
	canKey_ = check_ = false;
	auto drawBuf = startBuf_;
	while (drawBuf != ringBuf_)
	{
		drawBuf = drawBuf->next;
		drawBuf->value = 0;
		drawBuf->limit = 0;
	}
	startBuf_ = ringBuf_;
	for (auto miss : cmdMiss_)
	{
		miss = false;
	}
}

bool Controller::LoadCmd(std::string flieName, std::string objName)
{
	rapidxml::xml_document<> cmdDoc;
	rapidxml::file<> file = flieName.c_str();
	cmdDoc.parse<0>(file.data());
	rapidxml::xml_node<>* cmdList = cmdDoc.first_node();

	std::string value = cmdList->first_attribute("name")->value();
	if (value != objName) //�N�̃R�}���h�H
	{
		return false;
	}
	value = cmdList->first_attribute("version")->value();
	if (value != "1.0.6")//�o�[�W�����`�F�b�N
	{
		return false;
	}
	value = cmdList->last_attribute("size")->value();
	cmdList_.resize(atoi(value.c_str()));
	cmdItr_.resize(atoi(value.c_str()));
	cmdMiss_.resize(atoi(value.c_str()));
	int num = 0;

	for (auto cmdData = cmdList->first_node(); cmdData; cmdData = cmdData->next_sibling(), num++)
	{
		std::string name = cmdData->first_attribute("name")->value();//�Z�̖��O���擾

		/*TRACE("%s\n", cmdList_.second.c_str());
		std::string aaa = "�׌���";
		TRACE("%s\n", aaa.c_str());*/

		auto cmd = cmdData->first_node();
		cmdList_[num].first = name;
		cmdMiss_[num] = false;

		std::stringstream dataStream;
		dataStream << cmd->value();
		std::string numStr;
		while (getline(dataStream, numStr, ','))
		{
			auto key = atoi(numStr.c_str());
			getline(dataStream, numStr, ',');
			auto frame = atoi(numStr.c_str());
			getline(dataStream, numStr, ',');
			int time = atoi(numStr.c_str());
			cmdList_[num].second.emplace_back(std::array<int, 3U>{key, frame, time});
		}
		cmdItr_[num] = cmdList_[num].second.begin();
	}
	return true;
}

void Controller::WriteCmd(void)
{
	cmd = "empty";
	if (startBuf_ == nullptr)
	{
		startBuf_ = ringBuf_;
	}

	auto endTime = std::chrono::system_clock::now();
	int wirteData = 0;
	for (auto id : InputID())
	{
		if (cntData_[id][static_cast<int>(Trg::Now)])
		{
			wirteData |= 1 << static_cast<int>(id);
		}
	}
	if (wirteData && canKey_)
	{
		if (wirteData == ringBuf_->value)
		{
			ringBuf_->limit = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime_).count();
		}
		else
		{
			ringBuf_ = ringBuf_->next;
			ringBuf_->value = wirteData;
			startTime_ = std::chrono::system_clock::now();
		}

	}
	else
	{
		if (startBuf_ != ringBuf_)
		{
			if (ringBuf_->value != 512)
			{
				ringBuf_ = ringBuf_->next;
				ringBuf_->value = 512;
				ringBuf_->limit = 0;
				startTime_ = std::chrono::system_clock::now();
			}
			ringBuf_->limit = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime_).count();
			if (ringBuf_->limit > 5000)
			{
				startBuf_ = ringBuf_;
				ringBuf_->limit = 0;
			}
		}
	}


	/*if (wirteData == cmdItr_->at(0))
	{
		if (cmdItr_ == cmdList_.first.end() - 1)
		{
			cmdItr_ = cmdList_.first.begin();
			TRACE("��!\n");
		}
		else
		{
			cmdItr_ += 2;
			TRACE("!!\n");
			auto itr = cmdItr_ - 1;
		}
	}*/
	auto drawBuf = ringBuf_;//�����O�o�b�t�@��������Ƃ��������Ȃ�̂ł�����Ȃ�
	for (int g = 0; g < static_cast<int>(cmdList_.size()); g++)
	{
		if (startBuf_ != ringBuf_)
		{
			if (!cmdMiss_[g])
			{
				if (drawBuf->value == cmdItr_[g]->at(0))
				{
					if (!(cmdItr_[g] == cmdList_[g].second.end() - 1))
					{
						if (cmdItr_[g]->at(1) == 0)
						{
							++cmdItr_[g];
						}
					}
					else
					{
						//����
						//TRACE("%s\n", cmdList_[g].first.c_str());
						drawBuf = startBuf_;
						while (drawBuf != ringBuf_)
						{
							drawBuf = drawBuf->next;
							drawBuf->value = 0;
							drawBuf->limit = 0;
						}
						for (auto miss : cmdMiss_)
						{
							miss = false;
						}
						startBuf_ = ringBuf_;
						cmdItr_[g] = cmdList_[g].second.begin();
						canKey_ = false;
						cmd = cmdList_[g].first;
						break;
					}
					if (drawBuf->limit >= cmdItr_[g]->at(1))//���͂̎��Ԃ���������b�s�I
					{
						cmdMiss_[g] = true;
						check_ = true;
						cmdItr_[g] = cmdList_[g].second.begin();
						for (const auto miss : cmdMiss_)
						{
							check_ *= miss;
						}
					}
				}
				else
				{
					++cmdItr_[g];
					if (!(drawBuf->value == cmdItr_[g]->at(0)))//�ʂ̃L�[���������Ƃ��̃`�F�b�N
					{
						cmdMiss_[g] = true;
						check_ = true;
						cmdItr_[g] = cmdList_[g].second.begin();
						for (const auto miss : cmdMiss_)
						{
							check_ *= miss;//�S�����s��true�ɂȂ�
						}
					}
				}
			}
		}
		if (check_)
		{
			cmdFail();//�S�����s���Ă���΍ŏ�����
			break;
		}
	}
	if (wirteData == 0) //�����Ă��Ȃ��Ƃ��̓L�[���󂯕t����]
	{
		canKey_ = true;
	}
	//���s�쁫
	//for (auto id : InputID())
	//{
	//	if (cntData_[id][static_cast<int>(Trg::Now)] && !cntData_[id][static_cast<int>(Trg::Old)])
	//	{
	//		ringBuf_ = ringBuf_->next;
	//		if (startBuf_ == ringBuf_)
	//		{
	//			startBuf_ = startBuf_->next;//ringBuf����������炱���ɂ���
	//			_dbgDrawString(0, 0, "��������I���e��", 0xffffff);
	//		}
	//		ringBuf_->before->value = id;
	//		flag_ = CheckCmd();
	//	}
	//}
	//if (!flag_)//�R�}���h�~�X�̎�
	//{
	//	startBuf_ = ringBuf_;
	//}
	//else
	//{
	//	if (startBuf_ == ringBuf_)
	//	{
	//		startBuf_ = startBuf_->next;//ringBuf����������炱���ɂ���
	//		_dbgDrawString(0, 0, "��������I���e��...", 0xffffff);
	//	}
	//}

	//�f�o�b�O�p��
	/*int no = 0;
	while (drawBuf != ringBuf_)
	{
		_dbgDrawFormatString(no * 32, 560, 0xffffff, "%d", drawBuf->value);
		drawBuf = drawBuf->next;
		no++;
	}*/
	/*drawBuf = ringBuf_;
	for (int no = 0; drawBuf != startBuf_; no++, drawBuf = drawBuf->before)
	{
		_dbgDrawFormatString(no * 64, 560, 0xffffff, "%d", drawBuf->value);
		_dbgDrawFormatString(no * 64, 580, 0xffff00, "%d", no);
		_dbgDrawFormatString(no * 64, 600, 0xffff00, "%d", drawBuf->limit);
	}
	drawBuf = ringBuf_->next;
	for (int no = 0; drawBuf != ringBuf_; no++, drawBuf = drawBuf->next)
	{
		_dbgDrawFormatString(no * 64, 460, 0xffffff, "%d", drawBuf->value);
		_dbgDrawFormatString(no * 64, 480, 0xffff00, "%d", no);
		_dbgDrawFormatString(no * 64, 500, 0xffff00, "%d", drawBuf->limit);
	}
	int t = 0;
	for (const auto b : cmdMiss_) {
		_dbgDrawFormatString(600 + (t * 5), 500, 0xffffff, "%d", (int)b);
		t++;
	}*/
}