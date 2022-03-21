#include <DxLib.h>
#include <time.h>
#include <iostream>
#include <chrono>
#include <EffekseerForDXLib.h>
#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"
#include "../manager/MaterialManager.h"
#include "../game/text/TextPool.h"
#include "GameTwoScene.h"
#include "TitleScene.h" 
#include "ResultScene.h"
#include "OptionScene.h"
#include "GameSoloScene.h"
#include "TutorialScene.h"
#include "SceneManager.h"

bool SceneManager::Init(void)
{
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);

	// DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return false;
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(false);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Effekseer��2D�`��̐ݒ������B
	Effekseer_Set2DSetting(SCREEN_SIZE_X, SCREEN_SIZE_Y);

	//����������
	srand((unsigned int)time(NULL));

	// �G�t�F�N�g���\�[�X��ǂݍ��ށB
	// �ǂݍ��ގ��ɑ傫�����w�肷��B
	effect_[0] = LoadEffekseerEffect("effect/effect.efkefc", 20.0f);
	if(effect_[0] == -1)
	{
		return false;
	}

	// �Đ����̃G�t�F�N�g�̃n���h��������������B
	effect_[1] = -1;

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(true);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(true);

	//�C���X�^���X�̐���
	uniqueScene_ = std::make_unique<TitleScene>(INPUT_TYPE::KEY);
	
	lpTextPool.Init();
	sound_ = lpMaterialMng.LoadSoundHandle("sound/blast.wav");
	image_ = lpMaterialMng.LoadGraphHandle("image/shape.png");
	for (const auto font : fontFile_)
	{
		if (lpMaterialMng.LoadFontHandle(font) == -1)
		{
			return false;
		}
	}

	if (sound_ == -1)
	{
		return false;
	}

	if (image_ == -1)
	{
		return false;
	}

	delta_ = deltaTime;
	nextScene_ = SCENE_ID::CONTINUE;
	animCnt = 0.0;
	angle_ = 0.0;
	sceneNum_ = 0;
	inputType_ = INPUT_TYPE::KEY;
	screen_ = -1;
	clear_ = false;
	return true;
}

void SceneManager::Run(void)
{
	auto start = std::chrono::system_clock::now();		//�v���X�^�[�g������ۑ�
	auto end = std::chrono::system_clock::now();		//�v���I��������ۑ�
	auto dur = end - start;								//�v�������Ԃ��v�Z
	auto msec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
	double delta = msec / 3000.0;
	effect_[1] = PlayEffekseer2DEffect(effect_[0]);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && gameEnd_ == false)
	{
		_dbgStartDraw();

		end = std::chrono::system_clock::now();			// �v���I��������ۑ�
		dur = end - start;								// �v�������Ԃ��v�Z
		msec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
		start = std::chrono::system_clock::now();     // �v���X�^�[�g������ۑ�

		//�X�V����
		delta = msec / 3000.0;
		num_ += delta * 1.5;
		animCnt += delta;
		angle_ = (3.1415 / 180.0) * static_cast<double>(static_cast<int>(num_) % 360);
		
		GetMousePoint(&mousePos_[0].x, &mousePos_[0].y);
		// ����I�ɃG�t�F�N�g���Đ�����
		if (mousePos_[0] != mousePos_[1])
		{
			if (animCnt > 30.0)
			{
				// �G�t�F�N�g���Đ�����B
				effect_[1] = PlayEffekseer2DEffect(effect_[0]);
			}
		}

		// �Đ����̃G�t�F�N�g���ړ�����B
		SetPosPlayingEffekseer2DEffect(effect_[1], static_cast<float>(mousePos_[0].x), static_cast<float>(mousePos_[0].y), 0.0f);

		// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
		UpdateEffekseer2D();

		mousePos_[1] = mousePos_[0];

		if (!fadeIn_ && !fadeOut_)
		{
			nextScene_ = uniqueScene_->Update(delta);
			if (static_cast<SCENE_ID>(nextScene_) != SCENE_ID::CONTINUE)
			{
				fadeOut_ = true;
			}
		}

		//�摜�̃��[�h�����A�`��̏�������T�C�Y��200�~80	
		// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
		//DrawEffekseer2D();

		//�`�揈���ł��炤�n���h���̓���
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		screen_ = uniqueScene_->Draw();
		if (screen_ == -1)
		{
			break;
		}

		//�Q�[���̕`��V�[��
		SetDrawScreen(DX_SCREEN_BACK);
		ClsDrawScreen();

		if (fadeOut_ == true || fadeIn_ == true)
		{
			//�t�F�C�h�������`��
			FadeCommand(static_cast<SCENE_ID>(nextScene_), delta);
			SetDrawBlendMode(DX_BLENDMODE_MULA, 255);
		}
		DrawGraph(0, 0, screen_, 1);

		//_dbgDraw();
		//�f�o�b�O�p
		if (CheckHitKey(KEY_INPUT_J))
		{
			DrawLine(SCREEN_SIZE_X / 2, 0, SCREEN_SIZE_X / 2, SCREEN_SIZE_Y, 0);
			DrawLine(0, SCREEN_SIZE_Y / 2, SCREEN_SIZE_X, SCREEN_SIZE_Y / 2, 0);
		}

		ScreenFlip();
	}
}

void SceneManager::Release(void)
{
	//�e�������
	lpMaterialMng.DeleteSoundHandle("sound/blast.wav");
	lpMaterialMng.DeleteGraphHandle("image/shape.png");
	for (const auto font : fontFile_)
	{
		lpMaterialMng.DeleteFontHandle(font);
	}
	lpTextPool.Release();
	if (uniqueScene_ != nullptr)
	{
		uniqueScene_->Release();
		uniqueScene_.release();
		uniqueScene_ = nullptr;
	}
	// �G�t�F�N�g���\�[�X���폜����B(Effekseer�I�����ɔj�������̂ō폜���Ȃ��Ă��������ǈꉞ�ˁH)
	DeleteEffekseerEffect(effect_[0]);

	// Effekseer���I������B
	Effkseer_End();

	//DxLib�̏I��
	DxLib_End();
}

void SceneManager::FadeCommand(SCENE_ID nextScene, double delta)
{
	if (fadeIn_)
	{
		delta_ += delta * 2.0;
		if (delta_ > deltaTime)
		{
			fadeIn_ = false;
		}
	}

	if (fadeOut_)
	{
		if (delta_ > deltaTime - 1.0)
		{
			if (CheckSoundMem(sound_) == 0)
			{
				PlaySoundMem(sound_, DX_PLAYTYPE_BACK);
			}
		}
		delta_ -= delta * 2.0;
		if (delta_ <= 0)
		{
			sceneNum_ = uniqueScene_->GetNum();
			sceneID_ = uniqueScene_->GetScene();
			//inputType_ = uniqueScene_->GetInputType();
			fadeOut_ = false;
			fadeIn_ = true;
			uniqueScene_->Release();
			uniqueScene_.release();

			switch (nextScene)
			{
			case SCENE_ID::RESULT:
				uniqueScene_ = std::make_unique<ResultScene>(inputType_, sceneNum_, sceneID_);
				break;
			case SCENE_ID::TITLE:
				uniqueScene_ = std::make_unique<TitleScene>(inputType_);
				break;
			case SCENE_ID::GAME_TWO:
				uniqueScene_ = std::make_unique<GameTwoScene>(inputType_);
				break;
			case SCENE_ID::GAME_ONE:
				uniqueScene_ = std::make_unique<GameSoloScene>(inputType_);
				break;
			case SCENE_ID::OPTION:
				uniqueScene_ = std::make_unique<OptionScene>(inputType_, clear_);
				break;
			case SCENE_ID::TUTORIAL:
				uniqueScene_ = std::make_unique<TutorialScene>(inputType_);
				break;
			case SCENE_ID::END:
				gameEnd_ = true;
				return;
				break;
			}
		}
	}

	DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, delta_ / 100.0, angle_, image_, true);
}