//#pragma once
#include "Vector2.h"
#include "gamecommon.h"

//�e�̃C���X�^���X
class GameScene;

class Shot
{
private:
	static constexpr int SHOT_MAX_LIFE = 30;	//�e�̃��C�t�ő�l
	static constexpr int SHOT_MAX_SPEED = 15;	//�e�̃X�s�[�h�̍ő�l

	GameScene* mParent;
	int mImage;			//�e�̉摜
	Vector2 mPos;		//�e�̍��W
	int mMoveSpeed;		//�e�̑���
	int mLife;			//�e�̃��C�t
	
public:
	Shot(GameScene* parent);	//�R���X�g���X�^

	void CreateShot(Vector2 targetPos, DIR targetDir);		//�e�̍��W�ƌ����^�[�Q�b�g���󂯎��
	bool IsAlive(void);										//�e���\������Ă��邩�ǂ���
	void Destroy(void);		  //�摜������

	bool Init(void);		//�C���X�^���X�̐���
	Vector2 UpDate(void);	//�C���X�^���X�̍X�V
	void Draw(void);		//�C���X�^���X�̕`��
	bool Release(void);		//�C���X�^���X�̊J��

	~Shot(void);			//�f�X�g���X�^
};