#pragma once
#include "Transform.h" 

class SceneManager;
class Transform;

class SpaceDome
{

public:

	enum class STATE
	{
		NONE,
		STAY,
		FOLLOW
	};

	SpaceDome(SceneManager* manager, Transform* shipTransform);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	SceneManager* mSceneManager;

	//���
	STATE mState;

	//���@�̏��
	Transform* mShipTransform;

	//���f������̊�{���
	Transform mTransform;

	//��ԑJ��
	void ChangeState(STATE state);
};

