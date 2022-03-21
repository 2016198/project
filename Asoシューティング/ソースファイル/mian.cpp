//2016198_筒井杏二

#include "DxLib.h"
#include "time.h"
#include "main.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "GameClear.h"
#include "_debug/_DebugDispOut.h"
#include "_debug/_DebugConOut.h"

//変数の宣伝
SCENE_ID sceneID;                             //シーンの宣伝
bool enterKeyBack;                            //スペースの１フレーム前の状態
bool enterKeyTriggerKeyDown;                  //エンターキーのトリガー（押されたとき）
bool enterKeyTriggerKeyUp;                    //エンターキーのトリガー（話されたとき）

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//----------------システム処理
	SetWindowText("課題3_2016198_筒井杏二");
 	//システム処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);           //640x480ドット65536色モードの設定
	ChangeWindowMode(true);                                   //true:window   false:フルスクリーン
	if (DxLib_Init() == -1)                                   //Dxライブラリーの初期化
	{
		return -1;
	}
	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 225);

	//乱数の初期化
	srand((unsigned int)time(NULL));              

	//各種初期化処理
	sceneID = TITLE_SCENE;

	//インスタンスの生成
	GameScene gamescene;
	TitleScene titlescene;
	GameOverScene gameover;
	GameClear gameclear;

	//インスタンスの初期化
	if (!gamescene.Init()) return -1;
	if (!titlescene.Init()) return -1;
	if (!gameover.Init()) return -1;
	if (!gameclear.Init()) return -1;

	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		KeyCheck();                                     //トリガーチェック
		_dbgStartDraw();
		SetDrawScreen(DX_SCREEN_BACK);                  //バックバッファに設定
		ClsDrawScreen();                                //画面消去
		if (enterKeyTriggerKeyDown == true)
		{
			if (sceneID == TITLE_SCENE)
			{
				sceneID = GAME_SCENE;
			}
			if (sceneID == GAME_OVER_SCENE)
			{
				sceneID = TITLE_SCENE;
			}
			if (sceneID == GAME_CLEAR_SCENE)
			{
				gameclear.Reset();
				if (!gamescene.GameInit()) return -1;           //ゲームクリアの処理
				if (!titlescene.GameInit()) return -1;
				sceneID = TITLE_SCENE;
			}
		}
		if (gamescene.GameOver())
		{
			sceneID = GAME_OVER_SCENE;                      
			if (!gamescene.GameInit()) return -1;           //ゲームオーバー後の処理
			if (!titlescene.GameInit()) return -1;
		}
		if (gamescene.GameClear())
		{
			sceneID = GAME_CLEAR_SCENE;
		}
		switch (sceneID)
		{
		case TITLE_SCENE:
			titlescene.UpDate();                            //タイトルシーン更新処理
			titlescene.Draw();                              //タイトルシーン描画処理
			break;
		case GAME_SCENE:
			gamescene.UpDate();                             //ゲームシーン更新処理
			gamescene.Draw();                               //ゲームシーン描画処理
			break;
		case GAME_OVER_SCENE:
			gameover.UpDate();                              //ゲームオーバーシーン更新処理
			gameover.Draw();                                //ゲームオーバーシーン描画処理
			break;
		case GAME_CLEAR_SCENE:
			gameclear.UpDate();
			gameclear.Draw(gamescene.Score());
			break;
		default:
			break;
		}

		_dbgAddDraw();
		ScreenFlip();     //裏画面を表画面にコピー
	}

	if (!gameclear.Release()) return -1;
	if (!gameover.Release()) return -1;
	if (!titlescene.Release())return -1;
	if (!gamescene.Release()) return -1;

	DxLib_End();  //Dxライブラリの終了
	return 0;     //プログラムの終了
}

void KeyCheck(void)
{
	if (CheckHitKey(KEY_INPUT_RETURN) && enterKeyBack == false)
	{
		enterKeyTriggerKeyDown = true;
		//TRACE("down");
	}
	else
	{
		enterKeyTriggerKeyDown = false;
	}
	if (!CheckHitKey(KEY_INPUT_RETURN) && enterKeyBack == true)
	{
		enterKeyTriggerKeyUp = true;
		//TRACE("up");
	}
	else
	{
		enterKeyTriggerKeyUp = false;
	}
	if (enterKeyBack == true)
	{
		//TRACE("前 on");
	}
	else
	{
		//TRACE("前 off");
	}
	if (CheckHitKey(KEY_INPUT_RETURN))
	{
		//TRACE("今 on\n");
		enterKeyBack = true;
	}
	else
	{
		//TRACE("今 off\n");
		enterKeyBack = false;
	}
	
}
