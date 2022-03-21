#pragma once
class SceneManager;
class Transform;

class Stage
{
public:

	static constexpr float RADIUS = 10000.0f;

	Stage(SceneManager* manager, Transform* player);
	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawGrid(void);
	void Release(void);

	//���f��ID
	int GetModelDungeon(void);

private:

	SceneManager* mSceneManager;
	Transform* mPlayer;

	//�_���W�������f��
	int mModelDungeon;
	VECTOR mPosDungeon;

	//�{�X���f��
	int mModelBoss;
	VECTOR mPosBoss;

};

