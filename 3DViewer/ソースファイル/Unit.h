#pragma once
#include <DxLib.h>

class SceneManager;

class Unit
{
public:

	//�A�j���[�V�����̃X�s�[�h
	static constexpr float SPEED_ANIM = 40.0f;

	//���X�ɉ�]�����
	static constexpr float SPEED_ROT = 5.0f;
	static constexpr float SPEED_ROT_RAT = SPEED_ROT * (DX_PI_F / 180.0f);

	Unit(SceneManager* manager);
	void Init(void);
	void UpDate(void);
	void Draw(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetAnglePos(void);

private:

	SceneManager* mSceneManager;

	//���f���̃n���h��ID
	int mModelId;

	//�A�j���[�V�����p�̃n���h��ID
	int mAnimWalk;
	
	//���f���̕\�����W
	VECTOR mPos;

	//�J�����p�x(rad)
	VECTOR mAngles;
	VECTOR mAnglesLocal;

	//�A�j���[�V�����̑��Đ�����
	float mTimeTotalAnimWalk;

	//�A�j���[�V�����̃X�e�b�v����
	float mStepAnim;
};