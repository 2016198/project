#pragma once

class SceneManager;

class Particle
{
public:

	Particle(SceneManager* manager, int image);
	void Generate(VECTOR pos, float size, VECTOR dir, float speed, float life);
	void Update(void);
	void Draw(void);
	void Release(void);

	float GetZLen(void);
	void SetZLen(float len);
	VECTOR GetPos(void);

	bool IsAlive(void);

private:

	SceneManager* mSceneManager;

	//�O���t�B�b�N�n���h��
	int mImgLight;

	//���W
	VECTOR mPos;

	//�ړ�����
	VECTOR mDir;

	//�傫��
	float mSize;

	//�ړ����x
	float mSpeed;

	//��������
	float mLifeTime;

	//Z�\�[�g
	float mZLen;

	//�p�x
	float mAngle;
};

