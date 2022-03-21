#include <DxLib.h>
class Unit;
#pragma once
class Camera
{

public:

	//カメラの高さ
	static constexpr float HEGHT = 300.0f;

	//注意点からカメラまでのXZ距離
	static constexpr float DIS_TARGET_TO_CAMERA = 500.0f;

	//注意点からキャラクターまでのXZ距離
	static constexpr float DIS_TARGET_TO_UNIT = 300.0f;

	Camera();
	~Camera();

	void Init(void);
	void Updata(void);
	void SetBeforeDraw(void);
	void Draw(void);
	void Release(void);

	void GetUnit(Unit* unit);

	VECTOR GetPos(void);
	VECTOR GetAnglePos(void);
	VECTOR GetTargetPos(void);

private:

	Unit* mUnit;

	//カメラの位置
	VECTOR mPos;

	//カメラ角度(rad)
	VECTOR mAngles;

	//中視点
	VECTOR mTargetPos;
};

