#include <algorithm>
#include <DxLib.h>
#include "Quaternion.h"
#include "AsoUtility.h"
#include "SceneManager.h"
#include "Camera.h"
#include "ParticleGenerator.h"
#include "Particle.h"

ParticleGenerator::ParticleGenerator(SceneManager* manager, VECTOR pos, float radius)
{
	mSceneManager = manager;
	mPos = pos;
	mRadius = radius;
}

void ParticleGenerator::Init(void)
{
	//画像のロード
	//mImgLight = LoadGraph("Image/Light.png");
	mImgLight = LoadGraph("Image/1919.png");

	//四角メッシュ作成
	//CreateMeshSquare();

	//円形メッシュ作成
	CreateMeshCircle();

	//パーティクルの初期設定
	for (int e = 0; e < NUM_PARTICLE; e++)
	{
		mParticles.push_back(Generate(new Particle(mSceneManager, mImgLight)));
	}
	mStepGenerate = GEN_SEC;
}

void ParticleGenerator::Update(void)
{
	bool isGenerate = false;
	mStepGenerate -= mSceneManager->GetDeltaTime();
	if (mStepGenerate < 0.0f)
	{
		isGenerate = true;
	}

	//パーティクルの更新
	for (auto& p : mParticles)
	{
		p->Update();

		//生存時間が切れたら
		if (!p->IsAlive()) {
			if (isGenerate)
			{
				p = Generate(p);
				mStepGenerate = GEN_SEC;
				isGenerate = false;
			}
		}
	}

	//デバック用
	DebugProcess();
}

void ParticleGenerator::DebugProcess(void)
{
	Quaternion tmpQ;
	bool isHitKey = false;

	//左回転
	if (CheckHitKey(KEY_INPUT_L))
	{
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(1.0f), AsoUtility::AXIS_Y);
	}

	//右回転
	if (CheckHitKey(KEY_INPUT_J))
	{
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(-1.0f), AsoUtility::AXIS_Y);
	}

	//上回転
	if (CheckHitKey(KEY_INPUT_I))
	{
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(1.0f), AsoUtility::AXIS_X);
	}

	//下回転
	if (CheckHitKey(KEY_INPUT_K))
	{
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(-1.0f), AsoUtility::AXIS_X);
	}

	if (isHitKey == true)
	{
		mQuaRot = mQuaRot.Mult(tmpQ);
		CreateMeshCircle();
	}
}

void ParticleGenerator::Draw(void)
{
	
	//カメラの向き
	Camera* camera = mSceneManager->GetCamera();
	VECTOR c2t = camera->GetDir();

	VECTOR c2p;
	for (auto& p : mParticles)
	{
		//カメラから見たパーティクルの向き(ベクトル)
		c2p = VSub(p->GetPos(), camera->GetPos());
		float dot = VDot(c2t, c2p);

		//奥行距離
		p->SetZLen(dot);
	}

	//イテレーター・コレクションのソート
	std::sort(mParticles.begin(), mParticles.end(),
		[](Particle* x, Particle* y)
		{
			return x->GetZLen() > y->GetZLen();
		}
	);

	//四角メッシュ描画
	//DrawMeshSquare();

	//円形メッシュ描画
	DrawMeshCircle();

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	//パーティクルの描画
	for (const auto& p : mParticles)
	{
		p->Draw();
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ParticleGenerator::DrawMeshSquare(void)
{
	//四角メッシュの描画
	DrawPolygon3D(mVerticesSquare, 2, DX_NONE_GRAPH, true);

	//おまけで頂点の座標描画
	for (const auto& v : mVerticesSquare)
	{
		DrawSphere3D(v.pos, 2, 3, 0xff0000, 0xff0000, true);
	}
}

void ParticleGenerator::DrawMeshCircle(void)
{
	//円形メッシュの描画
	//0のところは頂点数です。後で修正しましょう。
	DrawPolygonIndexed3D(mVerticesCircle, NUM_POLYGON + 1, mIndexes, NUM_POLYGON, DX_NONE_GRAPH, true);

	//おまけで頂点の座標描画
	for (const auto& v : mVerticesCircle)
	{
		DrawSphere3D(v.pos, 2, 3, 0xff0000, 0xff0000, true);
	}
}

void ParticleGenerator::Release(void)
{
	DeleteGraph(mImgLight);
	for (const auto& p : mParticles)
	{
		p->Release();
	}
}

void ParticleGenerator::SetPos(VECTOR pos)
{
	mPos = pos;
}

void ParticleGenerator::SetRot(Quaternion rot)
{
	mQuaRot = rot;
}

Particle* ParticleGenerator::Generate(Particle* particle)
{
	//発生位置
	//-----------------------------------------------------------------------
	VECTOR pos;
	Quaternion rotY;

	//頂点座標(クォータニオン)
	rotY = Quaternion::AngleAxis(
		AsoUtility::Deg2RadF(static_cast<float>(GetRand(360))), AsoUtility::AXIS_Y);

	//親の角度から先に合成
	rotY = mQuaRot.Mult(rotY);

	//ドーナツ化対応
	float min = mRadius * (3.0f / 4.0f);
	pos = Quaternion::PosAxis(rotY, {0.0f, 0.0f, static_cast<float>(static_cast<int>(min) + GetRand(static_cast<int>(mRadius - min)))});


	pos = VAdd(mPos, pos);
	//-----------------------------------------------------------------------
	

	//移動方向
	//-----------------------------------------------------------------------
	VECTOR dir;
	//①X軸回転：(60～80)
	Quaternion rotX;

	//頂点座標(クォータニオン)
	rotX = Quaternion::AngleAxis(
		AsoUtility::Deg2RadF(static_cast<float>(30 + GetRand(40 - 30)) * -1.0f), AsoUtility::AXIS_X);

	//②Y軸回転とX軸回転を合成
	Quaternion rot = rotY.Mult(rotX);

	//③回転を方向に変換
	dir = rot.GetForward();
	//-----------------------------------------------------------------------

	//大きさ
	float size = GEN_MIN_SIZE + GetRand(GEN_MAX_SIZE - GEN_MIN_SIZE);

	//移動速度
	float speed = GEN_MIN_SPEED + GetRand(GEN_MAX_SPEED - GEN_MIN_SPEED);

	//生存時間
	float lifeTime = GEN_MIN_LIFE_TIME + GetRand(GEN_MAX_LIFE_TIME - GEN_MIN_LIFE_TIME);

	//生成
	particle->Generate(pos, size, dir, speed, lifeTime);

	return particle;
}

void ParticleGenerator::CreateMeshSquare(void)
{
	//白色
	COLOR_U8 color = GetColorU8(255, 255, 255, 255);

	for (int g = 0; g < 6; g++)
	{
		mVerticesSquare[g].dif = color;
	}

	float h = 100.0f;
	float zero = 0.0f;

	//座標
	mVerticesSquare[0].pos = {zero, zero, zero };
	mVerticesSquare[1].pos = {zero, zero, h};
	mVerticesSquare[2].pos = {h, zero, h};

	mVerticesSquare[3].pos = {zero, zero, zero};
	mVerticesSquare[4].pos = {h, zero, h};
	mVerticesSquare[5].pos = {h, zero, zero};
}

void ParticleGenerator::CreateMeshCircle(void)
{
	//白色
	COLOR_U8 color = GetColorU8(255, 255, 255, 255);

	//白色
	COLOR_U8 senter = GetColorU8(0, 200, 0, 255);

	mVerticesCircle[0].dif = senter;
	for (int g = 1; g < NUM_POLYGON + 1; g++)
	{
		mVerticesCircle[g].dif = color;
	}

	//本体の座標
	VECTOR cPos = mPos;
	cPos.z += 0.1f;

	//円の中心座標
	mVerticesCircle[0].pos = cPos;

	//円周のループを作成
	VECTOR pos;
	Quaternion rot;
	float cntAngle = 0.0f;
	for (int i = 0; i < NUM_POLYGON; i++)
	{
		//頂点座標(クォータニオン)
		rot = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(cntAngle), AsoUtility::AXIS_Y);

		//角度を合成
		rot = mQuaRot.Mult(rot);

		//座標を作る
		pos = Quaternion::PosAxis(rot, { 0.0f, 0.0f, mRadius });

		//構造体
		mVerticesCircle[i + 1].pos = VAdd(cPos, pos);

		//回転角度を加える
		cntAngle += SPLIT_ANGLE_DEG;
	}

	//頂点インデックス
	unsigned short cntIndex = 0;

	//4点
	for (int t = 0; t < 30; t += 3)
	{
		cntIndex++;
		mIndexes[t] = 0;
		mIndexes[t + 1] = cntIndex;
		mIndexes[t + 2] = cntIndex % NUM_POLYGON + 1;
	}
}
