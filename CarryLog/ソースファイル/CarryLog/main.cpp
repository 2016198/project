#include<DxLib.h>
#include<cmath>
#include <list>
#include <memory>
#include <time.h>
#include"Geometry.h"

using namespace std;

float DrawWood(const Capsule& cap, int handle, int y,int screen) {

	int size = y;
	auto v = cap.posB - cap.posA;
	auto angle = atan2(v.y, v.x) + DX_PI_F / 2.0f;
	auto w = cos(angle) * cap.radius;
	auto h = sin(angle) * cap.radius;

	DrawModiGraph(
		cap.posA.x - w, cap.posA.y - h,
		cap.posB.x - w, cap.posB.y - h,
		cap.posB.x + w, cap.posB.y + h,
		cap.posA.x + w, cap.posA.y + h, handle,true);

	if (h < 6.0f)
	{
		if (cap.posA.y < cap.posB.y)
		{
			DrawExtendString(cap.posA.x - w, cap.posA.y - h, 2.0, 2.0, "もどして", 0xff0000);
		}
		else
		{
			DrawExtendString(cap.posB.x - w + 35, cap.posB.y - h, 2.0, 2.0, "もどして", 0xff0000);
		}
	}
	if ((int)(cap.posA.y) - screen > size - 100 || (int)(cap.posB.y) - screen > size - 100)
	{
		if (cap.posA.y > cap.posB.y)
		{
			DrawExtendString(cap.posA.x - w, cap.posA.y - h, 2.0, 2.0, "のぼって", 0xff0000);
		}
		else
		{
			DrawExtendString(cap.posB.x - w, cap.posB.y - h, 2.0, 2.0, "のぼって", 0xff0000);
		}
	}
	//DrawFormatString(0, screen, 0xffffff, "%d,", (int)(cap.posB.y) - screen);
	//DrawFormatString(0, screen, 0xffffff, "\n%d,", (int)(cap.posA.y) - screen);
	return h;
}


///とある点を中心に回転して、その回転後の座標を返します。
///@param center 回転中心点
///@param angle 回転角度
///@param pos 元の座標
///@return 変換後の座標
Matrix RotatePosition(const Position2& center, float angle) {
	//①中心を原点に平行移動して
	//②原点中心に回転して
	//③中心を元の座標へ戻す
	auto mat = TranslateMat(center.x, center.y) *
		RotateMat(angle) *
		TranslateMat(-center.x, -center.y);
	return mat;
	//これを書き換えて、特定の点を中心に回転を行うようにしてください。
}

float Clamp(float value, float minVal = 0.0f, float maxVal = 1.0f) {
	//今は値をそのまま返していますが、クランプ(最小値最大値の範囲を超えたら最小値もしくは最大値にする)した
	//値を返してください。
	return min(max(value, minVal), maxVal);
}

//カプセルと円が当たったか？
bool IsHit(const Capsule& cap, const Circle& cc) {
	//手順
	//①まず、カプセル形状の端点cap.posAからccの中心点までのベクトルvpを作ります。
	auto t = cc.pos - cap.posA;
	//②次にカプセル形状そのもののベクトルposA→posBへのベクトルvを作ります。
	auto v = cap.posB - cap.posA;
	//③①と②の内積を求めます。
	auto dot = Dot(t, v);
	//④③の結果を②の大きさの2乗で割ります
	auto f = dot / v.SQMagnitude();
	//⑤④の結果をクランプします
	f = Clamp(f);
	//⑥⑤の結果を②の結果にかけます
	v *= f;
	//⑦①のベクトルから②のベクトルを引きます
	v = t - v;
	//⑧⑦のベクトルの大きさを測ります
	auto d = v.Magnitude();
	//⑨⑧の値と、cap.radius+cc.radiusの値を比較します。
	return d <= cap.radius + cc.radius;
}

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	SetMainWindowText("2016198_筒井杏二");
	ChangeWindowMode(1);
	SetGraphMode(512, 600, 32);
	if (DxLib_Init() == -1) { return -1; }
	srand((unsigned)time(NULL));
	

	int sw, sh;//スクリーン幅、高さ
	GetDrawScreenSize(&sw, &sh);
	int zoom = 3;
	sh *= zoom;
	int screen = MakeScreen(sw, sh);

	auto woodH = LoadGraph("img/wood.png");
	int wdW, wdH;
	GetGraphSize(woodH, &wdW, &wdH);
	wdW = 200;

	auto cascadeH = LoadGraph("img/cascade_chip.png");
	auto chipH = LoadGraph("img/atlas0.png");
	auto rockH= LoadGraph("img/rock.png");
	auto explosionH = LoadGraph("img/explosion.png");
	auto explosionFrame = 0;
	auto leftH = LoadGraph("img/mario.png");
	auto rightH = LoadGraph("img/luigi.png");
	auto clearH = LoadGraph("img/clear.png");
	float clear = 15.0f;
	float vy = 0.0f;
 	int mx = 0, my = 0, screenpos = sh - (sh / zoom);
	bool game = false;

	int r = 0;
	bool move;
	if (r == rand() % 2){
		r = -10;
		move = true;
	}
	else{
		r = sw + 10;
		move = false;
	}
	Circle stone(10.0f, Position2{ (float)r, (float)(screenpos) + (rand() % (sh / zoom) / 2 + 200) });

	std::list<Circle> circles;
	circles.emplace_front(20.0f, Position2{ static_cast<float>(rand() % sw), (float)(screenpos) - 10.0f });

	Capsule cap(20, Position2((sw - wdW) / 2, sh - 100), Position2((sw - wdW) / 2 + wdW, sh - 100));

	char keystate[256];
	
	float angle = 0.0f;
	int frame = 0;
	bool isLeft = false;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		GetHitKeyStateAll(keystate);
		if (game)
		{
			if (frame % 300 == 299 && explosionFrame == 0 && (int)clear >= 15)
			{
				circles.emplace_front(20.0f, Position2{ static_cast<float>(rand() % sw), (float)(screenpos) - 10.0f });;
			}
			SetDrawScreen(screen);

			DrawBox(0, 0, sw, sh, 0xaaffff, true);

			mx = mx;
			my = my;

			if ((int)clear >= 15)
			{
				cap.posA.y += 0.70f;
				cap.posB.y += 0.70f;

				if (keystate[KEY_INPUT_LEFT]) {
					isLeft = true;
				}
				else if (keystate[KEY_INPUT_RIGHT]) {
					isLeft = false;
				}

				if (isLeft) {
					mx = cap.posA.x;
					my = cap.posA.y;
				}
				else {
					mx = cap.posB.x;
					my = cap.posB.y;
				}

				if (keystate[KEY_INPUT_Z]) {

					angle = -0.05f;
				}
				else if (keystate[KEY_INPUT_X]) {

					angle = 0.05f;
				}
				else {
					angle = 0.0f;
				}

				if (explosionFrame > 0)
				{
					angle = 0.0f;
				}
				if (explosionFrame == 0)
				{
					if (circles.size() != 0)
					{
						for (auto& circle : circles)
						{
							//当たり判定を完成させて当たったときの反応を書いてください
							if (IsHit(cap, circle) ) {
								explosionFrame = 60;
								vy = -2.5f;
								circles.clear();
								break;
							}
						}
					}
					if (IsHit(cap, stone)) {
						explosionFrame = 60;
						vy = -2.5f;
						circles.clear();
					}
				}
				//カプセル回転
				Matrix rotMat = RotatePosition(Position2(mx, my), angle);
				cap.posA = MultipleVec(rotMat, cap.posA);
				cap.posB = MultipleVec(rotMat, cap.posB);
			}
			//背景の描画
			//滝
			int chipIdx = (frame / 4) % 3;
			constexpr int dest_chip_size = 32;
			int destY = 48;
			while (destY < sh) {
				int destX = 0;
				while (destX < sw) {
					DrawRectExtendGraph(
						destX, destY, destX + dest_chip_size, destY + dest_chip_size,
						chipIdx * 16, 0,
						16, 16,
						cascadeH, false);
					destX += dest_chip_size;
				}
				destY += dest_chip_size;
			}

			DrawRectGraph(0, 0, 96, 0, 32, 32, chipH, true);
			DrawRectGraph(sw - 32, 0, 32, 0, 32, 32, chipH, true);
			DrawRectGraph(0, 32, 96, 32, 32, 32, chipH, true);
			DrawRectGraph(sw - 32, 32, 32, 32, 32, 32, chipH, true);
			destY = 64;
			while (destY < sh) {
				DrawRectGraph(0, destY, 96, 64, 32, 32, chipH, true);
				DrawRectGraph(sw - 32, destY, 32, 64, 32, 32, chipH, true);
				destY += dest_chip_size;
			}
			float h = 0.0f;

			if (explosionFrame == 0)
			{
				h = DrawWood(cap, woodH, sh / zoom, screenpos);
				DrawCircle(mx, my, 30, 0xff0000, false, 3);
				if (h <= 0)
				{
					explosionFrame = 60;
					vy = -2.5f;
				}
			}

			if (explosionFrame == 0)
			{
				if (circles.size() != 0)
				{
					for (auto& circle : circles)
					{
						DrawRotaGraph(circle.pos.x, circle.pos.y, 2.1f, 0.0f, rockH, true);
						//DrawCircle(circle.pos.x, circle.pos.y, circle.radius, 0x0000ff, false, 3.0f);
					}
				}
				DrawRotaGraph(stone.pos.x, stone.pos.y, 1.3f, 0.0f, rockH, true);
				//DrawCircle(stone.pos.x, stone.pos.y, stone.radius, 0x0000ff, false, 3.0f);
			}

			if (((int)(cap.posA.y) - screenpos > sh / zoom + 10 || (int)(cap.posB.y) - screenpos > sh / zoom + 10)
				&& explosionFrame == 0)
			{
				explosionFrame = 60;
				vy = -2.5f;
				circles.clear();
			}

			if ((int)clear >= 15)//clear = 10.0f;
			{
				if (circles.size() != 0)
				{
					for (auto& circle : circles)
					{
						circle.pos.y += 1.0f;
						if (circle.pos.y > sh + 30)
						{
							circles.pop_back();
							break;
						}
					}
				}
				if (move){
					stone.pos.x++;
				}
				else {
					stone.pos.x--;
				}
				if ((int)(stone.pos.x) >= sw + 20 ||
					(int)(stone.pos.x) <= -10 ||
					(int)(stone.pos.y) - screenpos >= sh / zoom + 10)
				{
					if (r == rand() % 2) {
						r = -10;
						move = true;
					}
					else {
						r = sw + 10;
						move = false;
					}
					stone.pos = { (float)r, (float)(screenpos)+(rand() % (sh / zoom) / 2 + 200) };
				}
			}

			if (explosionFrame > 0)
			{
				--explosionFrame;
				auto center = (cap.posA + cap.posB) * 0.5;
				auto srcX = (60 - explosionFrame) / 5 * 128;
				cap.posA.y += vy;
				cap.posB.y += vy;
				vy += 0.25f;
				DrawRotaGraph(cap.posA.x, cap.posA.y, 3.0f, 0.0f, leftH, true);
				DrawRotaGraph(cap.posB.x, cap.posB.y, 3.0f, 0.0f, rightH, true);
				DrawRectRotaGraph2(center.x, center.y, srcX, 0, 128, 128, 64, 100, 1.0f, 0.0f, explosionH, true);
				if (explosionFrame == 0)
				{
					cap.posA = Position2((sw - wdW) / 2, sh - 100);
					cap.posB = Position2((sw - wdW) / 2 + wdW, sh - 100);
					angle = 0.0f;
					circles.clear();
					screenpos = sh - (sh / zoom);
					circles.emplace_front(20.0f, Position2{ static_cast<float>(rand() % sw),(float)(screenpos) - 10.0f });
					frame = 0;
					if (r == rand() % 2) {
						r = -10;
						move = true;
					}
					else {
						r = sw + 10;
						move = false;
					}
					stone.pos = { (float)r, (float)(screenpos)+(rand() % (sh / zoom) / 2 + 200) };
				}
			}

			//static constexpr float TIME_CLEAR_MESSAGE = 3.0f;
			if (cap.posA.y <= 48 && cap.posB.y <= 48)
			{
				DrawGraph(20, 100, clearH, true);
				clear -= 0.1f;
			}

			if ((int)clear == 0)
			{
				cap.posA = Position2((sw - wdW) / 2, sh - 100);
				cap.posB = Position2((sw - wdW) / 2 + wdW, sh - 100);
				angle = 0.0f;
				circles.clear();
				screenpos = sh - (sh / zoom);
				circles.emplace_front(20.0f, Position2{ static_cast<float>(rand() % sw),(float)(screenpos) - 10.0f });
				clear = 15.0f;
				frame = 0;
				if (r == rand() % 2) {
					r = -10;
					move = true;
				}
				else {
					r = sw + 10;
					move = false;
				}
				stone.pos = { (float)r, (float)(screenpos)+(rand() % (sh / zoom) / 2 + 200) };
			}

			++frame;
			SetDrawScreen(DX_SCREEN_BACK);

			DrawGraph(0, -screenpos, screen, true);
			if ((cap.posB.y - screenpos < 100 || cap.posA.y - screenpos < 100) && screenpos > 0)
			{
				screenpos -= 5;
			}
			else if (screenpos < 0)
			{
				screenpos = 0;
			}
		}
		else
		{
			SetDrawScreen(DX_SCREEN_BACK);
			DrawExtendString(120, 180, 2.0, 2.0, "  丸太のぼり", 0xffffff);
			DrawExtendString(60, 180, 2.0, 2.0, "\nスペースキーでスタート", 0xffffff);
			DrawExtendString(150, 400, 1.0, 1.0, "zで反時計回り", 0xffffff);
			DrawExtendString(150, 450, 1.0, 1.0, "xで時計回り", 0xffffff);
			DrawExtendString(150, 500, 1.0, 1.0, "←→で回転軸変更", 0xffffff);

			if (keystate[KEY_INPUT_SPACE])
			{
				//PlayMusic("img/bgm.wav", DX_PLAYTYPE_LOOP);
				game = true;
			}
		}
		
		ScreenFlip();
	}
	InitGraph();
	DxLib_End();

	return 0;
}