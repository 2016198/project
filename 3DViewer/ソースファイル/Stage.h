#pragma once
#include <DxLib.h>
class SceneManager;

class Stage
{
public:

	Stage(SceneManager* manager);
	void Init(void);
	void UpDate(void);
	void Draw(void);
	void Release(void);

private:

	SceneManager* mSceneManager;

	//モデルのハンドルID
	int mModelId;

	//モデルの表示座標
	VECTOR mPos;
};

