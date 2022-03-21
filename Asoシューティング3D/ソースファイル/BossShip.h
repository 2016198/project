#pragma once
#include <vector>
#include "Transform.h"
#include "SpriteAnimator.h"

class SceneManager;
class PlayerShip;
class EventShot;
class Turret;

class BossShip
{
public:

	//�ړ��X�s�[�h
	static constexpr float SPEED_MOVE = 4.0f;

	//���e��̃C�x���g�̏I������
	static constexpr float TIME_EVENT = 4.0f;

	//�j�󉉏o����
	static constexpr float TIME_DESTROY = 4.0f;

	//���j�G�t�F�N�g�Ԋu
	static constexpr float TIME_BLAST = 1.0f;

	enum class STATE
	{
		NONE,
		EVENT,
		BATTLE,
		DESTROY,
		END
	};

	BossShip(SceneManager* sceneManager, PlayerShip* playerShip);
	void Init(void);
	void Update(void);
	void UpdateTurret(void);
	void Draw(void);
	void DrawTurret(void);
	void Release(void);

	Transform* GetTranceform(void);

	std::vector<Turret*> GetTurrets(void);

	//�{�X�̔j��
	void Destroy(void);

	//�{�X�̏�Ԃ��j�󂩊m�F
	bool IsAlive(void);	

private:

	SceneManager* mSceneManager;
	PlayerShip* mPlayerShip;
	// ���g�̔���
	std::vector<SpriteAnimator*> mExplosion;

	//�C�x���g�p�̒e
	EventShot* mEventShot;

	//���f������̊�{���
	Transform mTransform;

	//���
	STATE mState;

	//�^���b�g
	std::vector<Turret*> mTurrets;

	//�C�x���g���Ԃ̊Ǘ�
	float mStepEvent;

	//�j�󉉏o���Ԃ̊Ǘ�
	float mStepDestroy;

	//���j�G�t�F�N�g�̊Ǘ�
	float mStepBlast;

	//��ԑJ��
	void ChangeState(STATE state);

	//�^���b�g�̍쐬
	void MakeTurret(VECTOR localPos, VECTOR localAddAxis);
};

