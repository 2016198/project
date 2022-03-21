//#pragma once
#include "Vector2.h"
#include "gamecommon.h"

class Lift
{
private:
	static constexpr int LIFT_MAX_SPEED = 2;	//���t�g�̃X�s�[�h�̍ő�l
	static constexpr int LIFT_ALIVE_TIME = 600;	//���t�g�̕\���̍ő�l

	//���t�g�̏��
	enum class LIST_STYLE
	{
		NO,			//�\������Ă��Ȃ�
		YES,		//���˂���Ă���
		MAX
	};

	int mAnimCount;			//�A�j���[�V�����ϐ�
	int mImage[static_cast<int>(LIST_STYLE::MAX)];			//�O���t�B�b�N�n���h��
	Vector2 mPos;			//���W
	int mMoveSpeed;			//��������
	Vector2 mSize;			//���t�g�̑傫��
	bool mAlive;			//���t�g�̕\������Ă��邩

public:
	Lift(void);				//�R���X�g���X�^

	bool IsAlive(void);		//���t�g���\������Ă��邩
	Vector2 GetPos(void);	//���W��Ԃ��B

	bool Init(void);			//�C���X�^���X�̐���
	void UpDate(void);			//�C���X�^���X�̍X�V
	void Draw(void);			//�C���X�^���X�̕`��
	bool Release(void);			//�C���X�^���X�̊J��

	~Lift(void);				//�f�X�g���X�^
};
