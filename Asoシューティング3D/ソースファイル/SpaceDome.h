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

	//ó‘Ô
	STATE mState;

	//©‹@‚Ìî•ñ
	Transform* mShipTransform;

	//ƒ‚ƒfƒ‹§Œä‚ÌŠî–{î•ñ
	Transform mTransform;

	//ó‘Ô‘JˆÚ
	void ChangeState(STATE state);
};

