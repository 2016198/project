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

	//状態
	STATE mState;

	//自機の情報
	Transform* mShipTransform;

	//モデル制御の基本情報
	Transform mTransform;

	//状態遷移
	void ChangeState(STATE state);
};

