#include <DxLib.h>
class Unit;
#pragma once
class Camera
{

public:

	//�J�����̍���
	static constexpr float HEGHT = 300.0f;

	//���ӓ_����J�����܂ł�XZ����
	static constexpr float DIS_TARGET_TO_CAMERA = 500.0f;

	//���ӓ_����L�����N�^�[�܂ł�XZ����
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

	//�J�����̈ʒu
	VECTOR mPos;

	//�J�����p�x(rad)
	VECTOR mAngles;

	//�����_
	VECTOR mTargetPos;
};

