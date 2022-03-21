#include<Dxlib.h>
#include <iostream>
#include <string>
#include "Geometry.h"

using Position2 = Vector2;

//struct Rect
//{
//	Position2 center;//中心点
//	float w;//幅の半分
//	float h;//高さの半分
//	float Left()const;//左の座標を返す
//	float Top()const;//上の座標を返す
//	float Right()const;//右の座標を返す
//	float Bottom()const;//下の座標を返す
//
//	float Width()const;//幅
//	float Height()const;//高さ
//};

using namespace std;
//メモリの見方
//デバッグ状態でウィンドウの中のメモリ

Position2 GetMousePositon2()
{
	int mx, my;
	GetMousePoint(&mx, &my);
	return Position2{ (float)mx,(float)my };
}

float DegreeToRadian(float def)
{
	return def * DX_PI_F / 180.0f;
}

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	SetGraphMode(640, 480, 32);
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(true);
	SetWindowText("2016198_筒井杏二");
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	Rect rcA = { 100.0f,100.0f,75,75 };
	char key[256];
	constexpr float speed = 4.0f;

	int Image[6];
	std::string path = ("Individual Sprites/bk/adventurer-attack2-0");
	std::string name[6] = {
		"0",
		"1",
		"2",
		"3",
		"4",
		"5"
	};
	int tile = LoadGraph("Tiles/Assets/Assets.png");
	for (int t = 0; t < 6; t++)
	{
		Image[t] = LoadGraph((path + name[t] + ".png").c_str());
	}
	int image = LoadGraph("arrow.png");
	int num = 0;
	int mouselast = 0;
	bool isReverse = false;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int mouse = GetMouseInput();
		if ((mouse & MOUSE_INPUT_LEFT) &&
			(mouselast & MOUSE_INPUT_LEFT) == 0)
		{
			if (isReverse)
			{
				isReverse = false;
			}
			else
			{
				isReverse = true;
			}
		}
		mouselast = GetMouseInput();

		int centerX = 16;
		if (isReverse)
		{
			int x, y;
			GetGraphSize(Image[num / 10 % 4], &x, &y);
			centerX = x - centerX;
		}
		GetHitKeyStateAll(key);
		if (key[KEY_INPUT_LEFT])
		{
			rcA.pos.x -= speed;
		}
		if (key[KEY_INPUT_RIGHT])
		{
			rcA.pos.x += speed;
		}
		if (key[KEY_INPUT_UP])
		{
			rcA.pos.y -= speed;
		}
		if (key[KEY_INPUT_DOWN])
		{
			rcA.pos.y += speed;
		}
		SetDrawScreen(DX_SCREEN_BACK);
		auto mPos = GetMousePositon2();
		Vector2 dir = mPos - rcA.pos;

		float angle = atan2(dir.y, dir.x);

		ClsDrawScreen();
		int imgHigh, imgWidth;
		GetGraphSize(image, &imgWidth, &imgHigh);
		constexpr size_t block_size = 32;
		constexpr size_t width = 810;
		auto count = width / block_size;
		float weight = (float)imgWidth / float(width);
		constexpr int baseY = 240;
		constexpr int sinSape = block_size * 2;
		float X = 0.0f;
		float Y = baseY + sinSape * sin(DegreeToRadian((float)(num)));
		Position2 currentPos(X, Y);

		Position2 lastDelta90Vectors[2] = { Vector2::Syamu(),Vector2::Syamu() };

		for (int i = 1; i <= count; ++i)
		{
			float nextX = i * block_size;
			float nextY = 50.0f * sin(DegreeToRadian((float)(0.5f * nextX + num)));
			//DrawLineAA(X - 2.0f, Y, nextX - 2.0f, nextY, 0xffffff, 3.0f);
			//DrawModiGraph(X - 2, Y, nextX - 2, nextY, nextX - 2, nextY + block_size, X - 2, Y + block_size, tile, true);
			auto deltaVec = Vector2(block_size, nextY).Normalized() * block_size;//ベクトルの回収
			auto nextPos = currentPos + deltaVec;

			auto middleVec0 = deltaVec;
			auto middleVecR = deltaVec.Rotated90();
			if (!(lastDelta90Vectors[0] == Vector2::Syamu()))
			{
				middleVecR = (middleVecR + lastDelta90Vectors[0]).Normalized() * block_size;
			}
			auto middleVecL = lastDelta90Vectors[0].Rotated90();
			
			if (!(lastDelta90Vectors[1] == Vector2::Syamu()))
			{
				middleVecL = (lastDelta90Vectors[0] + lastDelta90Vectors[1]).Normalized() * block_size;
			}
			//履歴の更新
			lastDelta90Vectors[1] = lastDelta90Vectors[0];
			lastDelta90Vectors[0] = deltaVec.Rotated90();

			auto middlePosL = currentPos + middleVecL;
			auto middlePosR = nextPos + middleVecR;

			DrawRectModiGraph(
				currentPos.x , currentPos.y,
				nextPos.x , nextPos.y,
				middlePosR.x, middlePosR.y,
				middlePosL.x, middlePosL.y,
			i * block_size * weight, 0, block_size * weight ,64, image, true);
			currentPos = nextPos;
		}
		DrawBox((int)(rcA.pos.x - rcA.w), (int)(rcA.pos.y - rcA.h), (int)(rcA.pos.x + rcA.w), (int)(rcA.pos.y + rcA.w), 0xffffff, true);
		DrawRotaGraph2((int)(rcA.pos.x), (int)(rcA.pos.y), centerX, 35, 4.0f, angle, Image[num / 10 % 4], true, isReverse, false);//回転の中心を変更できる
		ScreenFlip();
		num++;
	}
	InitGraph();
	DxLib_End();
	return 0;

	//char cstr[] = "Hello Worid";
	//cout << "" << cstr[6] << endl;
	//cout << "" << 6[cstr] << endl;
	//cout << "" << *(cstr+6) << endl;
	//6[cstr] = *"N";//値が変更されたら114514する
	//cout << cstr << endl;
	//int ar[] = { 1,2,3,4,5 };
	////ar[3]というのは、ar+3ではない
	////ar[3]というのはar + 3 * sizeof(int)
	////int なら4バイト
	//cout << "" << ar[3] << endl;
	//cout << "" << 3[ar] << endl;
	//cout << "" << *(ar + 3) << endl;

	//system("pause");
}
