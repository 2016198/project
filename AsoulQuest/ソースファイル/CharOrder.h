#pragma once

//�L�����N�^�[�̎��
enum class CHAR_TYPE
{
	PLAYER,
	ENEMY
};

class CharOrder
{
public:						//�����o�[�ϐ�
	CHAR_TYPE mCharType;	//�L�����N�^�[�̎��
	int mPosBottom;			//�L�����N�^�[�̑������W
	int mCharIndex;			//�L�����N�^�[�̓Y����
};
