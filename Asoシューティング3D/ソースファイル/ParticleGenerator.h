#pragma once
#include <vector>
#include "Quaternion.h"

class SceneManager;
class Particle;

class ParticleGenerator
{
public:

	//�p�[�e�B�N��������
	static constexpr int NUM_PARTICLE = 30;

	//�~�`����|���S��
	static constexpr int NUM_POLYGON = 10.0f;
	static constexpr float SPLIT_ANGLE_DEG = 360.0f / static_cast<float>(NUM_POLYGON);

	//�傫��
	static constexpr int GEN_MIN_SIZE = 3.0f;
	static constexpr int GEN_MAX_SIZE = 5.0f;

	//�ړ����x
	static constexpr int GEN_MIN_SPEED = 1.0f;
	static constexpr int GEN_MAX_SPEED = 2.0f;

	//��������
	static constexpr int GEN_MIN_LIFE_TIME = 1.0f;
	static constexpr int GEN_MAX_LIFE_TIME = 2.0f;

	//���X�ɐ���
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

	//���X�ɐ���
	float mStepGenerate;

	//���W
	VECTOR mPos;

	//��]
	Quaternion mQuaRot;

	//���a
	float mRadius;

	//�|���S���f�[�^(�l�p)
	VERTEX3D mVerticesSquare[6];

	//�|���S���f�[�^(�~�`)
	VERTEX3D mVerticesCircle[NUM_POLYGON + 1];

	//���_�C���f�b�N�X
	WORD mIndexes[NUM_POLYGON * 3];

	std::vector<Particle*> mParticles;

	//�e�X�g�p�p�[�e�B�N���̐���
	Particle* Generate(Particle* particle);

	//�e�X�g�p�F�l�p�̃��b�V���̍쐬
	void CreateMeshSquare(void);

	//�e�X�g�p�F�~�`�̃��b�V���̍쐬
	void CreateMeshCircle(void);
};

