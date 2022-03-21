#include <DxLib.h>
#include "AsoUtility.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Transform.h"

Stage::Stage(SceneManager* manager, Transform* player)
{
	mSceneManager = manager;
	mPlayer = player;
}

void Stage::Init(void)
{
	//ダンジョン
	mModelDungeon = MV1LoadModel("Model/Rock/Dungeon.mv1");
	MV1SetScale(mModelDungeon, { 1.0f, 1.0f, 1.0f });
	mPosDungeon = { 1000.0f, 400.0f, 1300.0f };
	MV1SetPosition(mModelDungeon, mPosDungeon);
	float rad = AsoUtility::RadIn2PI(180.0f);
	MV1SetRotationXYZ(mModelDungeon, { 0.0f, 180.0f, 0.0f });

	//ボス
	mModelBoss = MV1LoadModel("Model/BossShip/BossShip.mv1");
	MV1SetScale(mModelBoss, { 2.0f, 2.0f, 2.0f });
	mPosBoss = { 14500.0f, -800.0f, 6500.0f };
	MV1SetPosition(mModelBoss, mPosBoss);
	rad = AsoUtility::RadIn2PI(180.0f);
	MV1SetRotationXYZ(mModelBoss, { 0.0f, 180.0f, 0.0f });

}

void Stage::Update(void)
{
	VECTOR pPos = mPlayer->pos;
	VECTOR bPos = mPosBoss;

	//ぶつかったらシーンチェンジ
	float distance =
		(pPos.x - bPos.x) * (pPos.x - bPos.x) +
		(pPos.y - bPos.y) * (pPos.y - bPos.y) +
		(pPos.z - bPos.z) * (pPos.z - bPos.z);

	if (distance < RADIUS * RADIUS)
	{
		mSceneManager->ChangeScene(
			SceneManager::SCENE_ID::EVENT, true);
	}
}

void Stage::Draw(void)
{
	//グリッド線の描画
	DrawGrid();

	MV1DrawModel(mModelDungeon);
	MV1DrawModel(mModelBoss);

	//デバッグ
	DrawSphere3D(mPosBoss, RADIUS, 10, 0xffffff, 0xffffff, false);
}

void Stage::DrawGrid(void)
{
	//線の長さ
	constexpr int LEN = 3000.0f;

	//線の間隔
	constexpr int TERM = 100.0f;

	//線の数
	constexpr int NUM = LEN / TERM;

	//XYZのグリッド線描画
	for (int x = -NUM; x < NUM; x++)
	{
		DrawLine3D(
			{ (float)(x) * TERM, 0.0f, -LEN },
			{ (float)(x) * TERM, 0.0f,  LEN },
			0x5555ff);
		DrawLine3D(
			{ -LEN,0.0f,(float)(x) * TERM },
			{  LEN,0.0f,(float)(x) * TERM },
			0xff5555);
	}
	DrawLine3D(
		{ 0.0f, -LEN, 0.0f },
		{ 0.0f,  LEN, 0.0f },
		0x55ff55);
}

void Stage::Release(void)
{
	MV1DeleteModel(mModelDungeon);
	MV1DeleteModel(mModelBoss);
}

int Stage::GetModelDungeon(void)
{
	return mModelDungeon;
}
