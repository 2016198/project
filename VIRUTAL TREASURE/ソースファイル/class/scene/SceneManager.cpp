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

	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return false;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(false);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Effekseerに2D描画の設定をする。
	Effekseer_Set2DSetting(SCREEN_SIZE_X, SCREEN_SIZE_Y);

	//初期化処理
	srand((unsigned int)time(NULL));

	// エフェクトリソースを読み込む。
	// 読み込む時に大きさを指定する。
	effect_[0] = LoadEffekseerEffect("effect/effect.efkefc", 20.0f);
	if(effect_[0] == -1)
	{
		return false;
	}

	// 再生中のエフェクトのハンドルを初期化する。
	effect_[1] = -1;

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(true);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(true);

	//インスタンスの生成
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
	auto start = std::chrono::system_clock::now();		//計測スタート時刻を保存
	auto end = std::chrono::system_clock::now();		//計測終了時刻を保存
	auto dur = end - start;								//要した時間を計算
	auto msec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
	double delta = msec / 3000.0;
	effect_[1] = PlayEffekseer2DEffect(effect_[0]);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && gameEnd_ == false)
	{
		_dbgStartDraw();

		end = std::chrono::system_clock::now();			// 計測終了時刻を保存
		dur = end - start;								// 要した時間を計算
		msec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
		start = std::chrono::system_clock::now();     // 計測スタート時刻を保存

		//更新処理
		delta = msec / 3000.0;
		num_ += delta * 1.5;
		animCnt += delta;
		angle_ = (3.1415 / 180.0) * static_cast<double>(static_cast<int>(num_) % 360);
		
		GetMousePoint(&mousePos_[0].x, &mousePos_[0].y);
		// 定期的にエフェクトを再生する
		if (mousePos_[0] != mousePos_[1])
		{
			if (animCnt > 30.0)
			{
				// エフェクトを再生する。
				effect_[1] = PlayEffekseer2DEffect(effect_[0]);
			}
		}

		// 再生中のエフェクトを移動する。
		SetPosPlayingEffekseer2DEffect(effect_[1], static_cast<float>(mousePos_[0].x), static_cast<float>(mousePos_[0].y), 0.0f);

		// Effekseerにより再生中のエフェクトを更新する。
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

		//画像のロードをし、描画の処理するサイズは200×80	
		// Effekseerにより再生中のエフェクトを描画する。
		//DrawEffekseer2D();

		//描画処理でもらうハンドルの入手
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		screen_ = uniqueScene_->Draw();
		if (screen_ == -1)
		{
			break;
		}

		//ゲームの描画シーン
		SetDrawScreen(DX_SCREEN_BACK);
		ClsDrawScreen();

		if (fadeOut_ == true || fadeIn_ == true)
		{
			//フェイド処理＆描画
			FadeCommand(static_cast<SCENE_ID>(nextScene_), delta);
			SetDrawBlendMode(DX_BLENDMODE_MULA, 255);
		}
		DrawGraph(0, 0, screen_, 1);

		//_dbgDraw();
		//デバッグ用
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
	//各解放処理
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
	// エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいいけど一応ね？)
	DeleteEffekseerEffect(effect_[0]);

	// Effekseerを終了する。
	Effkseer_End();

	//DxLibの終了
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