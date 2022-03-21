#include <DxLib.h>
#include "resource.h"
#include "class/scene/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	SetOutApplicationLogValidFlag(0);			//Log.txtを作成しない
	SetWindowIconID(101);						//.exeのアイコンチェンジ
	SetWindowText("TreasureGame");
	ChangeWindowMode(true);

	if (!lpSceneMng.Init())	//初期化処理
	{
		return -1;
	}

	lpSceneMng.Run();		//実行処理

	lpSceneMng.Release();	//解放処理

	return 0;				//プログラムの終了
}