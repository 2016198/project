#pragma once
#include <vector>
#include "Quaternion.h"

class SceneManager;
class Particle;

class ParticleGenerator
{
public:

	//パーティクル生成数
	static constexpr int NUM_PARTICLE = 30;

	//円形自作ポリゴン
	static constexpr int NUM_POLYGON = 10.0f;
	static constexpr float SPLIT_ANGLE_DEG = 360.0f / static_cast<float>(NUM_POLYGON);

	//大きさ
	static constexpr int GEN_MIN_SIZE = 3.0f;
	static constexpr int GEN_MAX_SIZE = 5.0f;

	//移動速度
	static constexpr int GEN_MIN_SPEED = 1.0f;
	static constexpr int GEN_MAX_SPEED = 2.0f;

	//生存時間
	static constexpr int GEN_MIN_LIFE_TIME = 1.0f;
	static constexpr int GEN_MAX_LIFE_TIME = 2.0f;

	//徐々に生成
	static constexpr float GEN_SEC = 0.05f;
	

	ParticleGenerator(SceneManager* manager, VECTOR pos, float radius);
	void Init(void);
	void Update(void);
	void DebugProcess(void);
	void Draw(void);
	void DrawMeshSquare(void);
	void DrawMeshCircle(void);
	void Release(void);

	void SetPos(VECTOR pos);
	void SetRot(Quaternion rot);

private:

	SceneManager* mSceneManager;
	int mImgLight;

	//徐々に生成
	float mStepGenerate;

	//座標
	VECTOR mPos;

	//回転
	Quaternion mQuaRot;

	//半径
	float mRadius;

	//ポリゴンデータ(四角)
	VERTEX3D mVerticesSquare[6];

	//ポリゴンデータ(円形)
	VERTEX3D mVerticesCircle[NUM_POLYGON + 1];

	//頂点インデックス
	WORD mIndexes[NUM_POLYGON * 3];

	std::vector<Particle*> mParticles;

	//テスト用パーティクルの生成
	Particle* Generate(Particle* particle);

	//テスト用：四角のメッシュの作成
	void CreateMeshSquare(void);

	//テスト用：円形のメッシュの作成
	void CreateMeshCircle(void);
};

