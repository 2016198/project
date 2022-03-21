#pragma once
#include <DxLib.h>

class SceneManager;

class ShotBall
{
public:

	//�e�̃X�s�[�h
	static constexpr float MOVE_SPEED = 10.0f;

	//�e��������܂ł̋���
	static constexpr float LIFE = 100.0f;

	ShotBall(SceneManager* manager);

	void Init(void);
	void UpDate(void);
	void Draw(void);

	void Create(VECTOR pos, float angleY, unsigned int color);
	void Destroy(void);
	bool IsAlive(void);
private:
	SceneManager* mSceneManager;

	VECTOR mPos;
	bool mAlive;
	float mLife;
	float mx,mz;
	unsigned int mColor;
};