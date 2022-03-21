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

	bool LoadTMX(std::string fileName, std::string type);	//TMX�̃��[�h
	const TextMap& GetData();

private:
	TmxObj();				//�R���X�g���N�^
	~TmxObj();				//�f�X�g���N�^

	bool CheckTiledVersion(rapidxml::xml_node<>* node);		//�o�[�W�����`�F�b�N

	std::map<std::string, int> virsion_;					//�o�[�W�����ϐ�

	TextMap text_;	//�e�L�X�g�i�[�ϐ�
};