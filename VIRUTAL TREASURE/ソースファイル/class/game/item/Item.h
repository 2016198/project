#pragma once
#include <string>
#include <map>
#include <vector>
#include "../../Vector2.h"

//�A�C�e���̎��
enum class ITEM
{
	COMPASS,		//���ʎ���
	DETECTOR,		//�����T�m�@
	MAGNET,			//����
	CANDLE,			//�낤����
	NONE,			//�Ȃ�
	MAX
};

enum class CANDLE		//�낤�����g�p�C�x���g
{
	COME_HERE,			//����������
	RANDOM_POS,			//�ǂ����ւ���
	NONE,				//�͂���
	CHANGE_POS,			//�ꏊ����
	ITEM_GET,			//�A�C�e������
	NO_ITEM,			//�A�C�e�����Ȃ�
	MOVE_PLAS,			//�ړ��ʂ�2�{�ɂȂ�	
	MOVE_MINUS,			//�ړ��ʂ�1�ɂȂ�
	NO_USE,				//���g�p���
};

class Item
{
public:
	bool Init(void);													//����������
	bool Update(double delta, double angle, Vector2 dis);				//�X�V����
	void Draw(int num);													//�`�揈��
	void Release(void);													//�������

	Item();						//�R���X�g���N�^
	~Item();					//�f�X�g���N�^

	void SetInfo(Vector2 pos, ITEM itemS, ITEM itemU, Vector2 pos2);	//���W�Ǝg�p���ꂽ�A�C�e�����̓���
	double GetLife(void);												//�\�����Ԃ̎擾
	bool setMode_;														//���[�v���[�h�B
	CANDLE candle;														//�낤�����̏��

private:

	struct Info
	{
		Vector2 pos;			//�g�p�������W
		ITEM useItem;			//�g��ꂽ�A�C�e��
		ITEM selectItem;		//�I���A�C�e��
		double angle;			//�摜�̌X��
		double life;			//�A�C�e���̕\������
		bool search;			//�߂��ɖړI�n�����邩
	};

	Info info_;										//�A�C�e���̏��
	double delta_;									//�f���^�^�C��
	double distance_[2];							//�ړI�n�܂ł̋���
	int font_;										//�t�H���g�n���h��
	Vector2 movePos_;								//�ړ�������W
	Vector2 drawPos_;								//�`����W
	Vector2 movePow_;								//�ړ���

	static constexpr double MOVE = 10.0;			//���̈ړ���
							
	std::map<std::string, std::vector<std::string>> fileName_;			//�t�@�C���̃f�B���N�g��
	std::vector<int> image_;											//�O���t�B�b�N�n���h��
	std::vector<int> sound_;											//���ʉ��n���h��
};