#include "Rock.h"

Rock::Rock(void)
{

}

void Rock::Init(int modelId, VECTOR pos, VECTOR angles, VECTOR scale)
{
	//���f������̊�{�ݒ�
	mTransform.SetModel(modelId);
	mTransform.scl = scale;
	mTransform.quaRot = Quaternion::Euler(angles);
	mTransform.quaRotLocal = Quaternion();
	mTransform.pos = pos;
	mTransform.Update();

}

void Rock::Update(void)
{

}

void Rock::Draw(void)
{
	MV1DrawModel(mTransform.modelId);
}

void Rock::Release(void)
{
	//�n����邾���Ȃ̂ŉ���͂��Ȃ�
	//MV1DeleteModel(mTransform.modelId);
}
