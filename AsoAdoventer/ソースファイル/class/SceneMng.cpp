#include <memory>
#include <DxLib.h>
#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneMng.h"

constexpr int ScreenSizeX = 1024;
constexpr int ScreenSizeY = 768;

//SceneMng* SceneMng::s_Instance = nullptr;


void SceneMng::UpDate(void)
{

}

void SceneMng::Draw(void)
{

}

bool SceneMng::SysInit(void)
{
	SetGraphMode(ScreenSizeX, ScreenSizeY, 32);
	ChangeWindowMode(true);
	SetWindowText("2016198_筒井杏二");
	if (DxLib_Init() == -1)
	{
		return false;
	}
	_dbgSetup(ScreenSizeX, ScreenSizeY, 255);
	return true;
}

void SceneMng::Run(void)
{
	if (!initFlag_)
	{
		if (!SysInit())
		{
			return;
		}
	}
	//int x, y, z;

	scene_ = std::make_unique<TitleScene>();
	//int x, y;
	//GetDrawScreenSize(&x, &y);

	auto start = std::chrono::system_clock::now();     // 計測スタート時刻を保存
	auto end = std::chrono::system_clock::now();       // 計測終了時刻を保存
	auto dur = end - start;        // 要した時間を計算
	auto msec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
	double delta = msec / 1000000.0;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();

		end = std::chrono::system_clock::now();       // 計測終了時刻を保存
		dur = end - start;        // 要した時間を計算
		msec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
		delta = msec / 10000.0;

		scene_ = scene_->UpDate(delta, std::move(scene_));

		SetDrawScreen(DX_SCREEN_BACK);
		ClsDrawScreen();
		//DrawBox(0, 0, x, y, 0x00ffff, true);
		//z = GetMousePoint(&x, &y);
		//DrawFormatString(0, 0, 0xffffff, "%d %d %d", x, y, z);
		scene_->Draw(delta);
		//_dbgDraw();
		ScreenFlip();
		start = std::chrono::system_clock::now();     // 計測スタート時刻を保存
	}
	InitGraph();
	DxLib_End();
}

SceneMng::SceneMng()
{
	initFlag_= SysInit();
}

SceneMng::~SceneMng()
{

}