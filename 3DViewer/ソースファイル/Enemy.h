#pragma once
#include <DxLib.h>

class SceneManager;
class Unit;

class Enemy
{
public:

	//����̍L��
	static constexpr float VIEW_RANGE = 300.0f;

	//����p
	static constexpr float VIEW_ANGLE = 30.0f;

	//�A�j���[�V�����̃X�s�[�h
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

	//���f���̃n���h��ID
	int mModelId;
	int mModelid;

	//���f���̕\�����W
	VECTOR mPos;

	//���j�b�g���͈͓��ɓ����Ă��邩
	bool mIsNotice;

	//�J�����p�x(rad)
	VECTOR mAngles;
	VECTOR mAnglesLocal;

};

