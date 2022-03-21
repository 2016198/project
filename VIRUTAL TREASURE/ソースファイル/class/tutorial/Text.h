#pragma once
#include <vector>
#include <string>
#include "../Input/BaseInput.h"
#include "../../tmx/TmxObj.h"

enum class TEXT_MODE
{
	OPERATION,			//���샂�[�h
	MANUAL,				//�������[�h
	CHANGE				//��ʂ̐؂�ւ�
};

class Text
{

public:

	Text();			//�R���X�g���X�^
	~Text();		//�f�X�g���N�^

	bool Init(void);													//����������
	void SetText(std::string key);										//�e�L�X�g���Z�b�g����
	TEXT_MODE Update(const InputList input1, const InputList input2, bool progress);	//�X�V����
	void Draw(double delta);											//�`�揈��
	void Release(void);													//�������

	std::vector<std::string>::iterator GetChildItr(void);				//�q�̃C�e���[�^�[�����
	std::vector<std::vector<std::string>>::iterator GetParentItr(void);	//�e�̃C�e���[�^�[�����

private:
	int sound_;							//�T�E���h�n���h��

	std::array<InputList, 2U> input_;	//���͏��
	int pos_;							//�X���C�h���W
	int font_;							//�t�H���g�n���h��
	TextMap text_;						//�t�H���g

	std::vector<std::string>::iterator childItr_;				//�q�̃C�e���[�^�[
	std::vector<std::vector<std::string>>::iterator parentItr_;	//�e�̃C�e���[�^�[
	std::string type_;											//�������郂�[�h
};