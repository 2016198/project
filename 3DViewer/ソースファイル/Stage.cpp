#include "Stage.h"

Stage::Stage(SceneManager* manager)
{
	mSceneManager = manager;
}

void Stage::Init(void)
{
	mModelId = MV1LoadModel("Model/Stage.mv1");
	mPos = { 0.0f,-100.0f,0.0f };

	//���f���̍��W��ݒ�
	MV1SetPosition(mModelId, mPos);
}

void Stage::UpDate(void)
{

}

void Stage::Draw(void)
{
	//X�̐�
	DrawLine(0, 0, 100, 0, 0xffffff);

	//Y�̐�
	DrawLine(0, 0, 0, 100, 0xffffff);

	float LEM_LINE = 500.0f;

	//XYZ�̃O���b�h���`��
	for (int x = -5; x < 5; x++)
	{
		DrawLine3D({ (float)(x) * 90.0f,0.0f,-500.0f }, { (float)(x) * 90.0f,0.0f,500.0f }, 0xff0000);
		DrawLine3D({ -500.0f,0.0f,(float)(x) * 90.0f }, { 500.0f,0.0f,(float)(x) * 90.0f }, 0x00ff00);
	}
	DrawLine3D({0.0f, -200.0f, 0.0f}, { 0.0f,200.0f,0.0f }, 0x5555ff);

	//���f���̕`��
	MV1DrawModel(mModelId);
}

void Stage::Release(void)
{
	MV1DeleteModel(mModelId);
}
