#pragma once
#include "Transform.h"

class SceneManager;
class ParticleGenerator;
class SpriteAnimator;
class SpeechBalloon;
class PlayerShot;

class PlayerShip
{
public:

	//�ړ��X�s�[�h
	static constexpr float SPEED_MOVE = 10.0f;

	//���@�̉�]��
	static constexpr float SPEED_ROT_DEG_Y = 10.0f;
	static constexpr float SPEED_ROT_DEG_X = 10.0f;

	//�Փ˔���F���a
	static constexpr float COLLISION_RADIUS = 20.0f;

	//�e�̔��ˊԊu
	static constexpr float TIME_DELAY_SHOT = 0.2f;

	//3�E�F�C�V���b�g�̊p�x
	static constexpr float WAY_ANGLE = 5.0f;

	//���
	enum class STATE
	{
		NONE,
		RUN,
		DESTROY
	};

	PlayerShip(SceneManager* manager);
	void Init(void);
	void Update(void);
	void UpdateRun(void);
	void UpdateDestroy(void);
	void Draw(void);
	void Release(void);

	//����
	void ProcessTurn(void);
	void Turn(double deg, VECTOR axis);
	void ProcessShot(void);

	//���@�̔j��
	void Destroy(void);

	//���@�̏�Ԃ��j�󂩊m�F
	bool IsDestroy(void);

	Transform* GetTranceform(void);

	std::vector<PlayerShot*> GetShots(void);

	SpeechBalloon* GetSpeechBalloon(void);

private:

	SceneManager* mSceneManager;
	ParticleGenerator* mParticleGenerator;

	//���f������̊�{���
	Transform mTransform;

	//�����G�t�F�N�g
	SpriteAnimator* mExplosion;

	//���
	STATE mState;

	//�����o��
	SpeechBalloon* mSpeechBalloon;

	//�e
	std::vector<PlayerShot*> mShots;

	//�e�̔��ˊԊu
	float mDelayShot;

	//�����X�s�[�h
	float mAddMove;
	float mPow;

	//��ԑJ��
	void ChangeState(STATE state);

	//�e�𔭎�
	void CreateShot(double dir);
};

