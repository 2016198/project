//#include <utility>
#include <algorithm>
#include <memory>
#include <vector>
#include <iostream>
#include <chrono>
#include <DxLib.h>
#include "class/Square.h"
#include "class/Circle.h"
#include "class/Triangle.h"
#include "class/Star.h"
#include"class/Trefoil.h"
#include "class/Cross.h"
#include "class/Effect.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"

namespace chrono = std::chrono;

bool SysInit(void)
{
	SetGraphMode(640, 480, 32);
	ChangeWindowMode(true);
	SetWindowText("2016198_筒井杏二");
	if (DxLib_Init() == -1)
	{
		return false;
	}
	_dbgSetup(1024,768,255);
	return true;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	if (!SysInit())
	{
		return -1;
	}

	auto start = std::chrono::system_clock::now();     // 計測スタート時刻を保存
	auto end = std::chrono::system_clock::now();       // 計測終了時刻を保存
	auto dur = end - start;        // 要した時間を計算
	auto msec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
	float delta = msec / 1000000.0f;

	std::vector<std::unique_ptr<Shape>> shapeVec;
	//shape.resize(2);
	shapeVec.reserve(500);
	shapeVec.emplace_back(std::make_unique<Square>(Vector2Flt{ 100, 100 }, Vector2Flt{ 100, 100 }, Vector2Flt{ 1, -1 }, 0x00ffff));
	shapeVec.emplace_back(std::make_unique<Circle>(Vector2Flt{ 300, 300 }, Vector2Flt{ 50, 50 }, Vector2Flt{ -1, 1 }, 0xff00ff));
	shapeVec.emplace_back(std::make_unique<Star>(Vector2Flt{ 400, 350 }, Vector2Flt{ 50, 50 }, Vector2Flt{ 1, 1 }, 0x114514));
	shapeVec.emplace_back(std::make_unique<Trefoil>(Vector2Flt{ 100, 300 }, Vector2Flt{ 25, 25 }, Vector2Flt{ -1, -1 }, 0x364364));
	shapeVec.emplace_back(std::make_unique<Triangle>(Vector2Flt{ 200, 300 }, Vector2Flt{ 50, 50 }, Vector2Flt{ -1, 1 }, 0xffff00));	//多様性
	shapeVec.emplace_back(std::make_unique<Cross>(Vector2Flt{ 300, 100 }, Vector2Flt{ 50, 20 }, Vector2Flt{ -1, 1 }, 0x00ff00));

	/*名前空間を意識する*/
	//SquareのDrawで描画する
	//Vector2Flt data = { 200,200 };

	//std::unique_ptr<Shape> shape1;
	//std::unique_ptr<Shape> shape1(new Square(Vector2Flt{ 200, 200 }, Vector2Flt{ 100, 100 }));//①
	////宣伝と中身のインスタンスを分けられる
	////新しいオブジェクトとしてつくる
	//shape1.reset(new Square(Vector2Flt{ 200, 200 }, Vector2Flt{ 100, 100 }));//②
	////
	//shape1 = std::make_unique<Square>(Vector2Flt{ 200, 200 }, Vector2Flt{ 100, 100 });//③
	//std::unique_ptr<Shape> shape1 = std::make_unique<Square>(Vector2Flt{ 100, 100 }, Vector2Flt{ 100, 100 });
	//std::unique_ptr<Shape> shape2 = std::make_unique<Circle>(Vector2Flt{ 300, 300 }, Vector2Flt{ 100, 100 });
	//書いたものは＊型＊になる

	std::vector<int> intVec = { 1,74,1,6,10 };
	for (auto num : intVec) 
	{
		TRACE("%d ", num);
	}
	TRACE("\n");
	//intVec.erase(intVec.begin() + 1);//n番目の要素を消す
	//auto itr = intVec.begin();
	/*for (auto itr = intVec.begin(); itr != intVec.end();)
	{
		if ((*itr) % 2 == 0)
		{
			itr = intVec.erase(itr);
		}
		else
		{
			itr++;
		}
	}*/

	//ラムダ式 [キャプチャー部](引数部){式本体};
	//auto CheckNum = [&](int num) {return num % 2 == 0; };

	auto itr = std::remove_if(intVec.begin(), intVec.end(), [&](int num) {return num % 2 == 0; });
	intVec.erase(itr, intVec.end());
	
	for (auto num : intVec)
	{
		TRACE("%d" ,num);
	}
	//Shape* shape1 = new Square(Vector2Flt{ 200, 200 }, Vector2Flt{ 100, 100 });
	////ShapeのDrawで描画する
	//Shape* shape2 = new Shape(110, 10, 30, 30);
	//Square* shape3 = new Square(210, 10, 30, 30);
	float c = 0.0f;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();
		end = std::chrono::system_clock::now();       // 計測終了時刻を保存
		dur = end - start;        // 要した時間を計算
		msec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();// 要した時間をマイクロ秒（1/1,000,000秒）に変換して表示
		delta = msec / 1000000.0f;

		for (const auto& shape : shapeVec)
		{
			if (shape->UpDate(delta, *shape.get()))
			{
				for (int t = 0; t < 6; t++)
				{
					float x = (GetRand(514) - 257) / 10.0f;
					float y = (GetRand(514) - 257) / 10.0f;
					shapeVec.emplace_back(std::make_unique<Effect>(
						shape->GetPos(),
						Vector2Flt{ 0, 0 },
						Vector2Flt{ x, y },
						GetColor(GetRand(255), GetRand(255), GetRand(255))));
				}
			}
		}
		for (const auto& shape : shapeVec)
		{
			for (const auto& shapeType : shapeVec)
			{
				if (shape->Collsion(shapeType->GetPos(), shapeType->GetSize(), shapeType->GetType()) == ShapeType::TRIANGLE)
				{
					if (c < 0.0f)
					{
						shapeVec.emplace_back(std::make_unique<Triangle>
							(Vector2Flt{ (float)GetRand(400) + 25.0f, (float)GetRand(300) + 25.0f },
								Vector2Flt{ 25.0f, 25.0f },
								Vector2Flt{ (float)(GetRand(400) - 200) / 100.0f,(float)(GetRand(400) - 200) / 100.0f },
								GetColor(GetRand(255), GetRand(255), GetRand(255))));	//多様性
					}
					c = 0.1f;
				}
			}
		}
		c -= delta;
		auto ITR = std::remove_if(shapeVec.begin(), shapeVec.end(), [&](std::unique_ptr<Shape>& cnt) {return !(cnt->IsAlive()); });
		shapeVec.erase(ITR, shapeVec.end());
		start = std::chrono::system_clock::now();      // 計測スタート時刻を保存

		SetDrawScreen(DX_SCREEN_BACK);
		ClsDrawScreen();
		//shape1->Draw(f, { 0,0 });
		/*for (int r = 0; r < shapeVec.size(); r++)
		{
			shapeVec[r]->Draw();
		}*/
		for (auto& shape : shapeVec)
		{
			shape->Draw();
		}
		//DrawFormatString(0, 0, 0xffffff, "%f", c);
		/*int x, y;
		GetMousePoint(&x, &y);
		DrawFormatString(0, 0, 0xffffff, "%d  %d", x, y);*/
		//(*shape1).Draw();//中身を直接見れる
		/*shape2->Draw();
		shape3->Shape::Draw();*/
		_dbgDraw();
		ScreenFlip();	
	}
	/*delete shape1;
	shape1 = nullptr;*/
	shapeVec.erase(shapeVec.begin(), shapeVec.end());
	DxLib_End();
	return 1;
}