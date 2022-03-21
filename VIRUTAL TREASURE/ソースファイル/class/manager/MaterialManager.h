#pragma once
#include <string>
#include <map>
#include <vector>
#include "../Vector2.h"

using VecInt = std::vector<int>;		//�O���t�B�b�N�n���h��				

#define lpMaterialMng MaterialManager::GetInstance()//�V���O���g�[��

class MaterialManager
{
private:
	std::map<std::string, VecInt> map_;	//�ǂݍ��ݗp�ϐ�
	
public:
	static MaterialManager& GetInstance()	//�C���X�^���X�̓���
	{
		static MaterialManager s_Instance;
		return s_Instance;
	}

	//�X�N���[���̃��[�h������
	const int& LoadScreenic(std::string key, int sizeX, int sizeY);
	

	//�摜�̃��[�h������F���łɓǂݍ���ł�����A���̒l��Ԃ�
	const int& LoadGraphHandle(std::string key);

	//���̃��[�h������F���łɓǂݍ���ł�����A���̒l��Ԃ�
	const int& LoadSoundHandle(std::string key);

	//�t�H���g�f�[�^�����[�h����F���łɓǂݍ���ł�����A���̒l��Ԃ�
	const int& LoadFontHandle(std::string key);

	//�摜�̃��[�h������F���łɓǂݍ���ł�����A���̒l��Ԃ�
	const VecInt& LoadDivGraphic(std::string key, Vector2 count);

	void DeleteGraphHandle(std::string key);		//�摜�̊J��
	void DeleteSoundHandle(std::string key);		//�T�E���h�̊J��
	void DeleteFontHandle(std::string key);			//�t�H���g�f�[�^�̊J��
};

