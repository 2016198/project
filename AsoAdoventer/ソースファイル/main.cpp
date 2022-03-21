#include <chrono>
#include <memory>
#include <DxLib.h>
#include "class/SceneMng.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	lpSceneMng.Run();

	return 0;
}