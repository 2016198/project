#pragma once
#include <DxLib.h>

class SceneManager;

class TankShot
{
public:

	TankShot(SceneManager* manager);
	void Generate(VECTOR pos, VECTOR forward, unsigned int color);
	void Update(void);
	void Draw(void);

	//�����m�F
	bool IsAlive(void);

private:

	//�e�̑��x
	static constexpr float SPEED = 10.0f;

	//�e�̐���
	static constexpr float LIFE = 5.0f;

	SceneManager* mSceneManager;

	//�F�R�[�h
	unsigned int mColor;

	//��������
	float mLife;

	//�e�̍��W
	VECTOR mPos;

	//�ړ�����
	VECTOR mMovePow;
};

