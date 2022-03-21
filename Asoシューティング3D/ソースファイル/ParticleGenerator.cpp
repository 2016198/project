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
	//�摜�̃��[�h
	//mImgLight = LoadGraph("Image/Light.png");
	mImgLight = LoadGraph("Image/1919.png");

	//�l�p���b�V���쐬
	//CreateMeshSquare();

	//�~�`���b�V���쐬
	CreateMeshCircle();

	//�p�[�e�B�N���̏����ݒ�
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

	//�p�[�e�B�N���̍X�V
	for (auto& p : mParticles)
	{
		p->Update();

		//�������Ԃ��؂ꂽ��
		if (!p->IsAlive()) {
			if (isGenerate)
			{
				p = Generate(p);
				mStepGenerate = GEN_SEC;
				isGenerate = false;
			}
		}
	}

	//�f�o�b�N�p
	DebugProcess();
}

void ParticleGenerator::DebugProcess(void)
{
	Quaternion tmpQ;
	bool isHitKey = false;

	//����]
	if (CheckHitKey(KEY_INPUT_L))
	{
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(1.0f), AsoUtility::AXIS_Y);
	}

	//�E��]
	if (CheckHitKey(KEY_INPUT_J))
	{
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(-1.0f), AsoUtility::AXIS_Y);
	}

	//���]
	if (CheckHitKey(KEY_INPUT_I))
	{
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(1.0f), AsoUtility::AXIS_X);
	}

	//����]
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
	
	//�J�����̌���
	Camera* camera = mSceneManager->GetCamera();
	VECTOR c2t = camera->GetDir();

	VECTOR c2p;
	for (auto& p : mParticles)
	{
		//�J�������猩���p�[�e�B�N���̌���(�x�N�g��)
		c2p = VSub(p->GetPos(), camera->GetPos());
		float dot = VDot(c2t, c2p);

		//���s����
		p->SetZLen(dot);
	}

	//�C�e���[�^�[�E�R���N�V�����̃\�[�g
	std::sort(mParticles.begin(), mParticles.end(),
		[](Particle* x, Particle* y)
		{
			return x->GetZLen() > y->GetZLen();
		}
	);

	//�l�p���b�V���`��
	//DrawMeshSquare();

	//�~�`���b�V���`��
	DrawMeshCircle();

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	//�p�[�e�B�N���̕`��
	for (const auto& p : mParticles)
	{
		p->Draw();
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ParticleGenerator::DrawMeshSquare(void)
{
	//�l�p���b�V���̕`��
	DrawPolygon3D(mVerticesSquare, 2, DX_NONE_GRAPH, true);

	//���܂��Œ��_�̍��W�`��
	for (const auto& v : mVerticesSquare)
	{
		DrawSphere3D(v.pos, 2, 3, 0xff0000, 0xff0000, true);
	}
}

void ParticleGenerator::DrawMeshCircle(void)
{
	//�~�`���b�V���̕`��
	//0�̂Ƃ���͒��_���ł��B��ŏC�����܂��傤�B
	DrawPolygonIndexed3D(mVerticesCircle, NUM_POLYGON + 1, mIndexes, NUM_POLYGON, DX_NONE_GRAPH, true);

	//���܂��Œ��_�̍��W�`��
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
	//�����ʒu
	//-----------------------------------------------------------------------
	VECTOR pos;
	Quaternion rotY;

	//���_���W(�N�H�[�^�j�I��)
	rotY = Quaternion::AngleAxis(
		AsoUtility::Deg2RadF(static_cast<float>(GetRand(360))), AsoUtility::AXIS_Y);

	//�e�̊p�x�����ɍ���
	rotY = mQuaRot.Mult(rotY);

	//�h�[�i�c���Ή�
	float min = mRadius * (3.0f / 4.0f);
	pos = Quaternion::PosAxis(rotY, {0.0f, 0.0f, static_cast<float>(static_cast<int>(min) + GetRand(static_cast<int>(mRadius - min)))});


	pos = VAdd(mPos, pos);
	//-----------------------------------------------------------------------
	

	//�ړ�����
	//-----------------------------------------------------------------------
	VECTOR dir;
	//�@X����]�F(60�`80)
	Quaternion rotX;

	//���_���W(�N�H�[�^�j�I��)
	rotX = Quaternion::AngleAxis(
		AsoUtility::Deg2RadF(static_cast<float>(30 + GetRand(40 - 30)) * -1.0f), AsoUtility::AXIS_X);

	//�AY����]��X����]������
	Quaternion rot = rotY.Mult(rotX);

	//�B��]������ɕϊ�
	dir = rot.GetForward();
	//-----------------------------------------------------------------------

	//�傫��
	float size = GEN_MIN_SIZE + GetRand(GEN_MAX_SIZE - GEN_MIN_SIZE);

	//�ړ����x
	float speed = GEN_MIN_SPEED + GetRand(GEN_MAX_SPEED - GEN_MIN_SPEED);

	//��������
	float lifeTime = GEN_MIN_LIFE_TIME + GetRand(GEN_MAX_LIFE_TIME - GEN_MIN_LIFE_TIME);

	//����
	particle->Generate(pos, size, dir, speed, lifeTime);

	return particle;
}

void ParticleGenerator::CreateMeshSquare(void)
{
	//���F
	COLOR_U8 color = GetColorU8(255, 255, 255, 255);

	for (int g = 0; g < 6; g++)
	{
		mVerticesSquare[g].dif = color;
	}

	float h = 100.0f;
	float zero = 0.0f;

	//���W
	mVerticesSquare[0].pos = {zero, zero, zero };
	mVerticesSquare[1].pos = {zero, zero, h};
	mVerticesSquare[2].pos = {h, zero, h};

	mVerticesSquare[3].pos = {zero, zero, zero};
	mVerticesSquare[4].pos = {h, zero, h};
	mVerticesSquare[5].pos = {h, zero, zero};
}

void ParticleGenerator::CreateMeshCircle(void)
{
	//���F
	COLOR_U8 color = GetColorU8(255, 255, 255, 255);

	//���F
	COLOR_U8 senter = GetColorU8(0, 200, 0, 255);

	mVerticesCircle[0].dif = senter;
	for (int g = 1; g < NUM_POLYGON + 1; g++)
	{
		mVerticesCircle[g].dif = color;
	}

	//�{�̂̍��W
	VECTOR cPos = mPos;
	cPos.z += 0.1f;

	//�~�̒��S���W
	mVerticesCircle[0].pos = cPos;

	//�~���̃��[�v���쐬
	VECTOR pos;
	Quaternion rot;
	float cntAngle = 0.0f;
	for (int i = 0; i < NUM_POLYGON; i++)
	{
		//���_���W(�N�H�[�^�j�I��)
		rot = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(cntAngle), AsoUtility::AXIS_Y);

		//�p�x������
		rot = mQuaRot.Mult(rot);

		//���W�����
		pos = Quaternion::PosAxis(rot, { 0.0f, 0.0f, mRadius });

		//�\����
		mVerticesCircle[i + 1].pos = VAdd(cPos, pos);

		//��]�p�x��������
		cntAngle += SPLIT_ANGLE_DEG;
	}

	//���_�C���f�b�N�X
	unsigned short cntIndex = 0;

	//4�_
	for (int t = 0; t < 30; t += 3)
	{
		cntIndex++;
		mIndexes[t] = 0;
		mIndexes[t + 1] = cntIndex;
		mIndexes[t + 2] = cntIndex % NUM_POLYGON + 1;
	}
}
