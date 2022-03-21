#pragma once
#include <DxLib.h>

class SceneManager;
class Unit;

class Enemy
{
public:

	//視野の広さ
	static constexpr float VIEW_RANGE = 300.0f;

	//視野角
	static constexpr float VIEW_ANGLE = 30.0f;

	//アニメーションのスピード
	static constexpr float SPEED_ANIM = 50.0f;

	Enemy(SceneManager* manager, Unit* unit);
	void Init(void);
	void UpDate(void);
	void Draw(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetAnglePos(void);

private:
	SceneManager* mSceneManager;
	Unit* mUnit;

	//モデルのハンドルID
	int mModelId;
	int mModelid;

	//モデルの表示座標
	VECTOR mPos;

	//ユニットが範囲内に入っているか
	bool mIsNotice;

	//カメラ角度(rad)
	VECTOR mAngles;
	VECTOR mAnglesLocal;

};

